#ifndef STRUCTURES_H
#define STRUCTURES_H

// Общие лимиты. Держим их ЗДЕСЬ, а не в GlobalVariables.ino:
// Arduino склеивает .ino-файлы в алфавитном порядке после главного скетча,
// поэтому CompactInputRegulator.ino идёт РАНЬШЕ GlobalVariables.ino
// и определений оттуда не видит. structures.h подключается из WeighScrip.ino,
// то есть в самом начале - значит макросы видны всем файлам.
#define MAX_PRESET_AMOUNT 25
#define MAX_WIFI_AMOUNT   5
#define MAX_INPUT_SIZE    25

#define TIMEZONE_CODE "GMT-3"

struct paramPresetStruct {
  int index;
  String name;
  float min;
  float max;
};

struct wifiDataStruct {
  String lastSsid;
  String lastPassword;
};

struct wifiNetworkData {
  String ssid;
  int rssi;
  bool authOpen;
};

#endif