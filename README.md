# Dragino LoRa Basic TX

## 專案概述
展示如何在 Arduino Uno 上搭配 Dragino LoRa Basic TX 模組發送固定數值，代表 LoRa 封包的基礎傳輸流程，也便於快速驗證 TX 端與 RX 端的頻率/功率設定。

## 核心流程
- `setup()` 初始化 Serial（9600）與 LoRa 915 MHz，確認裝置就緒後設定最大發射功率。
- `loop()` 每秒透過 `LoRa.beginPacket()` + `LoRa.print(signalValue)` + `LoRa.endPacket()` 發送封包。
- 使用 `delay(1000)` 讓傳輸頻率穩定在 1 Hz，並在 Serial Monitor 顯示目前數值。

## 硬體清單
- Arduino Uno（或其他 atmelavr board + 3.3V SPI 支援）。
- Dragino LoRa Basic TX (SX1276/77/78) 模組，預設 915 MHz 頻段。
- USB 線連接開發板與 PlatformIO 所在電腦。
- 3.3V 電源、共地與 SPI 接腳正確連線，必要時加入電平轉換器。

## 使用的函式庫
- `LoRa`（sandeepmistry/LoRa@^0.8.0）— 控制 SX127x 封包打包、SPI 通訊與頻率/功率設定。
- `SPI`（Arduino 內建）— 提供底層總線支援，供 LoRa 套件使用。
- `Arduino AVR Core`（framework = arduino）— 建構 `setup()`、`loop()`、Serial 與延遲功能。

## 建置與上傳流程
1. 確認 `platformio.ini` 指向 `env:uno`，並包含 `lib_deps = sandeepmistry/LoRa@^0.8.0`。
2. 以 `pio run` 建構韌體。
3. 使用 `pio run --target upload` 將韌體寫入 Uno。
4. 開啟 Serial Monitor（9600 baud）觀察 `LoRa Simple Sender` 與 `Sending signal` 訊息。

## 操作提醒
- 預設轄入 `signalValue = 2`，可在程式中換成其他整數。
- 若需支援不同頻段，修改 `LoRa.begin(915E6)` 參數並與接收端一致。
- 若 LoRa 初始化失敗，程式會停在 `while (1);`，請檢查天線、供電與 SPI 接線。
- `LoRa.setTxPower(20)` 已設為最大功率，可依需求調整（2~20）。

## 測試建議
- 搭配 Dragino LoRa Basic RX 或其他 LoRa 接收器，確認封包內容與 RSSI。
- 監控 Serial Event 以驗證發送頻率與數值是否穩定。
