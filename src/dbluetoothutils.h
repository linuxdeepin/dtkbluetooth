// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHUTILS_H
#define DBLUETOOTHUTILS_H

#include "dbluetoothdevice.h"
#include "dtkbluetooth_global.h"
#include "dbluetoothdbustypes.h"
#include "dbluetoothobextransfer.h"
#include "dbluetoothagent.h"
#include <QDBusObjectPath>
#include <QBluetoothUuid>
#include <QDBusArgument>

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

inline QList<QDBusObjectPath>
getSpecificObject(const ObjectMap &objects, const QStringList &requiredInterfaces, const MapVariantMap &values = {})
{
    QList<QDBusObjectPath> ret;
    for (auto it = objects.cbegin(); it != objects.cend(); ++it) {
        const auto &objInterfaces = it.value();
        for (const auto &requiredInterface : requiredInterfaces) {
            const auto &objInterface = objInterfaces.find(requiredInterface);
            if (objInterface != objInterfaces.cend()) {
                const auto &interfaceProps = values.find(requiredInterface);
                if (interfaceProps == values.cend()) {
                    ret.append(it.key());
                } else {
                    const auto &requiredPrpos = interfaceProps.value();
                    const auto &existsProps = objInterface.value();
                    bool found{false};
                    for (auto requiredProp = requiredPrpos.cbegin(); requiredProp != requiredPrpos.cend(); ++requiredProp) {
                        const auto &existsProp = existsProps.find(requiredProp.key());
                        if (existsProp == existsProps.cend())
                            break;
                        const auto &v1 = requiredProp.value(), v2 = existsProp.value();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                        if (v1.typeId() == v2.typeId() and v1 == v2) {
#else
                        if (v1.type() == v2.type() and v1 == v2) {
#endif
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        ret.append(it.key());
                }
            }
        }
    }
    return ret;
}

inline quint64 DBusPathToAdapterId(const QString &path)
{
    return path.split("/").last().mid(3).toUInt();  // Adapter UBI "/org/bluez/hci0"
}

inline qint64 DBusPathToAdapterId(const QDBusObjectPath &path)
{
    return DBusPathToAdapterId(path.path());
}

inline QString AdapterIdToDBusPath(quint64 id)
{
    return QString("/org/bluez/hci") + QString::number(id);
}

inline QString DBusPathToDeviceAddr(const QDBusObjectPath &path)
{
    return path.path().split("/").last().mid(4).replace("_", ":");  // device UBI: "/org/bluez/hci0/dev_XX_XX_XX_XX_XX_XX"
}

inline QString DeviceAddrToDBusPath(const QString &adapter, QString device)
{
    const auto &rawDeviceStr = "/dev_" + device.replace(":", "_");
    return adapter + rawDeviceStr;
}

inline QString transferstatusToString(transferStatus transferstatus)
{
    switch (transferstatus) {
        case queued:
            return "queued";
        case active:
            return "active";
        case suspended:
            return "suspended";
        case complete:
            return "complete";
        case error:
            return "error";
        default:
            return QString{};
    }
}

inline transferStatus stringToTransferstatus(const QString &statusStr)
{
    if (statusStr == "queued")
        return queued;
    else if (statusStr == "active")
        return active;
    else if (statusStr == "suspended")
        return suspended;
    else if (statusStr == "complete")
        return complete;
    else
        return error;
}

inline quint64 getSessionId(QString pathStr)
{
    return pathStr.split("/").last().mid(7).toUInt();  // session UBI: "/org/bluez/obex/client/session0"
}

inline QString agentCapToString(const DAgent::Capability cap)
{
    switch (cap) {
        case DAgent::Capability::DisplayOnly:
            return "DisplayOnly";
        case DAgent::Capability::DisplayYesNo:
            return "DisplayYesNo";
        case DAgent::Capability::KeyboardOnly:
            return "KeyboardOnly";
        case DAgent::Capability::NoInputNoOutput:
            return "NoInputNoOutput";
        default:
            return QString{};
    }
}

inline QString addressTypeToString(DDevice::AddressType type)
{
    switch (type) {
        case DDevice::AddressType::Public:
            return "public";
        case DDevice::AddressType::Random:
            return "random";
        default:
            return QString{};
    }
}

inline DDevice::AddressType stringToAddressType(const QString &type)
{
    if (type == "public")
        return DDevice::AddressType::Public;
    else if (type == "random")
        return DDevice::AddressType::Random;
    else
        return DDevice::AddressType::Unknown;
}

DBLUETOOTH_END_NAMESPACE

#endif
