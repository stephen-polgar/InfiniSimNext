#pragma once
// #define min // workaround: nimble's min/max macros conflict with libstdc++
// #define max
// #include <host/ble_gap.h>
#include <atomic>
// #undef max
// #undef min

namespace Pinetime {
  namespace Controllers {  
    class MotionService {
    public:
     
      // void Init();
      // int OnStepCountRequested(uint16_t attributeHandle, ble_gatt_access_ctxt* context);
      // void OnNewStepCountValue(uint32_t stepCount);
      // void OnNewMotionValues(int16_t x, int16_t y, int16_t z);

      void SubscribeNotification(uint16_t attributeHandle);
      void UnsubscribeNotification(uint16_t attributeHandle);
      bool IsMotionNotificationSubscribed() const;

    private:
      friend class MotionController;
      explicit MotionService() = default; 
      // struct ble_gatt_chr_def characteristicDefinition[3];
      // struct ble_gatt_svc_def serviceDefinition[2];

      uint16_t stepCountHandle;
      uint16_t motionValuesHandle;
      std::atomic_bool stepCountNoficationEnabled {false};
      std::atomic_bool motionValuesNoficationEnabled {false};
    };
  }
}
