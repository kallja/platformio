#include <Arduino.h>

#include "i_gpio.h"

void initOnboardLedGpio()
{
    // Set pin mode
    pinMode(ONBOARD_LED, OUTPUT);
}
