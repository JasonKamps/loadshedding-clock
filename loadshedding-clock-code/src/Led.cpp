#include "Led.h"

// Default constructor
LED::LED()
{
    this->redPin = 0;
    this->greenPin = 0;
    this->bluePin = 0;
    this->mcp = Adafruit_MCP23X17();
}

// Constructor
LED::LED(int redPin, int greenPin, int bluePin)
{
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
}

void LED::setup()
{
    if (!mcp.begin_I2C())
    {
        Serial.println("MCP I2C error.");
    }

    mcp.pinMode(redPin, OUTPUT);
    mcp.pinMode(greenPin, OUTPUT);
    mcp.pinMode(bluePin, OUTPUT);

    Serial.println("LED setup complete.");
}

void LED::turnOff()
{
    mcp.digitalWrite(redPin, LOW);
    mcp.digitalWrite(greenPin, LOW);
    mcp.digitalWrite(bluePin, LOW);
}

void LED::turnRed()
{
    mcp.digitalWrite(redPin, HIGH);
    mcp.digitalWrite(greenPin, LOW);
    mcp.digitalWrite(bluePin, LOW);
}

void LED::turnGreen()
{
    mcp.digitalWrite(redPin, LOW);
    mcp.digitalWrite(greenPin, HIGH);
    mcp.digitalWrite(bluePin, LOW);
}

void LED::turnBlue()
{
    mcp.digitalWrite(redPin, LOW);
    mcp.digitalWrite(greenPin, LOW);
    mcp.digitalWrite(bluePin, HIGH);
}
