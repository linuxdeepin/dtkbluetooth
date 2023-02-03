// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtkbluetooth_global.h"
#include <QMap>
#include <QDBusObjectPath>
#include <QPair>
#include <qdbusextratypes.h>
#include <qpair.h>

#ifndef TYPES_H
#define TYPES_H

DBLUETOOTH_BEGIN_NAMESPACE

using ObjectMap = QMap<QDBusObjectPath, QMap<QString, QVariantMap>>;
using Interfaces = QMap<QString, QVariantMap>;
using fileInfo_p = QPair<QDBusObjectPath, QVariantMap>;

DBLUETOOTH_END_NAMESPACE

#endif
