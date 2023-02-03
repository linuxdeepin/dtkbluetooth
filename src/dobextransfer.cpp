// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dobextransfer_p.h"
#include "dobextransferinterface.h"
#include "dtkbluetoothutils.h"
#include <qobjectdefs.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DObexTransferPrivate::DObexTransferPrivate(quint64 sessionId, quint64 transferId, DObexTransfer *parent)
    : DObjectPrivate(parent)
    , m_obextransfer(new DObexTransferInterface("/org/bluez/obex/client/session" + QString::number(sessionId) + "/transfer" + QString::number(transferId)))
{
}

DObexTransferPrivate::~DObexTransferPrivate()
{
    delete m_obextransfer;
}

DObexTransfer::DObexTransfer(quint64 sessionId, quint64 transferId, QObject *parent)
    : QObject(parent)
    , DObject(*new DObexTransferPrivate(sessionId, transferId, this))
{
    D_DC(DObexTransfer);
    connect(d->m_obextransfer, &DObexTransferInterface::statusChanged, this, [this](const QString statusStr){
        Q_EMIT this->statusChanged(stringToenum(statusStr));
    });
    connect(d->m_obextransfer, &DObexTransferInterface::sessionChanged, this, &DObexTransfer::sessionChanged);
    connect(d->m_obextransfer, &DObexTransferInterface::nameChanged, this, &DObexTransfer::nameChanged);
    connect(d->m_obextransfer, &DObexTransferInterface::sizeChanged, this, &DObexTransfer::sizeChanged);
    connect(d->m_obextransfer, &DObexTransferInterface::transferredChanged, this, &DObexTransfer::transferredChanged);
    connect(d->m_obextransfer, &DObexTransferInterface::filenameChanged, this, &DObexTransfer::filenameChanged);

}

DObexTransfer::~DObexTransfer() = default;

transferStatus DObexTransfer::status() const{
    D_DC(DObexTransfer);
    return stringToenum(d->m_obextransfer->status());
}

quint64 DObexTransfer::session() const{
    D_DC(DObexTransfer);
    return d->m_obextransfer->session();
}

QString DObexTransfer::name() const{
    D_DC(DObexTransfer);
    return d->m_obextransfer->name();
}

quint64 DObexTransfer::size() const{
    D_DC(DObexTransfer);
    return d->m_obextransfer->size();
}

quint64 DObexTransfer::transferred() const{
    D_DC(DObexTransfer);
    return d->m_obextransfer->transferred();
}

QString DObexTransfer::filename() const{
    D_DC(DObexTransfer);
    return d->m_obextransfer->filename();
}

DExpected<void> DObexTransfer::cancel(){
    D_DC(DObexTransfer);
    auto reply = d->m_obextransfer -> cancel();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DBLUETOOTH_END_NAMESPACE
