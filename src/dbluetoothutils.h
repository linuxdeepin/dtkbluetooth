// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DTKBLUETOOTHUTILS_H
#define DTKBLUETOOTHUTILS_H

#include "dtkbluetooth_global.h"
#include "dbluetoothdbustypes.h"
#include <QDBusObjectPath>
#include <QBluetoothUuid>
#include <QDBusArgument>
#include "dbluetoothobextransfer.h"
#include <qglobal.h>

DBLUETOOTH_BEGIN_NAMESPACE

static constexpr auto &BlueZService = "org.bluez";
static constexpr auto &BlueZObexService = "org.bluez.obex";
static constexpr auto &FakeBlueZService = "org.FakeBlueZ";
static constexpr auto &FakeBlueZObexService = "org.FakeBluez.obex";
static constexpr auto &BlueZAdapterInterface = "org.bluez.Adapter1";
static constexpr auto &BlueZDeviceInterface = "org.bluez.Device1";
static constexpr auto &BlueZObexSessionInterface = "org.bluez.obex.Session1";
static constexpr auto &BlueZObexTransferInterface = "org.bluez.obex.Transfer1";
static constexpr auto &BlueZObexObjectPushInterface = "org.bluez.obex.ObjectPush1";

inline QList<QDBusObjectPath> getSpecificObject(const ObjectMap &objects, const QStringList &Interfaces)
{
    QList<QDBusObjectPath> ret;
    for (auto it = objects.cbegin(); it != objects.cend(); ++it) {
        bool found{true};
        const auto &interfaces = it.value();
        for (const auto &interface : Interfaces) {
            if (interfaces.find(interface) == interfaces.cend()) {
                found = false;
                break;
            }
        }
        if (found)
            ret.append(it.key());
    }
    return ret;
}

inline QString DBusPathToDeviceAddr(const QDBusObjectPath &path)
{
    return path.path().split("/").last().mid(4).replace("_", ":");
}

inline QDBusObjectPath DeviceAddrToDBusPath(const QString &adapter, QString device)
{
    const auto &rawDeviceStr = "/dev_" + device.replace(":", "_");
    return QDBusObjectPath{adapter + rawDeviceStr};
}

inline QString enumToString(transferStatus transferstatus){
    QString statusStr;
    switch (transferstatus) {
        case queued: statusStr = "queued";
        break;
        case active: statusStr = "active";
        break;
        case suspended: statusStr = "suspended";
        break;
        case complete: statusStr = "complete";
        break;
        case error: statusStr = "error";
        break;
    }
    return statusStr;
}

inline transferStatus stringToenum(QString statusStr){
    transferStatus transferstatus;
    if(statusStr == "queued")
        transferstatus = queued;
    else if(statusStr == "active")
        transferstatus = active;
    else if(statusStr == "suspended")
        transferstatus = suspended;
    else if(statusStr == "complete")
        transferstatus = complete;
    else
        transferstatus = error;
    return transferstatus;
}

inline quint64 getSessionId(QString pathStr){
    return pathStr.split("/").last().mid(QString("session").size(), -1).toInt();
}

DBLUETOOTH_END_NAMESPACE

#endif
