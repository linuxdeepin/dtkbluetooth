// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DEMO_H
#define DEMO_H

#include "dtkbluetooth_global.h"
#include <QObject>

DBLUETOOTH_BEGIN_NAMESPACE
class Demo : public QObject
{
    Q_OBJECT
public:
    Demo(QObject *parent = nullptr);
    ~Demo();
    int add(const int a, const int b);
};
DBLUETOOTH_END_NAMESPACE

#endif
