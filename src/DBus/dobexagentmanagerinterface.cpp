// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dobexagentmanagerinterface.h"
#include "btdispatcher.h"
#include "dtkbluetoothutils.h"
#include <qvariant.h>

DBLUETOOTH_BEGIN_NAMESPACE

DObexAgentManagerInterface::DObexAgentManagerInterface(QObject *parent)
    : QObject(parent)
{
}

void DObexAgentManagerInterface::registerAgent(const QDBusObjectPath &agent){
    m_inter->asyncCallWithArgumentList("RegisterAgent", {QVariant::fromValue(agent)});
}

void DObexAgentManagerInterface::unregisterAgent(const QDBusObjectPath &agent){
    m_inter->asyncCallWithArgumentList("UnregisterAgent", {QVariant::fromValue(agent)});
}

DBLUETOOTH_END_NAMESPACE
