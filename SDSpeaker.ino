#include <SD.h>
#include <ArduinoJson.h>

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

// struct paramPresetStruct{
//   int index;
//   String name;
//   float min;
//   float max;
// };

paramPresetStruct presetArr[MAX_PRESET_AMOUNT];
wifiDataStruct wifiData;

void init_SD() {
  sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  if (!SD.begin(SD_CS, sdSPI)) { // Here we need to place other SPI bus
    Serial.println("Failed to initialize SD card");
    SD_OK = false;
    return;
  }
  SD_OK = true;
  Serial.println("-- SD card initialized successfully! --");
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



String get_test_string_sd() {
  if (!SD_OK) return "";
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
    presetArr[i].index = 0;
    presetArr[i].name = "";
    presetArr[i].min = 0;
    presetArr[i].max = 0;
  }

  int itemCount = 0;
  for (JsonObject item : doc.as<JsonArray>()) {
    if (itemCount >= MAX_PRESET_AMOUNT) continue;
    paramPresetStruct paramPreset;

    paramPreset.index = item["index"];
    paramPreset.name = item["name"].as<String>();
    paramPreset.min = item["min"];
    paramPreset.max = item["max"];

    presetArr[itemCount] = paramPreset;
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

struct paramPresetStruct *get_preset(int id) {
  return &presetArr[id];
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
