// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHADAPTER_H
#define DBLUETOOTHADAPTER_H

#include "dbluetoothdevice.h"
#include "dbluetoothtypes.h"
#include <QScopedPointer>
#include <DExpected>
#include <DObject>

DBLUETOOTH_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DExpected;
using DTK_CORE_NAMESPACE::DObject;

class DManager;

class DAdapterPrivate;

class DAdapter : public QObject, public DObject
{
    Q_OBJECT
    explicit DAdapter(const quint64 adapter, QObject *parent = nullptr);
    friend class DManager;

public:
    ~DAdapter() override;

    Q_PROPERTY(QString address READ address);
    Q_PROPERTY(DDevice::AddressType addressType READ addressType);
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged);
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged);
    Q_PROPERTY(bool discoverable READ discoverable WRITE setDiscoverable NOTIFY discoverableChanged);
    Q_PROPERTY(
        quint32 discoverableTimeout READ discoverableTimeout WRITE setDiscoverableTimeout NOTIFY discoverableTimeoutChanged);
    Q_PROPERTY(bool discovering READ discovering NOTIFY discoveringChanged);

    QString address() const;
    DDevice::AddressType addressType() const;
    QString name() const;
    QString alias() const;
    void setAlias(const QString &alias);
    bool powered() const;
    void setPowered(const bool powered);
    bool discoverable() const;
    void setDiscoverable(const bool discoverable);
    quint32 discoverableTimeout() const;
    void setDiscoverableTimeout(const quint32 discoverableTimeout);
    bool discovering();
    DDevice specificDevice(QString deviceAddress);

public Q_SLOTS:
    DExpected<void> removeDevice(const QString &device);
    DExpected<void> startDiscovery();
    DExpected<void> stopDiscovery();
    DExpected<QStringList> devices() const;

Q_SIGNALS:
    void aliasChanged(const QString &alias);
    void poweredChanged(const bool &powered);
    void discoverableChanged(const bool &discoverable);
    void discoverableTimeoutChanged(const quint32 discoverableTimeout);
    void discoveringChanged(const bool discovering);

    void removed();

private:
    D_DECLARE_PRIVATE(DAdapter);
};

DBLUETOOTH_END_NAMESPACE
#endif
