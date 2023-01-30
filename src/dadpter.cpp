// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dadapter_p.h"
#include "ddevice.h"
#include "dtkbluetoothutils.h"

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DAdapterPrivate::DAdapterPrivate(const quint64 adapterId, DAdapter *parent)
    : DObjectPrivate(parent)
#ifdef USE_FAKE_INTERFACE
    , m_adapter(new DAdapterInterface("/org/deepin/fakebluez/hci" + QString::number(adapterId)))
#else
    , m_adapter(new DAdapterInterface("/org/bluez/hci" + QString::number(adapterId)))
#endif
{
}

DAdapterPrivate::~DAdapterPrivate()
{
    delete m_adapter;
}

DAdapter::DAdapter(const quint64 adapter, QObject *parent)
    : QObject(parent)
    , DObject(*new DAdapterPrivate(adapter, this))
{
    D_DC(DAdapter);
    connect(d->m_adapter, &DAdapterInterface::aliasChanged, this, &DAdapter::aliasChanged);
    connect(d->m_adapter, &DAdapterInterface::poweredChanged, this, &DAdapter::poweredChanged);
    connect(d->m_adapter, &DAdapterInterface::discoverableChanged, this, &DAdapter::discoverableChanged);
    connect(d->m_adapter, &DAdapterInterface::discoverableTimeoutChanged, this, &DAdapter::discoverableTimeoutChanged);
    connect(d->m_adapter, &DAdapterInterface::discoveringChanged, this, &DAdapter::discoveringChanged);
    connect(d->m_adapter, &DAdapterInterface::removed, this, &DAdapter::removed);
}

DAdapter::~DAdapter() = default;

QString DAdapter::address() const
{
    D_DC(DAdapter);
    return d->m_adapter->address();
}

AddressType DAdapter::addressType() const
{
    D_DC(DAdapter);
    const auto &type = d->m_adapter->addressType();
    if (type == "public")
        return AddressType::Public;
    else if (type == "random")
        return AddressType::Random;
    return AddressType::Unknown;
}

QString DAdapter::name() const
{
    D_DC(DAdapter);
    return d->m_adapter->name();
}

bool DAdapter::powered() const
{
    D_DC(DAdapter);
    return d->m_adapter->powered();
}

QString DAdapter::alias() const
{
    D_DC(DAdapter);
    return d->m_adapter->alias();
}

void DAdapter::setAlias(const QString &alias)
{
    D_D(DAdapter);
    d->m_adapter->setAlias(alias);
}

void DAdapter::setPowered(const bool powered)
{
    D_D(DAdapter);
    d->m_adapter->setPowered(powered);
}

bool DAdapter::discoverable() const
{
    D_DC(DAdapter);
    return d->m_adapter->discoverable();
}

void DAdapter::setDiscoverable(const bool discoverable)
{
    D_D(DAdapter);
    d->m_adapter->setDiscoverable(discoverable);
}

quint32 DAdapter::discoverableTimeout() const
{
    D_DC(DAdapter);
    return d->m_adapter->discoverableTimeout();
}

void DAdapter::setDiscoverableTimeout(const quint32 discoverableTimeout)
{
    D_D(DAdapter);
    d->m_adapter->setDiscoverableTimeout(discoverableTimeout);
}

bool DAdapter::discovering()
{
    D_DC(DAdapter);
    return d->m_adapter->discovering();
}

DDevice DAdapter::specificDevice(QString deviceAddress){
    D_DC(DAdapter);
    return DDevice(d->m_adapter->adapterPath(), deviceAddress);
}

DExpected<QStringList> DAdapter::devices() const
{
    D_DC(DAdapter);
    auto reply = d->m_adapter->devices();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    auto DeviceList = getSpecificObject(reply.value(), {QString(BlueZDeviceInterface)});
    QStringList ret;
    for (const auto &device : DeviceList)
        ret.append(DBusPathToDeviceAddr(device));
    return ret;
}

DExpected<void> DAdapter::removeDevice(const QString &device)
{
    D_DC(DAdapter);
    auto reply = d->m_adapter->removeDevice(DeviceAddrToDBusPath(d->m_adapter->adapterPath(), device));
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DAdapter::startDiscovery()
{
    D_DC(DAdapter);
    auto reply = d->m_adapter->startDiscovery();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DAdapter::stopDiscovery()
{
    D_DC(DAdapter);
    auto reply = d->m_adapter->stopDiscovery();
    reply.waitForFinished();
    if (reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DBLUETOOTH_END_NAMESPACE
