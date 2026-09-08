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

const char optionsFolder[]    = "/Options";
const char logsRootFolder[]   = "/Logs";
const char systemLogsFolder[] = "/Logs/System";
const char savesLogsFolder[]  = "/Logs/Saves";   // было второй раз systemLogsFolder - переопределение

// Заголовки CSV. Порядок колонок должен совпадать с порядком записи ниже.
const char saveLogHeader[]   = "timestamp,weight,dose,min,max";
const char systemLogHeader[] = "timestamp,key,message";


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
    SD_OK = false;
    // В лог не пишем - карты нет, писать некуда
    show_in_console("sd", "failed to initialize card");
  }
  else // this else only exists only for on_sd_state_changed for confidence
  {
    SD_OK = true;
    show_in_console("sd", "card initialized successfully");
  }

  // TJpgDec.setJpgScale(1);
  // TJpgDec.setCallback(tft_output);

  // Внутри стоит проверка SD_OK, так что при отсутствии карты просто выйдет.
  // Но вызывать имеет смысл ПОСЛЕ init_time() - иначе часы ещё на 1970 году
  // и первый файл уйдёт в no-date.csv.
  //check_create_directory_files(); // need to be done separatly, so everything would be created correctly

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
#define SD_CHECK_PERIOD_LOST 3000   // как часто пробовать примонтировать заново

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

    // Пишем в консоль ДО сброса флага - в лог всё равно уже не попадёт
    show_in_console("sd", "card removed");
    SD.end();                        // отпустить драйвер, иначе повторный begin не пройдёт
    SD_OK = false;
    on_sd_state_changed(false);
    return;
  }

  // Карты не было - пробуем примонтировать: вдруг вставили
  if (!SD.begin(SD_CS, sdSPI)) return;

  SD_OK = true;
  show_in_console_save_in_log("sd", "card inserted");
  on_sd_state_changed(true);
}

void on_sd_state_changed(bool ok) {
  if (ok) {
    check_create_directory_files();
    load_presets_from_SD();   // перечитать настройки со свежей карты
    fetch_sections();
    fetch_for_selection();
  }
  show_sd_ok(ok);
  block_redaction_section(true); // so there wont be issues in future
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

//
// ЖУРНАЛЫ
//
// Один файл на сутки: /Logs/Saves/2026-09-07.csv
// Так файлы не разрастаются и нужный день ищется глазами.
//

#define LOG_PATH_LEN 48


// Собирает путь вида "<папка>/ГГГГ-ММ-ДД.csv" - один файл на сутки.
// Время в имя не входит: точный момент есть в колонке timestamp внутри файла.
// Если часы ещё не установлены, кладём в отдельный файл, чтобы записи
// с датой 1970 года не смешивались с настоящими.
static void build_log_path(char* out, size_t size, const char* folder) {
  struct tm t;

  if (!getLocalTime(&t, 0) || t.tm_year < (2020 - 1900)) {
    snprintf(out, size, "%s/no-date.csv", folder);
    return;
  }

  snprintf(out, size, "%s/%04d-%02d-%02d.csv",
           folder, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
}


// Имя пересчитывается при каждом обращении: оно зависит только от даты,
// так что в течение суток получается один и тот же файл, а в полночь
// автоматически начинается новый.
static char saveLogPath[LOG_PATH_LEN]   = "";
static char systemLogPath[LOG_PATH_LEN] = "";

static const char* current_save_log_path() {
  build_log_path(saveLogPath, sizeof(saveLogPath), savesLogsFolder);
  return saveLogPath;
}

static const char* current_system_log_path() {
  build_log_path(systemLogPath, sizeof(systemLogPath), systemLogsFolder);
  return systemLogPath;
}


// Создаёт файл с шапкой, если его ещё нет. Существующий не трогает.
static bool ensure_log_file(const char* path, const char* header) {
  if (!SD_OK) return false;
  if (SD.exists(path)) return true;

  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("!! cannot create log %s\n", path);
    return false;
  }

  file.println(header);
  file.close();

  Serial.printf("[LOG] created %s\n", path);
  return true;
}


// Текст в CSV берём в кавычки: имя дозы может содержать запятую,
// иначе она разъедет колонки. Внутренние кавычки удваиваются по стандарту.
static void write_csv_text(File &file, const char* text) {
  file.print('"');
  for (const char* p = text; *p != '\0'; p++) {
    if (*p == '"') file.print('"');
    file.print(*p);
  }
  file.print('"');
}


// Создаёт файл с заданным содержимым, если его нет. Существующий не трогает.
static bool ensure_text_file(const char* path, const char* content) {
  if (!SD_OK) return false;
  if (SD.exists(path)) return true;

  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("!! cannot create %s\n", path);
    return false;
  }

  file.print(content);
  file.close();

  Serial.printf("[SD] created %s\n", path);
  return true;
}


