// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHDEVICE_H
#define DBLUETOOTHDEVICE_H

#include "dbluetoothdeviceinfo.h"
#include <DExpected>
#include <DObject>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DDevicePrivate;

class DDevice : public QObject, public DObject
{
    Q_OBJECT
    explicit DDevice(const QString &adapterPath, const QString &deviceAddress, QObject *parent = nullptr);
    friend class DAdapter;
    friend class DAgentAdaptor;

public:
    ~DDevice() override;

    enum class AddressType : quint8 { Public, Random, Unknown };

    Q_PROPERTY(bool blocked READ blocked WRITE setBlocked NOTIFY blockedChanged);
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged);
    Q_PROPERTY(bool legacyPairing READ legacyPairing CONSTANT);
    Q_PROPERTY(bool paired READ paired NOTIFY pairedChanged);
    Q_PROPERTY(bool servicesResolved READ servicesResolved NOTIFY servicesResolvedChanged);
    Q_PROPERTY(bool trusted READ trusted WRITE setTrusted NOTIFY trustedChanged);
    Q_PROPERTY(qint64 adapter READ adapter CONSTANT);
    Q_PROPERTY(QString address READ address CONSTANT);
    Q_PROPERTY(DDevice::AddressType addressType READ addressType NOTIFY addressTypeChanged)
    Q_PROPERTY(QString alias READ alias NOTIFY aliasChanged);
    Q_PROPERTY(qint16 RSSI READ RSSI NOTIFY RSSIChanged);
    Q_PROPERTY(DBluetoothDeviceInfo deviceInfo READ deviceInfo CONSTANT);
    Q_PROPERTY(QString icon READ icon CONSTANT);

    bool blocked() const;
    void setBlocked(bool blocked);
    bool connected() const;
    bool legacyPairing() const;
    bool paired() const;
    bool servicesResolved() const;
    bool trusted() const;
    void setTrusted(bool trusted);
    qint64 adapter() const;
    QString address() const;
    AddressType addressType() const;
    QString alias() const;
    DBluetoothDeviceInfo deviceInfo() const;
    QString icon() const;
    qint16 RSSI() const;
    bool isValid() const;

public Q_SLOTS:
    DExpected<void> disconnectDevice() const;
    DExpected<void> cancelPairing() const;
    DExpected<void> connectDevice() const;
    DExpected<void> pair() const;

Q_SIGNALS:
    void blockedChanged(bool blocked);
    void connectedChanged(bool connected);
    void pairedChanged(bool servicesResolved);
    void servicesResolvedChanged(bool servicesResolved);
    void trustedChanged(bool trusted);
    void addressTypeChanged(AddressType type);
    void aliasChanged(const QString &alias);
    void RSSIChanged(qint16 rssi);

    void removed();

private:
    D_DECLARE_PRIVATE(DDevice);
};

DBLUETOOTH_END_NAMESPACE
#endif
