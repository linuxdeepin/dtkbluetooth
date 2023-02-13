// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXTRANSFERINTERFACE_H
#define DOBEXTRANSFERINTERFACE_H

#include "dtkbluetooth_global.h"
#include "dbluetoothdbustypes.h"
#include <QObject>
#include <DObject>
#include <QDBusObjectPath>
#include <DDBusInterface>
#include <QDBusPendingReply>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DObexTransferInterface : public QObject
{
    Q_OBJECT
public:
    explicit DObexTransferInterface(const QString &path, QObject *parent = nullptr);
    ~DObexTransferInterface() override = default;

    Q_PROPERTY(QString status READ status NOTIFY statusChanged);
    Q_PROPERTY(quint64 session READ session NOTIFY sessionChanged);
    Q_PROPERTY(QString name READ name NOTIFY nameChanged);
    Q_PROPERTY(quint64 size READ size NOTIFY sizeChanged);
    Q_PROPERTY(quint64 transferred READ transferred NOTIFY transferredChanged);
    Q_PROPERTY(QString filename READ filename NOTIFY filenameChanged);


    QString status() const;
    quint64 session() const;
    QString name() const;
    quint64 size() const;
    quint64 transferred() const;
    QString filename() const;

public Q_SLOTS:
    QDBusPendingReply<void> cancel();

Q_SIGNALS:
    void statusChanged(QString status);
    void sessionChanged(quint64 session);
    void nameChanged(QString name);
    void sizeChanged(quint64 size);
    void transferredChanged(quint64 transferred);
    void filenameChanged(QString filename);

    void removed();

private:
    DDBusInterface *m_inter{nullptr};
};

DBLUETOOTH_END_NAMESPACE

#endif
