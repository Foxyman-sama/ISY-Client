#include "client.hpp"

boost::system::error_code Client::write(boost::asio::const_buffer _buf) noexcept  {
    boost::system::error_code error { };
    boost::asio::write(*mp_socket, _buf, error);
    if (!error) {
        return waitStatus();
    }

    qDebug() << "Error to write: " << error.message();
    return error;
}

boost::system::error_code Client::read(boost::asio::mutable_buffer _buf) noexcept {
    boost::system::error_code error { };
    boost::asio::read(*mp_socket, _buf, boost::asio::transfer_at_least(1), error);
    if (!error) {
        return sendStatus();
    }

    qDebug() << "Error to read: " << error.message();
    return error;
}

void Client::sendFile(const QString &_data,
                      const QString &_type) noexcept {
    if (write(boost::asio::buffer("client_send"))) {
        return;
    }

    std::vector<char> buf { };
    QFile             file { _data };
    uint64_t          size { static_cast<uint64_t>(file.size()) };
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Not opened!";
        return;
    }

    buf.resize(size);
    file.read(buf.data(), size);
    if (write(boost::asio::buffer(&size, sizeof(uint64_t)))) {
        return;
    }
    if (write(boost::asio::buffer(_type.toStdString()))) {
        return;
    }

    boost::system::error_code error { };
    for (size_t i { }; i < size; i += g_PACKET_SIZE) {
        std::vector<char> temp { };
        if (size - i < g_PACKET_SIZE) {
            temp.insert(temp.end(), buf.begin() + i, buf.end());
        }
        else {
            temp.insert(temp.end(), buf.begin() + i, buf.begin() + i + g_PACKET_SIZE);
        }
        if (write(boost::asio::buffer(temp))) {
            return;
        }
    }
}

boost::system::error_code Client::waitStatus() noexcept {
    boost::system::error_code error { };
    char                      readed[2] { };
    while (strcmp(readed, "r")) {
        boost::asio::read(*mp_socket, boost::asio::buffer(readed), error);
        if (error) {
            qDebug() << "Error to waitStatus \'r\'";
            break;
        }
    }

    return error;
}
boost::system::error_code Client::sendStatus() noexcept {
    boost::system::error_code error { };
    boost::asio::write(*mp_socket, boost::asio::buffer("r"), error);
    if (error) {
        qDebug() << "Error to sendStatus \'r\'";
    }

    return error;
}

void Client::connect(const QString &_ip,
                     const QString &_port) noexcept {
    mp_socket = new tcp::socket { m_io_context };
    mp_socket->connect(
                tcp::endpoint {
                    boost::asio::ip::address::from_string(_ip.toStdString()),
                    static_cast<boost::asio::ip::port_type>(_port.toInt())
        }
    );
    m_is_connected = true;
    emit isConnectedChanged();
}
void Client::disconnect() noexcept {
    boost::system::error_code error { };
    char                      temp[2] { };
    if (!error) {
        mp_socket->shutdown(boost::asio::socket_base::shutdown_both);
        mp_socket->close();
    }

    delete mp_socket;
    m_is_connected = false;
    emit isConnectedChanged();
}
void Client::send(const QString &_data,
                  const QString &_type) noexcept {
    if (!_data.isEmpty()) {
        if (_type.contains("file")) {
            if ((_data.contains("image")) || (_data.contains(".png")) ||
                (_data.contains(".jpg"))) {
                sendFile(_data, ".png");
            }
            else if ((_data.contains("video")) || (_data.contains(".mp4"))) {
                sendFile(_data, ".mp4");
            }
            else if ((_data.contains("audio")) || (_data.contains(".mp3"))) {
                sendFile(_data, ".mp3");
            }
        }
        else {
            if (write(boost::asio::buffer(_type.toStdString()))) {
                return;
            }
            if (write(boost::asio::buffer(_data.toStdString()))) {
                return;
            }
        }
    }
}
void Client::receive() noexcept {
    if (write(boost::asio::buffer("server_send"))) {
        return;
    }

    emit isBeginClearData();
    g_files.clear();
    emit isEndClearData();

    uint64_t size { };
    if (read(boost::asio::buffer(&size, sizeof(uint64_t)))) {
        return;
    }

    for (int i { }; i < size; ++i) {
        uint64_t name_size { };
        if (read(boost::asio::buffer(&name_size, sizeof(uint64_t)))) {
            return;
        }

        char temp[1024] { };
        if (read(boost::asio::buffer(temp, name_size))) {
            return;
        }     

        emit isBeginDataChanged();
        g_files.emplace_back(temp);
        emit isEndDataChanged();
    }

}

