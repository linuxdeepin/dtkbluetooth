// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICEINTERFACE_H
#define DDEVICEINTERFACE_H

#include "dtkbluetooth_global.h"
#include "dtkbluetoothdbustypes.h"
#include <QObject>
#include <DObject>
#include <QDBusObjectPath>
#include <DDBusInterface>
#include <QDBusPendingReply>
#include <ddbusinterface.h>
#include <qdbusextratypes.h>
#include <qobjectdefs.h>
#include <QBluetoothUuid>
#include <QBluetoothDeviceInfo>


DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DDeviceInterface : public QObject{
    Q_OBJECT
public:
    explicit DDeviceInterface(QDBusObjectPath path, QObject *parent = nullptr);
    ~DDeviceInterface() override = default;

    Q_PROPERTY(bool blocked READ blocked WRITE setBlocked NOTIFY blockedChanged);
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged);
    Q_PROPERTY(bool legacyPairing READ legacyPairing NOTIFY legacyPairingChanged);
    Q_PROPERTY(bool paired READ paired NOTIFY pairedChanged);
    Q_PROPERTY(bool servicesResolved READ servicesResolved NOTIFY servicesResolvedChanged);
    Q_PROPERTY(bool trusted READ trusted WRITE setTrusted NOTIFY trustedChanged);
    Q_PROPERTY(QString adapter READ adapter NOTIFY adapterChanged);
    Q_PROPERTY(QString address READ address NOTIFY addressChanged);
    Q_PROPERTY(QString alias READ alias NOTIFY aliasChanged);
    Q_PROPERTY(QBluetoothDeviceInfo deviceInfo READ deviceInfo NOTIFY deviceInfoChanged);
    Q_PROPERTY(QStringList UUIDs READ UUIDs NOTIFY UUIDsChanged);
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged);
    Q_PROPERTY(QString name READ name NOTIFY nameChanged);

    bool blocked() const;
    void setBlocked(const bool &blocked);
    bool connected() const;
    bool legacyPairing() const;
    bool paired() const;
    bool servicesResolved() const;
    bool trusted() const;
    void setTrusted(const bool trusted);
    QString adapter() const;
    QString address() const;
    QString alias() const;
    QBluetoothDeviceInfo deviceInfo() const;
    QStringList UUIDs() const;
    QString icon() const;
    QString name() const;

public Q_SLOTS:
    QDBusPendingReply<void> disconnect();
    QDBusPendingReply<void> cancelPairing();
    QDBusPendingReply<void> Connect();
    QDBusPendingReply<void> pair();
    QDBusPendingReply<QList<qint16>> RSSI();

Q_SIGNALS:
    void blockedChanged(const bool blocked);
    void connectedChanged(const bool connected);
    void legacyPairingChanged(const bool paired);
    void pairedChanged(const bool servicesResolved);
    void servicesResolvedChanged(const bool servicesResolved);
    void trustedChanged(const bool trusted);
    void adapterChanged(const QString adapter);
    void addressChanged(const QString address);
    void aliasChanged(const QString alias);
    void deviceInfoChanged(const QBluetoothDeviceInfo deviceInfo);
    void UUIDsChanged(const QStringList UUIDs);
    void iconChanged(const QString icon);
    void nameChanged(const QString name);

    void removed();

private:
    DDBusInterface *m_inter{nullptr};

};

DBLUETOOTH_END_NAMESPACE

#endif