#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <Adafruit_MCP23X17.h>

/**
 * LED class
 *
 * This class is used to represent and control an RGB LED.
 *
 * @param redPin The pin connected to the red LED.
 * @param greenPin The pin connected to the green LED.
 * @param bluePin The pin connected to the blue LED.
 * @param mcp The MCP23X17 object used to control the LED.
 */
class LED
{
private:
    int redPin;
    int greenPin;
    int bluePin;
    Adafruit_MCP23X17 mcp;

public:
    LED();
    LED(int redPin, int greenPin, int bluePin);
    void setup();
    void turnOff();
    void turnRed();
    void turnGreen();
    void turnBlue();
};

#endif