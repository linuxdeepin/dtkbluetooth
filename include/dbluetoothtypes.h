// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOTHTYPES_H
#define DBLUETOTHTYPES_H

#include "dtkbluetooth_global.h"
#include <QObject>
#include <QVariantMap>
#include <QDBusObjectPath>
#include <QPair>

DBLUETOOTH_BEGIN_NAMESPACE

enum class AgentError : quint8 { Canceled, Rejected };

enum class RequestDest { OrgBluezAgent, OrgBluezObexAgent };

using fileInfo = QPair<int, QVariantMap>;

DBLUETOOTH_END_NAMESPACE

#endif
