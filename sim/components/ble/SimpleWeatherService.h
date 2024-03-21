#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <optional>
#include <cstring>
#include <array>




int WeatherCallback(uint16_t connHandle, uint16_t attrHandle, struct ble_gatt_access_ctxt* ctxt, void* arg);

namespace Pinetime {
namespace Controllers {

class SimpleWeatherService {
public:
  
  void Init();

  int OnCommand(struct ble_gatt_access_ctxt* ctxt);

  static constexpr uint8_t MaxNbForecastDays = 5;

  enum class Icons : uint8_t {
    Sun = 0,       // ClearSky
    CloudsSun = 1, // FewClouds
    Clouds = 2,    // Scattered clouds
    BrokenClouds = 3,
    CloudShowerHeavy = 4, // shower rain
    CloudSunRain = 5,     // rain
    Thunderstorm = 6,
    Snow = 7,
    Smog = 8, // Mist
    Unknown = 255
  };

  using Location = std::array<char, 33>; // 32 char + \0 (end of string)

  struct CurrentWeather {
    CurrentWeather(uint64_t timestamp,
                   int16_t temperature,
                   int16_t minTemperature,
                   int16_t maxTemperature,
                   Icons iconId,
                   Location&& location)
        : timestamp {timestamp},
          temperature {temperature},
          minTemperature {minTemperature},
          maxTemperature {maxTemperature},
          iconId {iconId},
          location {std::move(location)} {
    }

    uint64_t timestamp;
    int16_t temperature;
    int16_t minTemperature;
    int16_t maxTemperature;
    Icons iconId;
    Location location;

    bool operator==(const CurrentWeather& other) const;
  };

  struct Forecast {
    uint64_t timestamp;
    uint8_t nbDays;

    struct Day {
      int16_t minTemperature;
      int16_t maxTemperature;
      Icons iconId;

      bool operator==(const Day& other) const;
    };

    std::array<Day, MaxNbForecastDays> days;

    bool operator==(const Forecast& other) const;
  };

  void SetCurrentWeather(uint64_t timestamp, int16_t temperature, int iconId);
  void SetForecast(uint64_t timestamp, std::array<Forecast::Day, MaxNbForecastDays> days);

  std::optional<CurrentWeather> Current() const;
  std::optional<Forecast> GetForecast() const;

  static int16_t CelsiusToFahrenheit(int16_t celsius) {
    return celsius * 9 / 5 + 3200;
  }

private:
  // 00050000-78fc-48fe-8e23-433b3a1942d0
  //static constexpr ble_uuid128_t BaseUuid() {
  //  return CharUuid(0x00, 0x00);
  //}

  // 0005yyxx-78fc-48fe-8e23-433b3a1942d0
  //static constexpr ble_uuid128_t CharUuid(uint8_t x, uint8_t y) {
  //  return ble_uuid128_t {.u = {.type = BLE_UUID_TYPE_128},
  //                       .value = {0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, y, x, 0x05, 0x00}};
  //}

  //ble_uuid128_t weatherUuid {BaseUuid()};

  //ble_uuid128_t weatherDataCharUuid {CharUuid(0x00, 0x01)};

  //const struct ble_gatt_chr_def characteristicDefinition[2] = {{.uuid = &weatherDataCharUuid.u,
  //                                                              .access_cb = WeatherCallback,
  //                                                              .arg = this,
  //                                                              .flags = BLE_GATT_CHR_F_WRITE,
  //                                                              .val_handle = &eventHandle},
  //                                                             {0}};
  //const struct ble_gatt_svc_def serviceDefinition[2] = {
  //   {.type = BLE_GATT_SVC_TYPE_PRIMARY, .uuid = &weatherUuid.u, .characteristics = characteristicDefinition},
  //    {0}};

  uint16_t eventHandle {};

  std::optional<CurrentWeather> currentWeather;
  std::optional<Forecast> forecast;
};
}
}
