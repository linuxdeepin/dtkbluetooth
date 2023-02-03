// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICE_P_H
#define DDEVICE_P_H

#include "ddeviceinterface.h"
#include <DObjectPrivate>
#include <dobject.h>
#include <dobject_p.h>
#include <qdbusextratypes.h>
#include "ddevice.h"

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DObjectPrivate;

class DDevicePrivate : public DObjectPrivate{
public:
    explicit DDevicePrivate(QDBusObjectPath path, DDevice *parent = nullptr);
    ~DDevicePrivate() override;

    DDeviceInterface *m_device{nullptr};
    D_DECLARE_PUBLIC(DDevice);
};

DBLUETOOTH_END_NAMESPACE

#endif
