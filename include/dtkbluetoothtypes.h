// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DTKBLUETOTHTYPES_H
#define DTKBLUETOTHTYPES_H

#include "dtkbluetooth_global.h"
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDBusObjectPath>
#include <qpair.h>

DBLUETOOTH_BEGIN_NAMESPACE

enum class AddressType : quint8 { Public, Random, Unknown };

using fileInfo = QPair<int,QVariantMap>;

DBLUETOOTH_END_NAMESPACE

#endif
