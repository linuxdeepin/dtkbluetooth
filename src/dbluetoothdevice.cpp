// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dbluetoothdevice_p.h"
#include "dbluetoothutils.h"
#include "ddeviceinterface.h"
#include <DExpected>
#include <DObject>
#include <QList>

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DDevicePrivate::DDevicePrivate(const QString &path, DDevice *parent)
    : DObjectPrivate(parent)
    , m_device(new DDeviceInterface(path))
{
}

DDevicePrivate::~DDevicePrivate()
{
    delete m_device;
}

DDevice::DDevice(const QString &adapterPath, const QString &deviceAddress, QObject *parent)
    : QObject(parent)
    , DObject(*new DDevicePrivate(DeviceAddrToDBusPath(adapterPath, deviceAddress), this))
{
    D_DC(DDevice);
    connect(d->m_device, &DDeviceInterface::blockedChanged, this, &DDevice::blockedChanged);
    connect(d->m_device, &DDeviceInterface::connectedChanged, this, &DDevice::connectedChanged);
    connect(d->m_device, &DDeviceInterface::pairedChanged, this, &DDevice::pairedChanged);
    connect(d->m_device, &DDeviceInterface::servicesResolvedChanged, this, &DDevice::servicesResolvedChanged);
    connect(d->m_device, &DDeviceInterface::trustedChanged, this, &DDevice::trustedChanged);
    connect(d->m_device, &DDeviceInterface::aliasChanged, this, &DDevice::aliasChanged);
    connect(d->m_device, &DDeviceInterface::RSSIChanged, this, &DDevice::RSSIChanged);
    connect(d->m_device, &DDeviceInterface::addressTypeChangde, this, [this](const QString &type) {
        Q_EMIT addressTypeChanged(stringToAddressType(type));
    });
    connect(d->m_device, &DDeviceInterface::removed, this, &DDevice::removed);
}

DDevice::~DDevice() = default;

bool DDevice::blocked() const
{
    D_DC(DDevice);
    return d->m_device->blocked();
}

void DDevice::setBlocked(bool blocked)
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

void DDevice::setTrusted(bool trusted)
{
    D_DC(DDevice);
    d->m_device->setTrusted(trusted);
}

qint64 DDevice::adapter() const
{
    D_DC(DDevice);
    return DBusPathToAdapterId(d->m_device->adapter());
}

QString DDevice::address() const
{
    D_DC(DDevice);
    return d->m_device->address();
}

DDevice::AddressType DDevice::addressType() const
{
    D_DC(DDevice);
    return stringToAddressType(d->m_device->addressType());
}

QString DDevice::alias() const
{
    D_DC(DDevice);
    return d->m_device->alias();
}

QString DDevice::icon() const
{
    D_DC(DDevice);
    return d->m_device->icon();
}

bool DDevice::isValid() const
{
    D_DC(DDevice);
    return d->m_device->isValid();
}

DBluetoothDeviceInfo DDevice::deviceInfo() const
{
    D_DC(DDevice);
    QList<QBluetoothUuid> uuidList;
    for (const auto &uuid : d->m_device->UUIDs())
        uuidList.append(QBluetoothUuid(uuid));
    DBluetoothDeviceInfo info(QBluetoothAddress(d->m_device->address()), d->m_device->name(), d->m_device->Class());
    info.setAppearance(d->m_device->appearance());
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    info.setServiceUuids(uuidList);
#else
    info.setServiceUuids(uuidList.toVector());
#endif
    return info;
}

qint16 DDevice::RSSI() const
{
    D_DC(DDevice);
    return d->m_device->RSSI();
}

// Methods
DExpected<void> DDevice::disconnectDevice() const
{
    D_DC(DDevice);
    auto reply = d->m_device->disconnect();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::cancelPairing() const
{
    D_DC(DDevice);
    auto reply = d->m_device->cancelPairing();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::connectDevice() const
{
    D_DC(DDevice);
    auto reply = d->m_device->connect();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DDevice::pair() const
{
    D_DC(DDevice);
    auto reply = d->m_device->pair();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DBLUETOOTH_END_NAMESPACE
