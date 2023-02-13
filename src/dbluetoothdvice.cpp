// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dbluetoothdevice_p.h"
#include "ddeviceinterface.h"
#include "dbluetoothutils.h"
#include <dexpected.h>
#include <dobject.h>
#include <dobject_p.h>
#include <dtkcore_global.h>
#include <qbluetoothuuid.h>
#include <qdbusextratypes.h>
#include <QDebug>
#include <qlist.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DDevicePrivate::DDevicePrivate(QDBusObjectPath path,DDevice *parent)
    : DObjectPrivate(parent)
#ifdef USE_FAKE_INTERFACE
    , m_device(new DDeviceInterface(path))
#else
    , m_device(new DDeviceInterface(path))
#endif
{
}

DDevicePrivate::~DDevicePrivate(){
    delete m_device;
}

DDevice::DDevice(QString adapterPath, QString deviceAddress,QObject *parent)
    : QObject(parent)
    , DObject(*new DDevicePrivate(DeviceAddrToDBusPath(adapterPath, deviceAddress),this))
{
    D_DC(DDevice);
    connect(d->m_device, &DDeviceInterface::blockedChanged, this, &DDevice::blockedChanged);
    connect(d->m_device, &DDeviceInterface::connectedChanged, this, &DDevice::connectedChanged);
    connect(d->m_device, &DDeviceInterface::legacyPairingChanged, this, &DDevice::legacyPairingChanged);
    connect(d->m_device, &DDeviceInterface::pairedChanged, this, &DDevice::pairedChanged);
    connect(d->m_device, &DDeviceInterface::servicesResolvedChanged, this, &DDevice::servicesResolvedChanged);
    connect(d->m_device, &DDeviceInterface::trustedChanged, this, &DDevice::trustedChanged);
    connect(d->m_device, &DDeviceInterface::adapterChanged, this, &DDevice::adapterChanged);
    connect(d->m_device, &DDeviceInterface::addressChanged, this, &DDevice::addressChanged);
    connect(d->m_device, &DDeviceInterface::aliasChanged, this, &DDevice::aliasChanged);
    connect(d->m_device, &DDeviceInterface::deviceInfoChanged, this, &DDevice::deviceInfoChanged);
    connect(d->m_device, &DDeviceInterface::UUIDsChanged, this, [this](const QStringList UUIDs){
        QList<QBluetoothUuid> ret;
        for(const auto& i : UUIDs)
            ret.append(QBluetoothUuid(i));
        Q_EMIT this->UUIDsChanged(ret);
    });
    connect(d->m_device, &DDeviceInterface::iconChanged, this, &DDevice::iconChanged);
    connect(d->m_device, &DDeviceInterface::nameChanged, this, &DDevice::nameChanged);
}

DDevice::~DDevice() = default;

bool DDevice::blocked() const
{
    D_DC(DDevice);
    return d->m_device->blocked();
}

void DDevice::setBlocked(const bool &blocked)
{
    D_DC(DDevice);
    d->m_device->setBlocked(blocked);
}

bool DDevice::connected() const
{
    D_DC(DDevice);
    return d->m_device->connected();
}

bool DDevice::legacyPairing() const
{
    D_DC(DDevice);
    return d->m_device->legacyPairing();
}

bool DDevice::paired() const
{
    D_DC(DDevice);
    return d->m_device->paired();
}

bool DDevice::servicesResolved() const
{
    D_DC(DDevice);
    return d->m_device->servicesResolved();
}

bool DDevice::trusted() const
{
    D_DC(DDevice);
    return d->m_device->trusted();
}

void DDevice::setTrusted(const bool trusted)
{
    D_DC(DDevice);
    d->m_device->setTrusted(trusted);
}

QString DDevice::adapter() const
{
    D_DC(DDevice);
    return d->m_device->adapter();
}

QString DDevice::address() const
{
    D_DC(DDevice);
    return d->m_device->address();
}

QString DDevice::alias() const
{
    D_DC(DDevice);
    return d->m_device->alias();
}

QBluetoothDeviceInfo DDevice::deviceInfo() const
{
    D_DC(DDevice);
    return d->m_device->deviceInfo();
}

QList<QBluetoothUuid> DDevice::UUIDs() const{
    D_DC(DDevice);
    auto reply = d->m_device->UUIDs();
    QList<QBluetoothUuid> ret;
    for(const auto& i : reply)
        ret.append(QBluetoothUuid(i));
    return ret;
}
QString DDevice::name() const{
    D_DC(DDevice);
    return d->m_device->name();
}

QString DDevice::icon() const{
    D_DC(DDevice);
    return d->m_device->icon();
}

//Methods
DExpected<void> DDevice::disconnectDevice(){
    D_DC(DDevice);
    auto reply = d->m_device->disconnect();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::cancelPairing(){
    D_DC(DDevice);
    auto reply = d->m_device->cancelPairing();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::connectDevice(){
    D_DC(DDevice);
    auto reply = d->m_device->connect();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::pair(){
    D_DC(DDevice);
    auto reply = d->m_device->pair();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<QList<qint16>> DDevice::RSSI(){
    D_DC(DDevice);
    auto reply = d->m_device->RSSI();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return reply.value();
}


DBLUETOOTH_END_NAMESPACE
