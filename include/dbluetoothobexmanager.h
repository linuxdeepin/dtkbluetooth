// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHOBEXMANAGER_H
#define DBLUETOOTHOBEXMANAGER_H

#include "dbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>
#include <dexpected.h>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DObexSession;
class DObexAgent;
class DObexManagerPrivate;

class DObexManager : public QObject, public DObject
{
    Q_OBJECT
    friend class DObexManager;
public:

    explicit DObexManager(QObject *parent = nullptr);
    ~DObexManager() override = default;

    Q_PROPERTY(bool available READ available);
    Q_PROPERTY(QList<quint64> sessions READ sessions);

    bool available() const;
    QList<quint64> sessions() const;

public Q_SLOTS:
    DExpected<QSharedPointer<DObexSession>> createSessionObject(const QString &destination, const QVariantMap& args);
    DExpected<void> registerAgent(const QSharedPointer<DObexAgent> &sessionId);
    DExpected<void> unregisterAgent(const QSharedPointer<DObexAgent> &agent);
    DExpected<void> requestDefaultAgent(const QSharedPointer<DObexAgent> &agent);

Q_SIGNALS:
    void availableChanged(const bool &available);
    void sessionsChanged(const QStringList &adapters);

private:
    D_DECLARE_PRIVATE(DObexManager)
};

DBLUETOOTH_END_NAMESPACE
#endif
