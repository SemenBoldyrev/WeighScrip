#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"   // sntp_get_sync_status / sntp_set_sync_status

#define TIME_TO_CONNECT 10

wifiNetworkData scanedWifiArr[MAX_WIFI_AMOUNT];

bool ConnectionOk = 0;

const char* timezoneInfo = TIMEZONE_CODE;
const char* ntpServer = "pool.ntp.org";


void init_wifi() {
  // Serial.println("Initializing wifi connection...");
  show_in_console_save_in_log("wifi","Initializing wifi connection...");
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

    // Не к чему подключаться - reconnect() только насорит в лог
    if (WiFi.SSID().length() == 0) return;

    // Драйвер уже в процессе - не мешаем, иначе получим
    // "sta is connecting, return error"
    if (WiFi.status() == WL_IDLE_STATUS) return;

    wifi_try_reconnect();
  }
}

void on_wifi_state_changed(bool ok) {
  if (ok) {
    char msg[64];
    IPAddress ip = WiFi.localIP();

    snprintf(msg, sizeof(msg), "connected, ip: %u.%u.%u.%u",
         ip[0], ip[1], ip[2], ip[3]);
    show_in_console_save_in_log("wifi",msg);
    sync_time(timezoneInfo);   // время могло разъехаться, пока связи не было
  }
  else {
    // Serial.println("[WIFI] connection lost");
    show_in_console_save_in_log("wifi","connection lost");
    wifi_try_reconnect();
  }
  //
  set_var_wifi_ok(ok);
  show_wifi_ok(ok);
  // сюда же вешается обновление значка в интерфейсе
}

void wifi_try_reconnect () {
  // strange behavior in terminal, but breaks nothing so ok
  // Serial.println("[WIFI] trying to reconnect...");
  show_in_console_save_in_log("wifi","trying to reconnect...");
  WiFi.reconnect();
  if (WiFi.status() == WL_CONNECTED) show_in_console_save_in_log("wifi","reconnection successfull!");
  else show_in_console_save_in_log("wifi","reconnection unsuccessfull...");
  
  //
  show_wifi_ok(WiFi.status() == WL_CONNECTED); // need this in 3 different places, should change later
  //
}

bool is_wifi_ok() {
  return ConnectionOk;
}

bool connect_to_wifi(String gSsid, String gPassword) { //maybe the char* would be better, but idk, struct using String
  // Serial.println("---");
  // Serial.println("Tryingn to connect to wifi, using:");
  // Serial.print("SSID: ");
  // Serial.println(gSsid);
  // Serial.print("PASSWORD: ");
  // Serial.println(gPassword);

  char msg[96];

  // %s, а не %u - это строки. И String в varargs подставлять нельзя,
  // нужен c_str(). Пароль в журнал не пишем.
  snprintf(msg, sizeof(msg), "trying to connect, ssid: %s", gSsid.c_str());

  show_in_console_save_in_log("wifi", msg);

  // Пустой или заведомо мусорный SSID подключать бессмысленно, а вот
  // навредить он успеет: драйвер уйдёт в бесконечные попытки и заблокирует
  // и следующий begin(), и сканирование.
  gSsid.trim();
  if (gSsid.length() == 0 || gSsid == "-" || gSsid == "null") {
    // Serial.println("!! no valid saved SSID, skipping connect");
    show_in_console_save_in_log("wifi","!! no valid saved SSID, skipping connect");
    ConnectionOk = 0;
    return false;
  }

  // Выходим из состояния "уже подключаюсь", иначе begin() ответит
  // "sta is connecting, cannot set config" и конфиг не применится.
  WiFi.disconnect(false);
  delay(100);

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
    // Serial.println("Connection successfull!");
    show_in_console_save_in_log("wifi","Connection successfull!");
    
    save_last_wifi_connection(gSsid, gPassword);
    ConnectionOk = 1;
  }
  else {
    // Serial.println("Unable to connect...");
    show_in_console_save_in_log("wifi","Unable to connect...");

    ConnectionOk = 0;
    // Обязательно: иначе драйвер продолжит переподключаться в фоне вечно
    // и заблокирует и сканирование, и любые следующие попытки.
    WiFi.disconnect(false);
  }

  on_wifi_state_changed(success); // <-- for on start change and etc

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
  //Serial.println("---");
  //Serial.println("Scaning network...");
  show_in_console_save_in_log("wifi","Scaning network...");

  

  // Драйвер может быть вообще не поднят - тогда любые mode/disconnect
  // отвечают 0x3001 (ESP_ERR_WIFI_NOT_INIT). Сначала убеждаемся, что он есть.
  wifi_mode_t mode = WiFi.getMode();
  char msg[48];   // было char* msg[48] - это массив УКАЗАТЕЛЕЙ, а нужен массив символов

  // \n в конце не нужен: show_in_console() и так печатает println
  snprintf(msg, sizeof(msg), "mode before scan: %d, status: %d", (int)mode, (int)WiFi.status());
  show_in_console_save_in_log("wifi", msg);

  //Serial.printf("[WIFI] mode before scan: %d, status: %d\n", (int)mode, (int)WiFi.status());

  if (mode != WIFI_STA && mode != WIFI_AP_STA) {
    if (!WiFi.mode(WIFI_STA)) {
      // Serial.println("!! cannot switch to STA, wifi driver is down");
      show_in_console_save_in_log("wifi","!! cannot switch to STA, wifi driver is down");
      set_var_cur_wifi_amount(0);
      return;
    }
    delay(100);
  }

  WiFi.scanDelete();   // сбросить результат прошлого сканирования

  // ГЛАВНОЕ. Приёмник один: сканировать эфир и одновременно пытаться
  // подключиться нельзя. А setAutoReconnect(true) заставляет драйвер
  // возобновлять попытки бесконечно, поэтому проверять WiFi.status()
  // бесполезно - формально он WL_DISCONNECTED, а радио занято.
  // Глушим автоподключение на время сканирования.
  bool wasConnected = (WiFi.status() == WL_CONNECTED);

  WiFi.setAutoReconnect(false);
  WiFi.disconnect(false);   // остановить текущую попытку, радио не выключать
  delay(150);

  int n = WiFi.scanNetworks();

  // Возвращаем автоподключение и, если связь была, поднимаем её обратно
  WiFi.setAutoReconnect(true);
  if (wasConnected) WiFi.reconnect();
  if (n <= 0) {
    // -1 = WIFI_SCAN_RUNNING (ещё идёт), -2 = WIFI_SCAN_FAILED
    char msg[48];
    snprintf(msg, sizeof(msg), "scan failed, code %d", n);
    show_in_console_save_in_log("wifi", msg);
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

  if (n < 0) show_error_message("Error on scanning network!");
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

  // configTime() только запускает SNTP-клиент и сразу возвращается,
  // ответ от сервера приходит позже - отсюда "меняется с N-го раза".
  //
  // Проверять "год больше 2020" НЕЛЬЗЯ: после первой удачной синхронизации
  // или ручной установки времени условие истинно сразу, ожидание
  // пропускается и мы снова читаем старые часы.
  // Поэтому сбрасываем признак синхронизации и ждём именно НОВЫЙ ответ.
  sntp_set_sync_status(SNTP_SYNC_STATUS_RESET);

  const uint32_t SNTP_TIMEOUT = 10000;   // мс
  uint32_t waitStart = millis();

  while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
    if (millis() - waitStart > SNTP_TIMEOUT) {
      Serial.println();
      show_in_console_save_in_log("time", "NTP sync timeout");
      break;
    }
    delay(100);
    Serial.print(".");
  }

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