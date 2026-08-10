#ifndef STRUCTURES_H
#define STRUCTURES_H

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