// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DOBEXSESSION_H
#define DOBEXSESSION_H

#include "dtkbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>
#include <dexpected.h>
#include <QFileInfo>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;


class DObexTransfer;
class DObexObjectPush;
class DObexSessionPrivate;

class DObexSession : public QObject, public DObject
{
    Q_OBJECT
    friend class DObexManager;
public:

    explicit DObexSession(quint64 sessionId, QObject *parent = nullptr);
    ~DObexSession() override = default;

    Q_PROPERTY(QString source READ source NOTIFY sourceChanged);
    Q_PROPERTY(QString destination READ destination NOTIFY destinationChanged);
    Q_PROPERTY(quint64 sessionId READ sessionId NOTIFY sessionIdChanged);

    QString source() const;
    QString destination() const;
    quint64 sessionId() const;

public Q_SLOTS:
    static DExpected<QSharedPointer<DObexSession>> fromId(const quint64 sessionId);

    DExpected<QString> capabilities();

    DExpected<fileInfo> sendFile(const QFileInfo &filePath);



Q_SIGNALS:
    void sourceChanged(const QString &source);
    void destinationChanged(const QString &destination);
    void sessionIdChanged(const quint64 &sessionId);

    void removed();

private:
    D_DECLARE_PRIVATE(DObexSession)
};

DBLUETOOTH_END_NAMESPACE
#endif
