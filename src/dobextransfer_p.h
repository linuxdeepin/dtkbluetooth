// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXTRANSFER_P_H
#define DOBEXTRANSFER_P_H

#include "dobextransferinterface.h"
#include <DObjectPrivate>
#include "dobextransfer.h"

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DObjectPrivate;

class DObexTransferPrivate : public DObjectPrivate
{
public:
    explicit DObexTransferPrivate(quint64 sessionId, quint64 transferId, DObexTransfer *parent = nullptr);
    ~DObexTransferPrivate() override;

    DObexTransferInterface *m_obextransfer{nullptr};
    D_DECLARE_PUBLIC(DObexTransfer)
};

DBLUETOOTH_END_NAMESPACE

#endif
