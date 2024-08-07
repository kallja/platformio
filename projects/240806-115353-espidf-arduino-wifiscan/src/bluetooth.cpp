#include "BluetoothSerial.h"

#include "i_bluetooth.h"
#include "i_gpio.h"

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

        switch (cmd)
        {
        case '0':
            // LED off
            Serial.println("Setting LED GPIO to LOW.");
            digitalWrite(ONBOARD_LED, LOW);
            break;

        case '1':
            // LED on
            Serial.println("Setting LED GPIO to HIGH.");
            digitalWrite(ONBOARD_LED, HIGH);
            break;

            // Ignore some chars
        case '\n': // 0xA
        case '\r': // 0xD
            break;

        default:
            Serial.printf("Unknown command char: '0x%x'.\n", cmd);
            break;
        }
    }

    delay(50);
}
