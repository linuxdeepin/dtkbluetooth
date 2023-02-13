// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXOBJECTPUSHINTERFACE_H
#define DOBEXOBJECTPUSHINTERFACE_H

#include "dtkbluetooth_global.h"
#include "dbluetoothdbustypes.h"
#include <QObject>
#include <DObject>
#include <QDBusObjectPath>
#include <DDBusInterface>
#include <QDBusPendingReply>
#include <qobjectdefs.h>
#include <QFileInfo>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DObexObjectPushInterface : public QObject
{
    Q_OBJECT
public:
    explicit DObexObjectPushInterface(const QString &path, QObject *parent = nullptr);
    ~DObexObjectPushInterface() override = default;

public Q_SLOTS:
    QDBusPendingReply<fileInfo_p> sendFile(const QFileInfo &filePath);

Q_SIGNALS:
    void removed();

private:
    DDBusInterface *m_inter{nullptr};
};

DBLUETOOTH_END_NAMESPACE

#endif
