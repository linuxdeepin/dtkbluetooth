// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dadapterinterface.h"
#include "btdispatcher.h"
#include "dtkbluetoothutils.h"

DBLUETOOTH_BEGIN_NAMESPACE

DAdapterInterface::DAdapterInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
#ifndef USE_FAKE_INTERFACE
    const auto &Service = QLatin1String(BlueZService);
    auto Connection = QDBusConnection::systemBus();
#else
    const auto &Service = QLatin1String(FakeBlueZService);
    auto Connection = QDBusConnection::sessionBus();
#endif
    const auto &Interface = QLatin1String(BlueZAdapterInterface);
    m_inter = new DDBusInterface(Service, path, Interface, Connection, this);
#ifndef USE_FAKE_INTERFACE
    m_inter->connect(
        &BluetoothDispatcher::instance(), &BluetoothDispatcher::adapterAdded, this, [this](const QDBusObjectPath &adapter) {
            if (m_inter->path() == adapter.path())
                Q_EMIT removed();
        });
#endif
}

QString DAdapterInterface::address() const
{
    return qdbus_cast<QString>(m_inter->property("Address"));
}

QString DAdapterInterface::addressType() const
{
    return qdbus_cast<QString>(m_inter->property("AddressType"));
}

QString DAdapterInterface::name() const
{
    return qdbus_cast<QString>(m_inter->property("Name"));
}

QString DAdapterInterface::alias() const
{
    return qdbus_cast<QString>(m_inter->property("Alias"));
}

void DAdapterInterface::setAlias(const QString &alias)
{
    m_inter->setProperty("Alias", alias);
}

bool DAdapterInterface::powered() const
{
    return qdbus_cast<bool>(m_inter->property("Powered"));
}

void DAdapterInterface::setPowered(const bool powered)
{
    m_inter->setProperty("Powered", powered);
}

bool DAdapterInterface::discoverable() const
{
    return qdbus_cast<bool>(m_inter->property("Discoverable"));
}

void DAdapterInterface::setDiscoverable(const bool discoverable)
{
    m_inter->setProperty("Discoverable", discoverable);
}

quint32 DAdapterInterface::discoverableTimeout() const
{
    return qdbus_cast<quint32>(m_inter->property("DiscoverableTimeout"));
}

void DAdapterInterface::setDiscoverableTimeout(const quint32 discoverableTimeout)
{
    m_inter->setProperty("DiscoverableTimeout", discoverableTimeout);
}

bool DAdapterInterface::discovering() const
{
    return qdbus_cast<bool>(m_inter->property("Discovering"));
}

QDBusPendingReply<ObjectMap> DAdapterInterface::devices() const
{
    const auto &dispatcher = BluetoothDispatcher::instance();
    return dispatcher.getManagedObjects();
}

QDBusPendingReply<void> DAdapterInterface::removeDevice(const QDBusObjectPath &device)
{
    return m_inter->asyncCallWithArgumentList("RemoveDevice", {QVariant::fromValue(device)});
}

QDBusPendingReply<void> DAdapterInterface::startDiscovery()
{
    return m_inter->asyncCall("StartDiscovery");
}

QDBusPendingReply<void> DAdapterInterface::stopDiscovery()
{
    return m_inter->asyncCall("StopDiscovery");
}

DBLUETOOTH_END_NAMESPACE
