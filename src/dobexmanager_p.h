// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXMANAGER_P_H
#define DOBEXMANAGER_P_H

#include "dobexagentmanagerinterface.h"
#include <DObjectPrivate>
#include "dobexmanager.h"

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DObjectPrivate;

class DObexManagerPrivate : public DObjectPrivate
{
public:
    explicit DObexManagerPrivate(DObexManager *parent = nullptr);
    ~DObexManagerPrivate() override;

    DObexAgentManagerInterface *m_obexmanager{nullptr};
    D_DECLARE_PUBLIC(DObexManager)
};

DBLUETOOTH_END_NAMESPACE

#endif
