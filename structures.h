#ifndef STRUCTURES_H
#define STRUCTURES_H

// Общие лимиты. Держим их ЗДЕСЬ, а не в GlobalVariables.ino:
// Arduino склеивает .ino-файлы в алфавитном порядке после главного скетча,
// поэтому CompactInputRegulator.ino идёт РАНЬШЕ GlobalVariables.ino
// и определений оттуда не видит. structures.h подключается из WeighScrip.ino,
// то есть в самом начале - значит макросы видны всем файлам.
#define MAX_PRESET_AMOUNT 10
#define MAX_WIFI_AMOUNT   5
#define MAX_INPUT_SIZE    25

#define TIMEZONE_CODE "GMT-3"

// Сколько знаков после запятой показывать для веса.
// ВНИМАНИЕ: это же число определяет, что переживёт открытие пресета -
// всё сверх него округляется и при сохранении записывается округлённым.
#define WEIGHT_DECIMALS   6

struct paramPresetStruct {
  int index;
  String name;
  // double, а не float: float это ~7 ЗНАЧАЩИХ цифр, и при весе больше
  // тысячи четыре знака после запятой в него уже не помещаются.
  // На ESP32 double настоящий, 64-битный.
  double min;
  double max;
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