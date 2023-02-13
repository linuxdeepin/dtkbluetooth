// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHOBEXTRANSFER_H
#define DBLUETOOTHOBEXTRANSFER_H

#include "dbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DObexTransferPrivate;

enum transferStatus{
    queued, 
    active, 
    suspended,
    complete,
    error
};

class DObexTransfer : public QObject, public DObject
{
    Q_OBJECT
    explicit DObexTransfer(quint64 sessionId, quint64 transferId, QObject *parent = nullptr);
    friend class DObexManager;

public:
    ~DObexTransfer() override;


    Q_PROPERTY(transferStatus status READ status NOTIFY statusChanged);
    Q_PROPERTY(quint64 session READ session NOTIFY sessionChanged);
    Q_PROPERTY(QString name READ name NOTIFY nameChanged);
    Q_PROPERTY(quint64 size READ size NOTIFY sizeChanged);
    Q_PROPERTY(quint64 transferred READ transferred NOTIFY transferredChanged);
    Q_PROPERTY(QString filename READ filename NOTIFY filenameChanged);


    transferStatus status() const;
    quint64 session() const;
    QString name() const;
    quint64 size() const;
    quint64 transferred() const;
    QString filename() const;


public Q_SLOTS:
    DExpected<void> cancel();

Q_SIGNALS:
    void statusChanged(transferStatus status);
    void sessionChanged(quint64 session);
    void nameChanged(QString name);
    void sizeChanged(quint64 size);
    void transferredChanged(quint64 transferred);
    void filenameChanged(QString filename);

    void removed();

private:
    D_DECLARE_PRIVATE(DObexTransfer);
};

DBLUETOOTH_END_NAMESPACE
#endif
