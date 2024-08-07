/* WiFi scan Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <Arduino.h>
#include <WiFi.h>
#include "BluetoothSerial.h"

#if !CONFIG_AUTOSTART_ARDUINO
void arduinoTask(void *pvParameter)
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.begin(115200);
    delay(100);

    while (1)
    {
        wifiScan();

        // Wait a bit before scanning again
        delay(5000);
    }
}

extern "C" void app_main()
{
    // initialize arduino library before we start the tasks
    initArduino();

    xTaskCreate(&arduinoTask, "arduino_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
#else

void initWifiSta()
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.println("Onboard LED HIGH");
    delay(100);
}

void wifiScan()
{
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
        }
    }
    Serial.println("");
}

void loopWifiScan()
{
    wifiScan();
    // Wait a bit before scanning again
    delay(5000);
}

#define ONBOARD_LED GPIO_NUM_2

void initOnboardLedGpio()
{
    // Set pin mode
    pinMode(ONBOARD_LED, OUTPUT);
}

void blinkOnboardLed()
{
    delay(500);
    Serial.println("Onboard LED HIGH");
    digitalWrite(ONBOARD_LED, HIGH);
    delay(500);
    Serial.println("Onboard LED LOW");
    digitalWrite(ONBOARD_LED, LOW);
}

BluetoothSerial serialBt;
char cmd;

void initBluetooth()
{
    serialBt.begin("Esp-BT");
}

void loopBluetooth()
{
    if (serialBt.available())
    {
        cmd = serialBt.read();
    }

    switch (cmd)
    {
    case '0':
        // LED off
        Serial.println("Onboard LED LOW");
        digitalWrite(ONBOARD_LED, LOW);
        break;
    case '1':
        // LED on
        Serial.println("Onboard LED HIGH");
        digitalWrite(ONBOARD_LED, HIGH);
        break;

    default:
        break;
    }

    delay(50);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("start");
    initOnboardLedGpio();
    initBluetooth();
}

void loop()
{
    loopBluetooth();
}
#endif
