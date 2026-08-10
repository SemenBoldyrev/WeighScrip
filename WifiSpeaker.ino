#include <WiFi.h>
#include "time.h"

#define TIME_TO_CONNECT 10

wifiNetworkData scanedWifiArr[MAX_WIFI_AMOUNT];

bool ConnectionOk = 0;

const char* timezoneInfo = "GMT-3";
const char* ntpServer = "pool.ntp.org";

void init_wifi() {
  Serial.println("Initializing wifi connection...");
  WiFi.mode(WIFI_AP);

  connect_to_last_wifi();
  if (ConnectionOk) sync_time(timezoneInfo);
}

bool connect_to_wifi(String gSsid, String gPassword) { //maybe the char* would be better, but idk, struct using String
  Serial.println("---");
  Serial.println("Tryingn to connect to wifi, using:");
  Serial.print("SSID: ");
  Serial.println(gSsid);
  Serial.print("PASSWORD: ");
  Serial.println(gPassword);

  //bool success = WiFi.softAP(gSsid, gPassword); //can just return WiFi.softAP(gSsid, gPassword), but want to debug so via success
  WiFi.begin(gSsid, gPassword);

  int ttc = 0;
  while (WiFi.status() != WL_CONNECTED && ttc != TIME_TO_CONNECT) {
    delay(1000);
    ttc ++;
    Serial.print(".");
  }
  Serial.println();

  bool success = WiFi.status() == WL_CONNECTED;

  if (success) {
    Serial.println("Connection successfull!");
    save_last_wifi_connection(gSsid, gPassword);
    ConnectionOk = 1;
  }
  else {
    Serial.println("Unable to connect..."); 
    ConnectionOk = 0; 
    }

  return success;
}

void connect_to_last_wifi() {
  wifiDataStruct* wifiData = get_wifi_data();
  connect_to_wifi(wifiData -> lastSsid, wifiData -> lastPassword);
}

void save_last_wifi_connection(String gSsid, String gPassword) {
  save_wifi_data(gSsid, gPassword);
}

void scan_network() {
  Serial.println("---");
  Serial.println("Scaning network...");

  int n = WiFi.scanNetworks();
  if (n == 0) Serial.println("No networks found...");
  else {
    memset(scanedWifiArr, 0, MAX_WIFI_AMOUNT);

    Serial.print(n);
    Serial.println(" networks found");

    Serial.println("---------");
    for (int i = 0; i < n; i++){
      if (i > MAX_WIFI_AMOUNT) continue;
      
      scanedWifiArr[i].ssid = WiFi.SSID(i);
      scanedWifiArr[i].rssi = WiFi.RSSI(i);
      scanedWifiArr[i].authOpen = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN);

      Serial.print(i);
      Serial.println(":");

      Serial.print("SSID: ");
      Serial.println(scanedWifiArr[i].ssid);

      Serial.print("RSSI: ");
      Serial.print(scanedWifiArr[i].rssi);
      Serial.println("dBm");

      Serial.print("Authefication open: ");
      Serial.println(scanedWifiArr[i].authOpen);

      Serial.println("---------");
    }

    set_var_cur_wifi_amount(n);
  }
}

wifiNetworkData *get_scaned_wifi_detwork_data(int index) {
  return &scanedWifiArr[index];
}

void wifi_disconnect() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void sync_time(const char* timezone) { //<-- its here,  because depends on internet connection, atleast for now
  if (!ConnectionOk) return;
  configTime(0, 0, ntpServer);
  setenv("TZ", timezone, 1);
  tzset();

  Serial.println();
  Serial.println("Timezone changed! New current time: ");

  int ttc = 0;
  while (ttc != TIME_TO_CONNECT) {
    delay(1000);
    ttc ++;
    Serial.print(".");
  }
  Serial.println();

  struct tm timeInfo;
  if (!getLocalTime(&timeInfo)) {
    Serial.println("ERROR ON EXTRACTING TIME");
    return;
  }

  Serial.print("Time: ");

  Serial.printf("%d.",timeInfo.tm_mday);
  Serial.printf("%d.",timeInfo.tm_mon + 1);
  Serial.print(timeInfo.tm_year + 1900);

  Serial.printf(" %02d:%02d:%02d\n", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
  
  Serial.println();
}