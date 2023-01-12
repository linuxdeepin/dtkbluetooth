// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "btobexdispatcher.h"
#include "dtkbluetoothutils.h"

DBLUETOOTH_BEGIN_NAMESPACE

BluetoothObexDispatcher::BluetoothObexDispatcher(const QString &Service, QObject *parent)
    : DBusSignalDispatcher(Service, parent)
{
    connect(this->source, &DObjectManagerInterface::InterfacesAdded, this, &BluetoothObexDispatcher::dispatchAdded);
    connect(this->source, &DObjectManagerInterface::InterfacesRemoved, this, &BluetoothObexDispatcher::dispatchRemoved);
}

void BluetoothObexDispatcher::dispatchAdded(const QDBusObjectPath &path, const Interfaces &interfaces)
{
    if (interfaces.find(QString(BlueZObexSessionInterface)) != interfaces.cend())
        Q_EMIT sessionAdded(path);
    else if (interfaces.find(QString(BlueZObexTransferInterface)) != interfaces.cend())
        Q_EMIT transferAdded(path);
    else if (interfaces.find(QString(BlueZObexObjectPushInterface)) != interfaces.cend())
        Q_EMIT objectPushAdded(path);
    return;
}

void BluetoothObexDispatcher::dispatchRemoved(const QDBusObjectPath &path, const QStringList &args)
{
    if (args.contains(QString(BlueZObexSessionInterface)))
        Q_EMIT sessionRemoved(path);
    else if (args.contains(QString(BlueZObexTransferInterface)))
        Q_EMIT transferRemoved(path);
    else if (args.contains(QString(BlueZObexObjectPushInterface)))
        Q_EMIT objectPushRemoved(path);
    return;
}

BluetoothObexDispatcher &BluetoothObexDispatcher::instance()
{
    static BluetoothObexDispatcher dispatcher{BlueZObexService};
    return dispatcher;
}

DBLUETOOTH_END_NAMESPACE
