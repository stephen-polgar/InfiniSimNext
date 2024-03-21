#pragma once

//#include <cstdint>

#include "components/ble/AlertNotificationService.h"
// #include "components/ble/BatteryInformationService.h"
// #include "components/ble/CurrentTimeClient.h"
// #include "components/ble/CurrentTimeService.h"
// #include "components/ble/DeviceInformationService.h"
// #include "components/ble/DfuService.h"
// #include "components/ble/HeartRateService.h"
// #include "components/ble/ImmediateAlertService.h"
#include "components/ble/MusicService.h"
#include "components/ble/NavigationService.h"
// #include "components/ble/ServiceDiscovery.h"
//#include "components/ble/MotionService.h"
#include "components/ble/SimpleWeatherService.h"
//#include "components/fs/FS.h"
// #include "components/ble/FSService.h"

namespace Pinetime
{
  namespace Controllers
  {
    class NimbleController
    {

    public:
      void Init();
      void StartAdvertising();
      //      int OnGAPEvent(ble_gap_event* event);

      //      int OnDiscoveryEvent(uint16_t i, const ble_gatt_error* pError, const ble_gatt_svc* pSvc);
      //      int OnCTSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error* error, const ble_gatt_chr* characteristic);
      //      int OnANSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error* error, const ble_gatt_chr* characteristic);
      //      int OnCurrentTimeReadResult(uint16_t connectionHandle, const ble_gatt_error* error, ble_gatt_attr* attribute);
      //      int OnANSDescriptorDiscoveryEventCallback(uint16_t connectionHandle,
      //                                                const ble_gatt_error* error,
      //                                                uint16_t characteristicValueHandle,
      //                                                const ble_gatt_dsc* descriptor);

      void StartDiscovery();

      uint16_t connHandle();
      void NotifyBatteryLevel(uint8_t level);

      void RestartFastAdv()
      {
        fastAdvCount = 0;
      }

      void EnableRadio();
      void DisableRadio();
     
      AlertNotificationService alertService;
      MusicService musicService;
      SimpleWeatherService weatherService;
      NavigationService navService;

    private:
      //      void PersistBond(struct ble_gap_conn_desc& desc);
      //      void RestoreBond();

      static constexpr const char *deviceName = "InfiniTime";

      //      DeviceInformationService deviceInformationService;
      //      CurrentTimeClient currentTimeClient;
      
      //      AlertNotificationClient alertNotificationClient;
      //      CurrentTimeService currentTimeService;
      
      //      BatteryInformationService batteryInformationService;
      //      ImmediateAlertService immediateAlertService;
      //      HeartRateService heartRateService;
      //      FSService fsService;
      //      ServiceDiscovery serviceDiscovery;

      uint8_t addrType;
      //      uint16_t connectionHandle = BLE_HS_CONN_HANDLE_NONE;
      uint8_t fastAdvCount = 0;
      uint8_t bondId[16] = {0};

      //      ble_uuid128_t dfuServiceUuid {
      //        .u {.type = BLE_UUID_TYPE_128},
      //        .value = {0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x30, 0x15, 0x00, 0x00}};
    };

    //    static NimbleController* nptr;
  }
}
