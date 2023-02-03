// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dmanager_p.h"
#include "dagentmanagerinterface.h"
#include "dtkbluetoothutils.h"
#include <dobject.h>
#include <qfileinfo.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DTK_CORE_NAMESPACE::emplace_tag;

DManagerPrivate::DManagerPrivate(DManager *parent)
    : DObjectPrivate(parent)
{
}

DManagerPrivate::~DManagerPrivate()
{
    delete m_manager;
}

DManager::DManager(QObject *parent)
    : QObject(parent)
    , DObject(*new DManagerPrivate(this))
{

}


DExpected<QStringList> DManager::adapters() const{
    D_DC(DManager);
    auto reply = d->m_manager->adapters();
    reply.waitForFinished();
    if (!reply.isValid()){
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    }
    auto AdapterList = getSpecificObject(reply.value(), {QString(BlueZAdapterInterface)});
    QStringList ret;
    for (const auto &adapters : AdapterList)
        ret.append(adapters.path().split("/").last().mid(3,-1));
    return ret;
};

bool DManager::available() const{
    QFileInfo bluetoothDir("/lib/systemd/system/bluetooth.service");
    if(bluetoothDir.isFile())
        return true;
    else
        return false;
};

DExpected<QSharedPointer<DAdapter>> DManager::getAdapterObject(const QString& adapterId){

};

DExpected<void> DManager::registerAgent(const QSharedPointer<DAgent> &agent){

};

DExpected<void> DManager::unregisterAgent(const QSharedPointer<DAgent> &agent){

};

DExpected<void> DManager::requestDefaultAgent(const QSharedPointer<DAgent> &agent){

};



DBLUETOOTH_END_NAMESPACE
