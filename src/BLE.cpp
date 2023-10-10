/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-10-10 15:06:38
 * @LastEditTime: 2023-10-10 18:51:11
 * @FilePath: /ePaper/src/BLE.cpp
 * @Description: 
 */
#include"BLE.h"
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
String rxload="";
BLECharacteristic *pNotifyCharacteristic;
BLECharacteristic *pReadCharacteristic;

void MyServerCallbacks::onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Connected!");
    }
void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        rxload="";
        for (int i = 0; i < rxValue.length(); i++){
          rxload +=(char)rxValue[i];
        }
      }
    }
void setupBLE(String BLEName){
  const char *ble_name=BLEName.c_str();
  BLEDevice::init(ble_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID); 

  pNotifyCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_NOTIFY,BLECharacteristic::PROPERTY_NOTIFY);
  pNotifyCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_WRITE,BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks()); 

  pReadCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_READ,BLECharacteristic::PROPERTY_READ);

  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}