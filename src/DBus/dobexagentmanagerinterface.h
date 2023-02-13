// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXAGENTMANAGERINTERFACE_H
#define DOBEXAGENTMANAGERINTERFACE_H

#include "dtkbluetooth_global.h"
#include "dbluetoothdbustypes.h"
#include <QObject>
#include <DObject>
#include <QDBusObjectPath>
#include <DDBusInterface>
#include <QDBusPendingReply>
#include <qdbusextratypes.h>
#include <qobjectdefs.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DObexAgentManagerInterface : public QObject
{
    Q_OBJECT
public:
    explicit DObexAgentManagerInterface(QObject *parent = nullptr);
    ~DObexAgentManagerInterface() override = default;

public Q_SLOTS:

    void registerAgent(const QDBusObjectPath &agent);
    void unregisterAgent(const QDBusObjectPath &agent);

Q_SIGNALS:

private:
    DDBusInterface *m_inter{nullptr};

};

DBLUETOOTH_END_NAMESPACE

#endif
