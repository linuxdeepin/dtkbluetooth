// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dbluetoothdeviceinfo.h"

DBLUETOOTH_BEGIN_NAMESPACE

DBluetoothDeviceInfo::DBluetoothDeviceInfo(const DBluetoothDeviceInfo &other)
    : QBluetoothDeviceInfo(dynamic_cast<const QBluetoothDeviceInfo &>(other))
    , m_appearance(other.m_appearance)
{
}

DBluetoothDeviceInfo::DBluetoothDeviceInfo(const QBluetoothDeviceInfo &other)
    : QBluetoothDeviceInfo(other)
{
}

DBluetoothDeviceInfo::DBluetoothDeviceInfo(const QBluetoothAddress &address, const QString &name, quint32 classOfDevice)
    : QBluetoothDeviceInfo(address, name, classOfDevice)
{
}

DBluetoothDeviceInfo::DBluetoothDeviceInfo(const QBluetoothUuid &uuid, const QString &name, quint32 classOfDevice)
    : QBluetoothDeviceInfo(uuid, name, classOfDevice)
{
}

void DBluetoothDeviceInfo::setAppearance(quint16 app)
{
    m_appearance = app;
}

quint16 DBluetoothDeviceInfo::appearance() const
{
    return m_appearance;
}

DBLUETOOTH_END_NAMESPACE
