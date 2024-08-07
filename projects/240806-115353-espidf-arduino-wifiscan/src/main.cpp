/* WiFi scan Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "BluetoothSerial.h"
#include "sdkconfig.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <WiFi.h>

#include "i_bluetooth.h"
#include "i_gpio.h"
#include "i_wifi.h"

void blinkOnboardLed()
{
    delay(500);
    Serial.println("Onboard LED HIGH");
    digitalWrite(ONBOARD_LED, HIGH);
    delay(500);
    Serial.println("Onboard LED LOW");
    digitalWrite(ONBOARD_LED, LOW);
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
