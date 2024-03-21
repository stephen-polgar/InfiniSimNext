#pragma once

#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class Battery {
    public:
      Battery();

      void ReadPowerState();
      void MeasureVoltage();
      
      uint8_t PercentRemaining() const {
        return percentRemaining;
      }

      uint16_t Voltage() const {
        return voltage;
      }

      bool BatteryIsLow() const {
        return percentRemaining <= lowBatteryThreshold;
      }

      bool IsCharging() const {
        // isCharging will go up and down when fully charged
        // isFull makes sure this returns false while fully charged.
        return isCharging && !isFull;
      }

      bool IsPowerPresent() const {
        return isPowerPresent;
      }

    private:
      static Battery* instance;

      //static constexpr nrf_saadc_input_t batteryVoltageAdcInput = NRF_SAADC_INPUT_AIN7;
    public:
      uint16_t voltage = 0;
      uint8_t percentRemaining = 0;

      bool isFull = false;
      bool isCharging = false;
      bool isPowerPresent = false;
      bool firstMeasurement = true;

      //void SaadcInit();

      //void SaadcEventHandler(nrfx_saadc_evt_t const* p_event);
      //static void AdcCallbackStatic(nrfx_saadc_evt_t const* event);

      static constexpr uint8_t lowBatteryThreshold {20};

      bool isReading = false;
    };
  }
}