void check_create_directory_files()
{
  if (!SD_OK) return;

  // mkdir не создаёт вложенность сам - идём сверху вниз.
  // Если папка уже есть, вызов просто вернёт false, это не ошибка.
  if (!SD.exists(optionsFolder))    SD.mkdir(optionsFolder);
  if (!SD.exists(logsRootFolder))   SD.mkdir(logsRootFolder);
  if (!SD.exists(systemLogsFolder)) SD.mkdir(systemLogsFolder);
  if (!SD.exists(savesLogsFolder))  SD.mkdir(savesLogsFolder);

  // Файлы настроек. Пустыми, но СИНТАКСИЧЕСКИ ВЕРНЫМИ:
  // deserializeJson() на отсутствующем или пустом файле оставляет doc
  // в неопределённом состоянии, и дальше читаются мусорные значения.
  ensure_text_file(presetPath, "[]");
  ensure_text_file(wifiPath,   "{\"lastSsid\":\"\",\"lastPassword\":\"\"}");

  // Картинку загрузки сгенерировать нельзя - только предупредить
  if (!SD.exists(loadingImagePath)) {
    Serial.printf("!! no loading image at %s\n", loadingImagePath);
  }

  generate_save_log_file();
  generate_system_log_file();
}


void generate_save_log_file()
{
  const char* path = current_save_log_path();
  ensure_log_file(path, saveLogHeader);
  set_var_cur_saves_log_file_name(path);
}


void generate_system_log_file()
{
  const char* path = current_system_log_path();
  ensure_log_file(path, systemLogHeader);
  set_var_cur_system_log_file_name(path);
}


void save_in_save_log(const char* time_stamp, double weight, const char* dose_name,
                      double min_weight, double max_weight)
{
  if (!SD_OK) return;

  const char* path = current_save_log_path();

  // Файл мог не создаться раньше (не было карты) - создастся сейчас
  if (!ensure_log_file(path, saveLogHeader)) return;

  File file = SD.open(path, FILE_APPEND);   // APPEND, а не WRITE: WRITE обрежет файл
  if (!file) return;

  char wBuf[24], minBuf[24], maxBuf[24];
  format_weight(weight,     wBuf,   sizeof(wBuf));
  format_weight(min_weight, minBuf, sizeof(minBuf));
  format_weight(max_weight, maxBuf, sizeof(maxBuf));

  write_csv_text(file, time_stamp);
  file.print(',');
  file.print(wBuf);
  file.print(',');
  write_csv_text(file, dose_name);
  file.print(',');
  file.print(minBuf);
  file.print(',');
  file.println(maxBuf);

  file.close();
}


void save_in_system_log(const char* time_stamp, const char* key, const char* message)
{
  if (!SD_OK) return;

  const char* path = current_system_log_path();

  if (!ensure_log_file(path, systemLogHeader)) return;

  File file = SD.open(path, FILE_APPEND);
  if (!file) return;

  write_csv_text(file, time_stamp);
  file.print(',');
  write_csv_text(file, key);
  file.print(',');
  write_csv_text(file, message);
  file.println();

  file.close();
}