// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXSESSIONINTERFACE_H
#define DOBEXSESSIONINTERFACE_H

#include "dtkbluetooth_global.h"
#include <QObject>
#include <DObject>
#include <QDBusObjectPath>
#include <DDBusInterface>
#include <QDBusPendingReply>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DObexSessionInterface : public QObject
{
    Q_OBJECT
public:
    explicit DObexSessionInterface(const QString &path, QObject *parent = nullptr);
    ~DObexSessionInterface() override = default;

    Q_PROPERTY(QString source READ source NOTIFY sourceChanged);
    Q_PROPERTY(QString destination READ destination NOTIFY destinationChanged);
    Q_PROPERTY(quint64 sessionId READ sessionId NOTIFY sessionIdChanged);

    QString source() const;
    QString destination() const;
    quint64 sessionId() const;

public Q_SLOTS:
    QDBusPendingReply<QString> getCapabilities();

Q_SIGNALS:
    void sourceChanged(const QString &source);
    void destinationChanged(const QString &destination);
    void sessionIdChanged(const quint64 &sessionId);

    void removed();

private:
    DDBusInterface *m_inter{nullptr};
};

DBLUETOOTH_END_NAMESPACE

#endif
