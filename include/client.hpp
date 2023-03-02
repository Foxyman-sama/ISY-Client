#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QFile>
#include <QDebug>
#include <random>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using tcp = boost::asio::ip::tcp;

constexpr size_t            g_COOLDOWN { 30 };
constexpr size_t            g_PACKET_SIZE { 65'536 };
inline std::vector<QString> g_files { };

class Client
    : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool is_connected READ isConnected NOTIFY isConnectedChanged)

private:
    boost::asio::io_context &m_io_context;
    tcp::socket             *mp_socket;
    bool                     m_is_connected;

private:
    boost::system::error_code write(boost::asio::const_buffer _buf) noexcept;
    boost::system::error_code read(boost::asio::mutable_buffer _buf) noexcept;

    void sendFile(const QString &_data,
                  const QString &_type) noexcept;

public:
    explicit Client(boost::asio::io_context &_io_context,
                    QObject                 *_p_parent = nullptr) noexcept
        : QObject { nullptr }
        , m_io_context { _io_context }
        , mp_socket { }
        , m_is_connected { false } { }
    ~Client() noexcept {
        if (mp_socket) {
            disconnect();
        }
    }

    bool                      isConnected() const noexcept {
        return m_is_connected;
    }
    boost::system::error_code waitStatus() noexcept;
    boost::system::error_code sendStatus() noexcept;

signals:
    void isConnectedChanged();
    void isBeginClearData();
    void isEndClearData();
    void isBeginDataChanged();
    void isEndDataChanged();

public slots:
    void connect(const QString &_ip,
                 const QString &_port) noexcept;
    void disconnect() noexcept;
    void send(const QString &_data,
              const QString &_type) noexcept;
    void receive() noexcept;
};

#endif
