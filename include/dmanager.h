// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DMANAGER_H
#define DMANAGER_H

#include "dtkbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>
#include <dexpected.h>
#include "dadapter.h"

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DAgent;
class DManagerPrivate;

class DManager : public QObject, public DObject
{
    Q_OBJECT
public:


    explicit DManager(QObject *parent = nullptr);
    ~DManager() override = default;

    Q_PROPERTY(bool available READ available NOTIFY availableChanged);

    DExpected<QStringList> adapters() const;
    bool available() const;

public Q_SLOTS:
    DExpected<QSharedPointer<DAdapter>> getAdapterObject(const QString& adapterId);
    DExpected<void> registerAgent(const QSharedPointer<DAgent> &agent);
    DExpected<void> unregisterAgent(const QSharedPointer<DAgent> &agent);
    DExpected<void> requestDefaultAgent(const QSharedPointer<DAgent> &agent);

Q_SIGNALS:
    void availableChanged(const bool &available);

private:
    D_DECLARE_PRIVATE(DManager)
};

DBLUETOOTH_END_NAMESPACE
#endif
