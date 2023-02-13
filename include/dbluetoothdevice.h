// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHDEVICE_H
#define DBLUETOOTHDEVICE_H

#include "dbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>
#include <qglobal.h>
#include <qobjectdefs.h>
#include <QBluetoothUuid>
#include <QBluetoothDeviceInfo>


DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DDevicePrivate;

class DDevice : public QObject, public DObject{

    Q_OBJECT
    explicit DDevice(QString adapterPath, QString deviceAddress, QObject *parent=nullptr);
    friend class DAdapter;

public:
    ~DDevice() override;

    enum class AddressType : quint8 { Public, Random, Unknown };

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
    Q_PROPERTY(QList<QBluetoothUuid> UUIDs READ UUIDs NOTIFY UUIDsChanged);
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
    QList<QBluetoothUuid> UUIDs() const;
    QString icon() const;
    QString name() const;

public Q_SLOTS:
    DExpected<void> disconnectDevice();
    DExpected<void> cancelPairing();
    DExpected<void> connectDevice();
    DExpected<void> pair();
    DExpected<QList<qint16>> RSSI();

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
    void deviceInfoChanged(const QBluetoothDeviceInfo deviceInfo); //TODO: DBluetoothDeviceInfo
    void UUIDsChanged(const QList<QBluetoothUuid> UUIDs);
    void iconChanged(const QString icon);
    void nameChanged(const QString name);

    void removed();

private:
    D_DECLARE_PRIVATE(DDevice);

};

DBLUETOOTH_END_NAMESPACE
#endif
