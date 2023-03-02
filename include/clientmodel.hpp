#ifndef CLIENTMODEL_HPP
#define CLIENTMODEL_HPP

#include <QAbstractListModel>
#include "client.hpp"

inline boost::asio::io_context g_io { };
inline Client                  g_client { g_io };

class ClientModel
        : public QAbstractListModel {
    Q_OBJECT

public:
    enum ClientRoles {
        NAMEROLE = Qt::UserRole + 1
    };

public:
    explicit ClientModel(QObject *_p_parent = nullptr) noexcept
        : QAbstractListModel { _p_parent } {
        connect(&g_client, &Client::isBeginClearData, this, [&]() {
            beginResetModel();
        });
        connect(&g_client, &Client::isEndClearData, this, [&]() {
            endResetModel();
        });
        connect(&g_client, &Client::isBeginDataChanged, this, [&]() {
            int index { static_cast<int>(g_files.size()) };
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(&g_client, &Client::isEndDataChanged, this, [&]() {
            endInsertRows();
        });
    }

    QVariant               data(const QModelIndex &_index,
                                int                _role) const override {
        if ((_index.isValid()) && (_role == NAMEROLE)) {
            return QVariant { g_files[_index.row()] };
        }

        return QVariant();
    }
    int                    rowCount(const QModelIndex &_parent) const override {
        if (_parent.isValid()) {
            return 0;
        }

        return g_files.size();
    }
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles { };
        roles[NAMEROLE] = "name";
        return roles;
    }
};

#endif
