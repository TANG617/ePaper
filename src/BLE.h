#ifndef BLE_H
#define BLE_H
// BLE
#include <Arduino.h>
#include <BLEDevice.h> 
#include <BLEServer.h> 
#include <BLEUtils.h> 
#include <BLE2902.h> 
#include <String.h> 

extern BLECharacteristic *pNotifyCharacteristic;
extern BLECharacteristic *pReadCharacteristic;
extern bool deviceConnected;
extern uint8_t txValue;
extern long lastMsg;
extern String rxload;

/*為BLE供應商定義指定的 UUID 編號*/
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_WRITE "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_NOTIFY "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_READ "6E400004-B5A3-F393-E0A9-E50E24DCCA9E"

/*為BLE服務器編寫一個Callback函式來管理BLE的連接。*/
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};

/*具有BLE功能的Callback函式。 
 *調用時，移動終端向 ESP32 發送數據時，會將其存儲到 reload 中。
 */
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic);
};

void setupBLE(String BLEName);



#endif