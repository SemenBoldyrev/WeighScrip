#include <SD.h>
#include <ArduinoJson.h>
// #include <TJpg_Decoder.h>

#include "structures.h"

#define SD_CS 5
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SCK 18

SPIClass sdSPI = SPIClass(HSPI); // Needs separated SPI bus, so it wont bother touch SPI
                                 // (I using HSPI, because i think VSPI will breake it, due to VSPI being used for touch...)

bool SD_OK = false;
JsonDocument doc;

const char presetPath[] = "/Options/Presets.json";
const char testPath[] = "/Options/TestFile.txt";
const char wifiPath[] = "/Options/WiFiConnection.json";
const char loadingImagePath[] = "/Options/ESPloadingPicture.jpg";

// struct paramPresetStruct{
//   int index;
//   String name;
//   float min;
//   float max;
// };

wifiDataStruct wifiData;

void init_SD() {
  sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  if (!SD.begin(SD_CS, sdSPI)) { // Here we need to place other SPI bus
    Serial.println("Failed to initialize SD card");
    SD_OK = false;
  }
  else // this else only exists only for on_sd_state_changed for confidence
  {
    SD_OK = true;
    Serial.println("-- SD card initialized successfully! --");
  }

  // TJpgDec.setJpgScale(1);
  // TJpgDec.setCallback(tft_output);

  on_sd_state_changed(SD_OK);
}


//
// Динамическая проверка наличия карты. Вызывать из loop().
//
// Аппаратного пина card-detect на плате нет, поэтому проверяем реальным
// обращением к носителю. SD.cardType() и SD.cardSize() НЕ подходят: они
// отдают значения, прочитанные при монтировании, и после извлечения карты
// продолжают возвращать старые данные.
//
#define SD_CHECK_PERIOD_OK   3000   // как часто проверять, когда карта есть
#define SD_CHECK_PERIOD_LOST 5000   // как часто пробовать примонтировать заново

static uint32_t lastSdCheck = 0;

// Настоящее чтение каталога: открыть корень и запросить первый элемент.
// Просто SD.open("/") может пройти по кэшу FAT и соврать.
static bool sd_probe() {
  File root = SD.open("/");
  if (!root) return false;

  if (!root.isDirectory()) {
    root.close();
    return false;
  }

  // File probe = root.openNextFile();   // здесь идёт обращение к карте
  // if (probe) probe.close();
  // root.close();
  return true;
}

void sd_tick() {
  uint32_t period = SD_OK ? SD_CHECK_PERIOD_OK : SD_CHECK_PERIOD_LOST;
  if (millis() - lastSdCheck < period) return;
  lastSdCheck = millis();

  if (SD_OK) {
    if (sd_probe()) return;          // всё на месте

    Serial.println("[SD] card removed");
    SD.end();                        // отпустить драйвер, иначе повторный begin не пройдёт
    SD_OK = false;
    on_sd_state_changed(false);
    return;
  }

  // Карты не было - пробуем примонтировать: вдруг вставили
  if (!SD.begin(SD_CS, sdSPI)) return;

  Serial.println("[SD] card inserted");
  SD_OK = true;
  on_sd_state_changed(true);
}

void on_sd_state_changed(bool ok) {
  if (ok) {
    load_presets_from_SD();   // перечитать настройки со свежей карты
    fetch_sections();
    fetch_for_selection();
  }
  show_sd_ok(ok);
  // сюда же можно повесить значок состояния карты в интерфейсе
}

bool is_sd_ok() {
  return SD_OK;
}

String read_file(const char* path) {
  if (!SD_OK) return "";
  File file = SD.open(path, FILE_READ);
  
  if (!file) {
    Serial.print("-- Failed to open file for reading: '");
    Serial.print(path);
    Serial.println("' --");
    return "";
  }

  String fileContent = file.readString();
  
  file.close();
  return fileContent;
}

void write_file(const char* path, String data) {
  if (!SD_OK) return;
  File file = SD.open(path, FILE_WRITE);
  
  if (!file) {
    Serial.print("Failed to open file for writing: '");
    Serial.print(path);
    Serial.println("'");
    return;
  }

  file.print(data);
  
  file.close();
}


// void show_loading_picture() {
//   if (!SD_OK) return;

//   // было: SD.exists("testfile.txt") - картинка рисовалась только когда
//   // постороннего файла НЕТ. Проверять надо саму картинку.
//   if (!SD.exists(loadingImagePath)) {
//     Serial.printf("!! no loading image at %s\n", loadingImagePath);
//     return;
//   }

//   // ГЛАВНОЕ: TJpg_Decoder отдаёт пиксели RGB565 в порядке байт, обратном
//   // тому, что ждёт tft.pushImage(). Без этого красный и синий меняются
//   // местами и картинка уходит в сине-зелёный.
//   bool prevSwap = tft.getSwapBytes();
//   tft.setSwapBytes(true);

//   TJpgDec.drawFsJpg(0, 0, loadingImagePath, SD);

//   // Возвращаем как было: этот же флаг влияет на вывод LVGL.
//   tft.setSwapBytes(prevSwap);
// }

String get_test_string_sd() {
  if (!SD_OK || SD.exists(testPath)) return "";
  return read_file(testPath); 
}


void load_presets_from_SD() {
  if (!SD_OK) return;

  doc.clear();

  deserializeJson(doc, read_file(presetPath));
  JsonArray jsonArr = doc.as<JsonArray>();

  // НЕЛЬЗЯ memset по массиву структур со String - это ломает кучу.
  // Чистим "по-человечески".
  for (int i = 0; i < MAX_PRESET_AMOUNT; i++) {
    paramPresetStruct *cur_preset = get_var_preset(i);
    cur_preset -> index = 0;
    cur_preset -> name = "";
    cur_preset -> min = 0;
    cur_preset -> max = 0;
  }

  int itemCount = 0;
  for (JsonObject item : doc.as<JsonArray>()) {
    if (itemCount >= MAX_PRESET_AMOUNT) continue;
    paramPresetStruct *cur_preset = get_var_preset(itemCount);

    cur_preset -> index = item["index"];
    cur_preset -> name = item["name"].as<String>();
    cur_preset -> min = item["min"];
    cur_preset -> max = item["max"];
    itemCount++;
  }

  set_var_cur_preset_amount(itemCount);
}

void save_presets_to_SD(paramPresetStruct* gPresetArr, size_t size) {
  if (!SD_OK) return;

  doc.clear();

  for (int i = 0; i < size; i++) {
    if (i >= MAX_PRESET_AMOUNT) continue;
    doc[i]["index"] = gPresetArr[i].index;
    doc[i]["name"] = gPresetArr[i].name;
    doc[i]["min"] = gPresetArr[i].min;
    doc[i]["max"] = gPresetArr[i].max;
  }

  write_file(presetPath, doc.as<String>());
}


void save_wifi_data(String gSsid, String gPassword) {
  if (!SD_OK) return;

  doc.clear();

  doc["lastSsid"] = gSsid;
  doc["lastPassword"] = gPassword;

  write_file(wifiPath, doc.as<String>());
}

wifiDataStruct *get_wifi_data() {
  if (!SD_OK) return &wifiData;

  doc.clear();

  deserializeJson(doc, read_file(wifiPath));

  wifiData.lastSsid = doc["lastSsid"].as<String>();
  wifiData.lastPassword = doc["lastPassword"].as<String>();

  return &wifiData;
}
