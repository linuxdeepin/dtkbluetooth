// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddeviceinterface.h"
#include "btdispatcher.h"
#include "dadapter.h"
#include "dtkbluetoothutils.h"
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothuuid.h>
#include <qdbusabstractinterface.h>
#include <qdbusargument.h>
#include <QDBusMetaType>
#include <QMetaType>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>
#include <qlist.h>
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
    const auto &Interface = QLatin1String(BlueZDeviceInterface);
    m_inter = new DDBusInterface(Service, path.path(), Interface, Connection, this);
#ifndef USE_FAKE_INTERFACE
    m_inter->connect(
        &BluetoothDispatcher::instance(), &BluetoothDispatcher::deviceRemoved, this, [this](const QDBusObjectPath device) {
            if(device.path() == this->m_inter->path())
                Q_EMIT removed();
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
    // TODO DBluetoothDeviceInfo
    //return qdbus_cast<DBluetoothDeviceInfo>(m_inter->property("DeviceInfo"));
}

QStringList DDeviceInterface::UUIDs() const{
    return qdbus_cast<QStringList>(m_inter->property("UUIDs"));
}

QString DDeviceInterface::name() const{
    return qdbus_cast<QString>(m_inter->property("Name"));
}

QString DDeviceInterface::icon() const{
    return qdbus_cast<QString>(m_inter->property("Icon"));
}

//Methods
QDBusPendingReply<void> DDeviceInterface::disconnect(){
    return m_inter->asyncCall("Disconnect");
}

QDBusPendingReply<void> DDeviceInterface::cancelPairing(){
    return m_inter->asyncCall("CancelPairing");
}

QDBusPendingReply<void> DDeviceInterface::connect(){
    return m_inter->asyncCall("Connect");
}

QDBusPendingReply<void> DDeviceInterface::pair(){
    return m_inter->asyncCall("Pair");
}

QDBusPendingReply<QList<qint16>> DDeviceInterface::RSSI(){
    return m_inter->asyncCall("RSSI");
}


DBLUETOOTH_END_NAMESPACE
