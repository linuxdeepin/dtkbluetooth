// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dagentmanagerinterface.h"
#include "btdispatcher.h"
#include "dtkbluetoothutils.h"
#include <dobject.h>

DBLUETOOTH_BEGIN_NAMESPACE

DAgentManagerInterface::DAgentManagerInterface(QObject *parent)
    : QObject(parent)
{

}

QDBusPendingReply<ObjectMap> DAgentManagerInterface::adapters() const{
    const auto &dispatcher = BluetoothDispatcher::instance();
    return dispatcher.getManagedObjects();
}


void DAgentManagerInterface::registerAgent(const QDBusObjectPath &agent){
    m_inter->asyncCallWithArgumentList("RegisterAgent", {QVariant::fromValue(agent)});
}

void DAgentManagerInterface::unregisterAgent(const QDBusObjectPath &agent){
    m_inter->asyncCallWithArgumentList("unregisterAgent", {QVariant::fromValue(agent)});
}

DBLUETOOTH_END_NAMESPACE
