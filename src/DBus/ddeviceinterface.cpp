// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddeviceinterface.h"
#include "btdispatcher.h"
#include "dadapter.h"
#include "dtkbluetoothutils.h"
#include <qbluetoothdeviceinfo.h>
#include <qdbusargument.h>
#include <qobject.h>

DBLUETOOTH_BEGIN_NAMESPACE

DDeviceInterface::DDeviceInterface(QDBusObjectPath path, QObject *parent)
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
    m_inter = new DDBusInterface(Service, path.path(), Interface, Connection, this);
#ifndef USE_FAKE_INTERFACE
    m_inter->connect(
        &BluetoothDispatcher::instance(), &BluetoothDispatcher::deviceAdded, this, []() {
            //TODO
        });
#endif
}

bool DDeviceInterface::blocked() const{
    return qdbus_cast<bool>(m_inter->property("Blocked"));
}

void DDeviceInterface::setBlocked(const bool &blocked){
    m_inter->setProperty("Blocked", blocked);
}

bool DDeviceInterface::connected() const{
    return qdbus_cast<bool>(m_inter->property("Connected"));
}

bool DDeviceInterface::legacyPairing() const{
    return qdbus_cast<bool>(m_inter->property("LegacyPairing"));
}

bool DDeviceInterface::paired() const{
    return qdbus_cast<bool>(m_inter->property("Paired"));
}

bool DDeviceInterface::servicesResolved() const{
    return qdbus_cast<bool>(m_inter->property("ServicesResolved"));
}

bool DDeviceInterface::trusted() const{
    return qdbus_cast<bool>(m_inter->property("Trusted"));
}

void DDeviceInterface::setTrusted(const bool trusted){
    m_inter->setProperty("Trusted", trusted);
}

QString DDeviceInterface::adapter() const{
    return qdbus_cast<QString>(m_inter->property("Adapter"));
}

QString DDeviceInterface::address() const{
    return qdbus_cast<QString>(m_inter->property("Address"));
}

QString DDeviceInterface::alias() const{
    return qdbus_cast<QString>(m_inter->property("Alias"));
}

QBluetoothDeviceInfo DDeviceInterface::deviceInfo() const{
    // TODO return qdbus_cast<QBluetoothDeviceInfo>(m_inter->property("DeviceInfo"));
}



DBLUETOOTH_END_NAMESPACE