// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "demoservice.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDebug>

DemoService::DemoService(QObject *parent)
    : QObject(parent)
{
    registerService();
}

DemoService::~DemoService() {}

bool DemoService::registerService()
{
    Q_UNUSED(new DemoService(this));

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService("com.deepin.FakeBluetooth")) {
        QString errorMsg = bus.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";

        qWarning() << QString("Can't register the %1 service, %2.").arg("com.deepin.FakeBluetooth").arg(errorMsg);
        return false;
    }
    if (!bus.registerObject("/com/deepin/FakeBluetooth/Agent", this)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg("/com/deepin/FakeBluetooth/Agent");
        return false;
    }

    return true;
}

bool DemoService::Docked() const
{
    return m_docked;
}

void DemoService::setDocked(bool docked)
{
    if (docked == m_docked)
        return;

    m_docked = docked;
    Q_EMIT DockedChanged(docked);
}

UserPathList DemoService::ListUsers()
{
    return m_users;
}

void DemoService::setListUsers(const UserPathList &list)
{
    if (list == m_users)
        return;

    for (auto user : list) {
        if (m_users.indexOf(user) < 0)
            Q_EMIT UserNew(user.user_id, user.path);
    }

    m_users = list;
}
