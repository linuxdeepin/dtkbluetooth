// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dobexsession_p.h"
#include "dtkbluetoothutils.h"
#include <dobject.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DObexSessionPrivate::DObexSessionPrivate(quint64 sessionId, DObexSession *parent)
    : DObjectPrivate(parent)
#ifdef USE_FAKE_INTERFACE
    , m_obexsession(new DObexSessionInterface("/org/bluez/obex/client/session" + QString::number(sessionId)))
    , m_obexobjectpush((new DObexObjectPushInterface("/org/bluez/obex/client/session" + QString::number(sessionId))))
#else
    , m_obexsession(new DObexSessionInterface("/org/bluez/obex/client/session" + QString::number(sessionId)))
    , m_obexobjectpush((new DObexObjectPushInterface("/org/bluez/obex/client/session" + QString::number(sessionId))))
#endif
{
}

DObexSessionPrivate::~DObexSessionPrivate()
{
    delete m_obexsession;
}

DObexSession::DObexSession(quint64 sessionId, QObject *parent)
    : QObject(parent)
    , DObject(*new DObexSessionPrivate(sessionId, this))
{
    D_DC(DObexSession);
    connect(d->m_obexsession, &DObexSessionInterface::sourceChanged, this, &DObexSession::sourceChanged);
    connect(d->m_obexsession, &DObexSessionInterface::destinationChanged, this, &DObexSession::destinationChanged);
    connect(d->m_obexsession, &DObexSessionInterface::sessionIdChanged, this, &DObexSession::sessionIdChanged);
}

QString DObexSession::source() const{
    D_DC(DObexSession);
    return d->m_obexsession->source();
}

QString DObexSession::destination() const{
    D_DC(DObexSession);
    return d->m_obexsession->destination();
}

quint64 DObexSession::sessionId() const{
    D_DC(DObexSession);
    return d->m_obexsession->sessionId();
}

DExpected<QString> DObexSession::capabilities(){
    D_DC(DObexSession);
    auto reply = d->m_obexsession->getCapabilities();
    reply.waitForFinished();
    if(!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<QSharedPointer<DObexSession>> DObexSession::fromId(const quint64 sessionId){
    return QSharedPointer<DObexSession>{new DObexSession(sessionId)};
}

DExpected<fileInfo> DObexSession::sendFile(const QFileInfo &filePath){
    D_DC(DObexSession);
    auto reply = d->m_obexobjectpush->sendFile(filePath);
    reply.waitForFinished();
    if(!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}




DBLUETOOTH_END_NAMESPACE
