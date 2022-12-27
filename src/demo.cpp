// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "demo.h"
#include <QDebug>

DBLUETOOTH_BEGIN_NAMESPACE
Demo::Demo(QObject *parent)
    : QObject(parent)
{
}

Demo::~Demo() {}

int Demo::add(const int a, const int b)
{
    return a + b;
}

DBLUETOOTH_END_NAMESPACE
