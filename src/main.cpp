#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// 定義發送的數值
const int signalValue = 2;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Simple Sender");

  // 初始化 LoRa (請確保與接收端頻率一致)
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // 選填：調整發射功率 (2 到 20，預設通常是 17)
  LoRa.setTxPower(20); // 設定最大功率,提升傳輸距離
  // LoRa.setSyncWord(0x12);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending signal: ");
  Serial.println(signalValue);

  // 開始發送封包
  LoRa.beginPacket();
  LoRa.print(signalValue); // 發送數字 1
  LoRa.endPacket();

  // 設定發送頻率為 1Hz (每 1000 毫秒一次)
  delay(1000); 
}