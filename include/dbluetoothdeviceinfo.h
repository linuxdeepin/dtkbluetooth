// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DBLUETOOTHDEVICEINFO_H
#define DBLUETOOTHDEVICEINFO_H

#include "dtkbluetooth_global.h"
#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QBluetoothUuid>

DBLUETOOTH_BEGIN_NAMESPACE

class DBluetoothDeviceInfo : public QBluetoothDeviceInfo  // TODO: WIP
{
    enum class AppearanceMainCategory {
        Unknown = 0x0,
        Phone,
        Computer,
        Watch,
        Clock,
        Display,
        RemoteControl,
        EyeGlasses,
        Tag,
        Keyring,
        MediaPlayer,
        BarcodeScanner,
        Thermometer,
        HeartRateSensor,
        BloodPressure,
        HumanInterfaceDevice,
        GlucoseMeter,
        RunningWalkingSensor,
        Cycling,
        ControlDevice,
        NetworkDevice,
        Sensor,
        LightFixture,
        Fan,
        HVAC,
        AirConditioning,
        Humidifier,
        Heating,
        AccessControl,
        MotorizedDevice,
        PowerDevice,
        LightSource,
        WindowCovering,
        AudioSink,
        AudioSource,
        MotorizedVehicle,
        DomesticAppliance,
        WearableAudioDevice,
        Aircraft,
        AVEquipment,
        DisplayEquipment,
        HearingAid,
        Gaming,
        Signage,
        PulseOximeter,
        WeightScale,
        PersonalMobilityDevice,
        ContinuousGlucoseMonitor,
        InsulinPump,
        MedicationDelivery,
        Spirometer,
        OutdoorSportActivity
    };
    enum class AppearanceUnknownSubcategory { GenericUnknown = 0x0 };
    enum class AppearancePhoneSubcategory { GenericPhone = 0x40 };
    enum class AppearanceComputerSubcategory {
        GenericComputer = 0x80,
        DesktopWorkstation,
        ServerClassComputer,
        Laptop,
        HandheldPCOrPDA,
        PalmsizePCOrPDA,
        WearableComputer,
        Tablet,
        DockingStation,
        AllInOne,
        BladeServer,
        Convertible,
        Detachable,
        IoTGateway,
        MiniPC,
        StickPC
    };
    enum class AppearanceWatchSubcategory { GenericWatch = 0xc0, SportsWatch, Smartwatch };
    enum class AppearanceClockSubcategory { GenericClock = 0x100 };
    enum class AppearanceDisplaySubcategory { GenericDisplay = 0x140 };
    enum class AppearanceRemoteControlSubcategory { GenericRemoteControl = 0x180 };
    enum class AppearanceEyeGlassesSubcategory { GenericEyeGlasses = 0x1c0 };
    enum class AppearanceTagSubcategory { GenericTag = 0x200 };
    enum class AppearanceKeyringSubcategory { GenericKeyring = 0x240 };
    enum class AppearanceMediaPlayerSubcategory { GenericMediaPlayer = 0x280 };
    enum class AppearanceBarcodeScannerSubcategory { GenericBarcodeScanner = 0x2c0 };
    enum class AppearanceThermometerSubcategory {
        GenericThermometer = 0x300,
        EarThermometer,
    };

public:
    DBluetoothDeviceInfo() = default;
    DBluetoothDeviceInfo(const DBluetoothDeviceInfo &other);
    DBluetoothDeviceInfo(const QBluetoothDeviceInfo &other);
    DBluetoothDeviceInfo(const QBluetoothAddress &address, const QString &name, quint32 classOfDevice);
    DBluetoothDeviceInfo(const QBluetoothUuid &uuid, const QString &name, quint32 classOfDevice);
    ~DBluetoothDeviceInfo() = default;

    void setAppearance(quint16 app);
    quint16 appearance() const;

private:
    quint16 m_appearance;
};

DBLUETOOTH_END_NAMESPACE

#endif
