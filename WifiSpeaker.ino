#include <WiFi.h>
#include "time.h"

#define TIME_TO_CONNECT 10

wifiNetworkData scanedWifiArr[MAX_WIFI_AMOUNT];

bool ConnectionOk = 0;

const char* timezoneInfo = TIMEZONE_CODE;
const char* ntpServer = "pool.ntp.org";

void init_wifi() {
  Serial.println("Initializing wifi connection...");
  WiFi.mode(WIFI_STA); // было WIFI_AP - в этом режиме WiFi.begin() к сети не подключится
  WiFi.setAutoReconnect(true);  // драйвер сам поднимет связь после короткого пропадания

  connect_to_last_wifi();
  if (ConnectionOk) sync_time(timezoneInfo);
}


//
// Периодическая проверка связи. Вызывается из loop(), ничего не блокирует.
//
#define WIFI_CHECK_PERIOD     2000    // как часто опрашивать статус, мс
#define WIFI_RECONNECT_PERIOD 30000   // как часто пробовать переподключиться, мс

static uint32_t lastWifiCheck = 0;
static uint32_t lastReconnectTry = 0;

void wifi_tick() {
  if (millis() - lastWifiCheck < WIFI_CHECK_PERIOD) return;
  lastWifiCheck = millis();

  bool nowOk = (WiFi.status() == WL_CONNECTED);

  // реагируем только на СМЕНУ состояния, а не каждые 2 секунды
  if (nowOk != ConnectionOk) {
    ConnectionOk = nowOk;
    on_wifi_state_changed(nowOk);
  }

  // связи нет - изредка пробуем поднять. reconnect() не блокирует.
  if (!ConnectionOk && millis() - lastReconnectTry > WIFI_RECONNECT_PERIOD) {
    lastReconnectTry = millis();
    Serial.println("[WIFI] trying to reconnect...");
    WiFi.reconnect();
  }
}

void on_wifi_state_changed(bool ok) {
  if (ok) {
    Serial.print("[WIFI] connected, ip: ");
    Serial.println(WiFi.localIP());
    sync_time(timezoneInfo);   // время могло разъехаться, пока связи не было
  }
  else {
    Serial.println("[WIFI] connection lost");
  }

  // сюда же вешается обновление значка в интерфейсе
}

bool is_wifi_ok() {
  return ConnectionOk;
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

  // Сканировать можно, только когда радио в режиме станции и НЕ занято
  // попыткой подключения. После неудачного WiFi.begin() ESP32 продолжает
  // переподключаться в фоне бесконечно - и scanNetworks() отдаёт -2.
  WiFi.mode(WIFI_STA);
  WiFi.scanDelete();
  WiFi.disconnect(false);
  delay(100);

  int n = WiFi.scanNetworks();
  if (n <= 0) {
    // -1 = WIFI_SCAN_RUNNING (ещё идёт), -2 = WIFI_SCAN_FAILED
    Serial.print("No networks found...  (");
    Serial.print(n);
    Serial.println(")");
    set_var_cur_wifi_amount(0);
  }
  else {
    // memset по структурам со String ломает кучу - чистим полями
    for (int i = 0; i < MAX_WIFI_AMOUNT; i++) {
      scanedWifiArr[i].ssid = "";
      scanedWifiArr[i].rssi = 0;
      scanedWifiArr[i].authOpen = false;
    }

    Serial.print(n);
    Serial.println(" networks found");

    Serial.println("---------");
    for (int i = 0; i < n; i++){
      if (i >= MAX_WIFI_AMOUNT) continue; // было ">" - запись за границу массива
      
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

wifiNetworkData *get_scaned_wifi_network_data(int index) {
  return &scanedWifiArr[index];
}

void wifi_disconnect() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void sync_time(const char* timezone) { //<-- its here,  because depends on internet connection, atleast for now
  if (!ConnectionOk) return;
  Serial.println();
  Serial.println("Syncing time");

  configTime(0, 0, ntpServer);
  setenv("TZ", timezone, 1);
  tzset();

  // int ttc = 0;
  // while (ttc != TIME_TO_CONNECT) {
  //   delay(1000);
  //   ttc ++;
  //   Serial.print(".");
  // }
  Serial.println();
  Serial.println("Timezone changed! New current time: ");

  struct tm timeInfo;
  if (!getLocalTime(&timeInfo)) {
    Serial.println("ERROR ON EXTRACTING TIME");
    //return;
  }
  getLocalTime(&timeInfo);

  Serial.print("Time: ");

  Serial.printf("%d.",timeInfo.tm_mday);
  Serial.printf("%d.",timeInfo.tm_mon + 1);
  Serial.print(timeInfo.tm_year + 1900);

  Serial.printf(" %02d:%02d:%02d\n", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
  
  Serial.println();

  common_time_procedure();
}