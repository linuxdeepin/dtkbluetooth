// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dobexobjectpushinterface.h"
#include "btdispatcher.h"
#include "btobexdispatcher.h"
#include "dtkbluetoothutils.h"
#include <QMetaType>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>

DBLUETOOTH_BEGIN_NAMESPACE

DObexObjectPushInterface::DObexObjectPushInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<fileInfo_p>("fileInfo_p");
    qDBusRegisterMetaType<fileInfo_p>();

#ifndef USE_FAKE_INTERFACE
    const auto &Service = QLatin1String(BlueZObexService);
    auto Connection = QDBusConnection::systemBus();
#else
    const auto &Service = QLatin1String(FakeBlueZObexService);
    auto Connection = QDBusConnection::sessionBus();
#endif
    const auto &Interface = QLatin1String(BlueZObexObjectPushInterface);
    m_inter = new DDBusInterface(Service, path, Interface, Connection, this);
#ifndef USE_FAKE_INTERFACE
    m_inter->connect(&BluetoothObexDispatcher::instance(), &BluetoothObexDispatcher::objectPushAdded, this, [this](const QDBusObjectPath &objectPush){
        if(m_inter->path() == objectPush.path())
            removed();
    });
#endif

}

QDBusPendingReply<fileInfo_p> DObexObjectPushInterface::sendFile(const QFileInfo &filePath){
    return m_inter->asyncCallWithArgumentList("SendFile", {QVariant::fromValue(filePath)});
}

DBLUETOOTH_END_NAMESPACE
