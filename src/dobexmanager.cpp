// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dobexmanager_p.h"
#include "dobexagentmanagerinterface.h"
#include "dtkbluetoothutils.h"
#include "QFileInfo"

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DObexManagerPrivate::DObexManagerPrivate(DObexManager *parent)
    : DObjectPrivate(parent)
{
}

DObexManagerPrivate::~DObexManagerPrivate()
{
    delete m_obexmanager;
}

DObexManager::DObexManager(QObject *parent)
    : QObject(parent)
    , DObject(*new DObexManagerPrivate(this))
{
}

bool DObexManager::available() const{
    QFileInfo bluetoothDir("/lib/systemd/system/bluetooth.service");
    if(bluetoothDir.isFile())
        return true;
    else
        return false;
}

QList<quint64> DObexManager::sessions() const{

}

DExpected<QSharedPointer<DObexSession>> DObexManager::createSessionObject(const QString &destination, const QVariantMap& args){

}

DExpected<void> DObexManager::registerAgent(const QSharedPointer<DObexAgent> &sessionId){

}

DExpected<void> DObexManager::unregisterAgent(const QSharedPointer<DObexAgent> &agent){

}

DExpected<void> DObexManager::requestDefaultAgent(const QSharedPointer<DObexAgent> &agent){

}



DBLUETOOTH_END_NAMESPACE
