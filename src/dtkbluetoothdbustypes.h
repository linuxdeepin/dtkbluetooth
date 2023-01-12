// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtkbluetooth_global.h"
#include <QMap>
#include <QDBusObjectPath>

#ifndef TYPES_H
#define TYPES_H

DBLUETOOTH_BEGIN_NAMESPACE

using ObjectMap = QMap<QDBusObjectPath, QVariantMap>;
using Interfaces = QMap<QString, QVariantMap>;

DBLUETOOTH_END_NAMESPACE

#endif
