#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled.h"

#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED width, in pixels

#define SCREEN_ADDRESS 0x3C // 0x3C for 128x64

// declare SSD1306 display connected to I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 128x64px bitmap array
// made using https://kleki.com/ and https://notisrac.github.io/FileToCArray/
static const unsigned char eishkom[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0x78, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0x78, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x1f, 0x00, 0x00, 0x30, 0x01, 0x60, 0x00,
    0x0f, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x78, 0x3f, 0x00, 0xf0, 0x7b, 0x8f, 0xf0, 0x00,
    0x0f, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x3e, 0x03, 0xf8, 0x7f, 0xff, 0xf8, 0x00,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x79, 0x80, 0x7c, 0xfe, 0x07, 0xf8, 0x7f, 0xff, 0xfc, 0x00,
    0x0f, 0x80, 0x00, 0x00, 0x03, 0xfc, 0x7f, 0xf0, 0x7d, 0xfc, 0x07, 0xfc, 0x7f, 0xff, 0xfe, 0x00,
    0x07, 0x80, 0x38, 0x00, 0x0f, 0xfe, 0x7f, 0xf8, 0x7f, 0xf8, 0x0f, 0xfc, 0x7f, 0xfe, 0x3f, 0x00,
    0x07, 0x80, 0xfc, 0x1c, 0x1f, 0xfe, 0x7f, 0xfc, 0x3f, 0xf0, 0x1f, 0xbe, 0x7e, 0x7c, 0x1f, 0x00,
    0x07, 0xff, 0xfc, 0x3c, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xf8, 0x1f, 0x1e, 0x7e, 0x7c, 0x0f, 0x80,
    0x07, 0xff, 0xfc, 0x3e, 0x3f, 0x00, 0x3f, 0x3e, 0x3f, 0xf8, 0x3e, 0x1f, 0x3e, 0x3c, 0x0f, 0x80,
    0x07, 0xff, 0xf0, 0x3c, 0x3c, 0x00, 0x3e, 0x3e, 0x3f, 0xfc, 0x3e, 0x1f, 0x3e, 0x7c, 0x07, 0xc0,
    0x07, 0xff, 0xc0, 0x3e, 0x3f, 0x80, 0x3e, 0x1e, 0x3e, 0x7c, 0x3e, 0x0f, 0x3e, 0x3e, 0x07, 0xc0,
    0x03, 0xc8, 0x00, 0x3c, 0x3f, 0xfe, 0x3e, 0x1f, 0x3e, 0x3e, 0x3e, 0x0f, 0x3e, 0x3e, 0x03, 0xc0,
    0x03, 0xc0, 0x00, 0x3e, 0x1f, 0xff, 0x3e, 0x0f, 0x3e, 0x1f, 0x3c, 0x0f, 0x3e, 0x3e, 0x03, 0xc0,
    0x03, 0xc0, 0x00, 0x3c, 0x1f, 0xff, 0x3e, 0x0f, 0x3e, 0x1f, 0x3e, 0x1f, 0x1f, 0x3e, 0x03, 0xc0,
    0x03, 0xc0, 0x00, 0x3c, 0x07, 0xff, 0x1e, 0x0f, 0x3e, 0x0f, 0x9e, 0x1f, 0x1f, 0x3e, 0x03, 0xe0,
    0x03, 0xe0, 0x00, 0x3e, 0x00, 0x3f, 0x1e, 0x0f, 0x3e, 0x0f, 0x9f, 0x1f, 0x1f, 0x3e, 0x03, 0xe0,
    0x03, 0xe0, 0x00, 0x1e, 0x01, 0xff, 0x1e, 0x0f, 0x3e, 0x07, 0x9f, 0xbe, 0x1f, 0x1e, 0x01, 0xc0,
    0x03, 0xe0, 0x0f, 0x1e, 0x0f, 0xfe, 0x1f, 0x0f, 0x1e, 0x07, 0x0f, 0xfe, 0x1f, 0x00, 0x00, 0x00,
    0x01, 0xfa, 0xff, 0x1e, 0x0f, 0xf8, 0x1f, 0x0f, 0x1c, 0x00, 0x07, 0xfc, 0x1f, 0x80, 0x00, 0x00,
    0x01, 0xff, 0xff, 0x1f, 0x0f, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x0f, 0x80, 0x00, 0x00,
    0x01, 0xff, 0xff, 0x0e, 0x0f, 0x80, 0x0e, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x0f, 0x80, 0x00, 0x00,
    0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
    0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


static const unsigned char begins[] PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x78, 0x70, 0x00, 0x03, 0x80, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x1f, 0x80, 
  0x7b, 0xfc, 0x00, 0x3f, 0xf0, 0x01, 0xfe, 0xf0, 0x0f, 0xf8, 0x00, 0xf7, 0xf8, 0x00, 0x7f, 0xf0, 
  0x7f, 0xfe, 0x00, 0x7f, 0xf8, 0x03, 0xff, 0xf0, 0x0f, 0xf8, 0x00, 0xff, 0xfc, 0x01, 0xff, 0xf0, 
  0x7f, 0xff, 0x00, 0xff, 0xfc, 0x07, 0xff, 0xf0, 0x0f, 0xf8, 0x00, 0xff, 0xfe, 0x01, 0xff, 0xf0, 
  0x7f, 0x0f, 0x81, 0xf8, 0x7c, 0x07, 0xc3, 0xf0, 0x00, 0x78, 0x00, 0xfc, 0x3e, 0x03, 0xe0, 0x70, 
  0x7e, 0x07, 0x81, 0xe0, 0x1e, 0x0f, 0x81, 0xf0, 0x00, 0x78, 0x00, 0xf8, 0x1e, 0x03, 0xc0, 0x00, 
  0x7c, 0x07, 0xc3, 0xe0, 0x1e, 0x0f, 0x01, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x1e, 0x03, 0xc0, 0x00, 
  0x7c, 0x03, 0xc3, 0xc0, 0x0f, 0x0f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x1f, 0x03, 0xc0, 0x00, 
  0x7c, 0x03, 0xc3, 0xff, 0xff, 0x0f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x03, 0xf0, 0x00, 
  0x78, 0x03, 0xc3, 0xff, 0xff, 0x1f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x01, 0xff, 0x00, 
  0x78, 0x03, 0xc3, 0xff, 0xff, 0x1f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0xe0, 
  0x78, 0x03, 0xc3, 0xc0, 0x00, 0x1f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0x7f, 0xf0, 
  0x78, 0x03, 0xc3, 0xc0, 0x00, 0x1f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0x07, 0xf0, 
  0x7c, 0x03, 0xc3, 0xc0, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xf8, 
  0x7c, 0x03, 0xc3, 0xc0, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x78, 
  0x7c, 0x07, 0xc3, 0xe0, 0x00, 0x0f, 0x01, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x78, 
  0x7e, 0x07, 0x81, 0xe0, 0x02, 0x0f, 0x81, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x02, 0x00, 0x78, 
  0x7f, 0x0f, 0x81, 0xf8, 0x1e, 0x07, 0xe7, 0xf0, 0x00, 0x78, 0x00, 0xf0, 0x0f, 0x03, 0x80, 0xf8, 
  0x7f, 0xff, 0x00, 0xff, 0xfe, 0x03, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0xf0, 0x0f, 0x03, 0xff, 0xf0, 
  0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x01, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0xf0, 0x0f, 0x03, 0xff, 0xe0, 
  0x7b, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 0xfe, 0xf0, 0x1f, 0xff, 0xf0, 0xf0, 0x0f, 0x03, 0xff, 0xc0, 
  0x00, 0x60, 0x00, 0x03, 0x80, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char ends[] PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xf8, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x1f, 0x87, 0xc0, 0x00, 0x1f, 0xe0, 0x00, 
  0x00, 0x1f, 0xfe, 0x00, 0x07, 0xc7, 0xfe, 0x00, 0x00, 0xff, 0xe7, 0xc0, 0x00, 0xff, 0xfe, 0x00, 
  0x00, 0x7f, 0xff, 0x80, 0x0f, 0xdf, 0xff, 0x00, 0x01, 0xff, 0xf7, 0xc0, 0x01, 0xff, 0xff, 0x00, 
  0x00, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0x00, 
  0x01, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0x00, 
  0x03, 0xfe, 0x0f, 0xe0, 0x0f, 0xfe, 0x3f, 0xc0, 0x07, 0xf8, 0xff, 0xc0, 0x0f, 0xf0, 0x1f, 0x00, 
  0x03, 0xf8, 0x07, 0xf0, 0x0f, 0xf8, 0x0f, 0xe0, 0x0f, 0xe0, 0x3f, 0xc0, 0x0f, 0xc0, 0x07, 0x00, 
  0x07, 0xf0, 0x03, 0xf0, 0x0f, 0xf0, 0x07, 0xe0, 0x0f, 0xc0, 0x1f, 0xc0, 0x0f, 0xc0, 0x00, 0x00, 
  0x07, 0xe0, 0x01, 0xf8, 0x0f, 0xe0, 0x07, 0xe0, 0x1f, 0x80, 0x1f, 0xc0, 0x0f, 0xc0, 0x00, 0x00, 
  0x0f, 0xc0, 0x01, 0xf8, 0x0f, 0xe0, 0x07, 0xe0, 0x1f, 0x80, 0x0f, 0xc0, 0x0f, 0xc0, 0x00, 0x00, 
  0x0f, 0xc0, 0x00, 0xf8, 0x0f, 0xc0, 0x07, 0xe0, 0x1f, 0x80, 0x0f, 0xc0, 0x0f, 0xc0, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xc0, 0x07, 0xe0, 0x1f, 0x00, 0x0f, 0xc0, 0x0f, 0xe0, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xfc, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x0f, 0xfe, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xfc, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x07, 0xff, 0xe0, 0x00, 
  0x1f, 0xff, 0xff, 0xfc, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x03, 0xff, 0xfc, 0x00, 
  0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x01, 0xff, 0xfe, 0x00, 
  0x1f, 0x80, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x00, 0x7f, 0xff, 0x00, 
  0x0f, 0x80, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xff, 0x00, 
  0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x3f, 0x00, 0x07, 0xc0, 0x00, 0x00, 0xff, 0x80, 
  0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x1f, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x3f, 0x80, 
  0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x1f, 0x80, 0x0f, 0xc0, 0x00, 0x00, 0x1f, 0x80, 
  0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x1f, 0x80, 0x0f, 0xc0, 0x00, 0x00, 0x0f, 0x80, 
  0x07, 0xe0, 0x00, 0x00, 0x0f, 0xc0, 0x03, 0xe0, 0x1f, 0x80, 0x1f, 0xc0, 0x00, 0x00, 0x1f, 0x80, 
  0x07, 0xf0, 0x00, 0x10, 0x0f, 0xc0, 0x03, 0xe0, 0x0f, 0xc0, 0x1f, 0xc0, 0x08, 0x00, 0x1f, 0x80, 
  0x07, 0xf8, 0x00, 0xf0, 0x0f, 0xc0, 0x03, 0xe0, 0x0f, 0xe0, 0x3f, 0xc0, 0x0e, 0x00, 0x3f, 0x80, 
  0x03, 0xfe, 0x07, 0xf0, 0x0f, 0xc0, 0x03, 0xe0, 0x07, 0xf8, 0xff, 0xc0, 0x0f, 0xc0, 0x7f, 0x80, 
  0x01, 0xff, 0xff, 0xf0, 0x0f, 0xc0, 0x03, 0xe0, 0x07, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x00, 
  0x00, 0xff, 0xff, 0xf0, 0x0f, 0xc0, 0x03, 0xe0, 0x03, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xfe, 0x00, 
  0x00, 0x7f, 0xff, 0xf0, 0x0f, 0xc0, 0x03, 0xe0, 0x01, 0xff, 0xf7, 0xc0, 0x0f, 0xff, 0xfc, 0x00, 
  0x00, 0x1f, 0xff, 0xc0, 0x07, 0xc0, 0x03, 0xe0, 0x00, 0xff, 0xe7, 0xc0, 0x07, 0xff, 0xf0, 0x00, 
  0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x7f, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setupOLED()
{
    // initialise OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println("ERROR: Can't connect to the display.");
    }

    // initial settings
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.setRotation(2);

    // splash screen
    display.drawBitmap(0, 0, eishkom, 128, 64, WHITE);
    display.display();
    delay(1000);
    clearDisplay();

    Serial.println("OLED setup complete.");
}

void displayText(String text, int yLoc, bool overwriteDisplay)
{
    displayText(text, yLoc, 1, false, overwriteDisplay);
}

void displayText(String text, int yLoc, int textSize, bool wrap, bool overwriteDisplay)
{
    display.setTextWrap(wrap);
    display.setTextSize(textSize);
    display.setTextColor(WHITE, BLACK);

    // overwrite previous text
    display.setCursor(0, yLoc);
    for (int i = 0; i <= text.length(); i++)
    {
        display.print(" ");
    }

    // overwrite entrie display
    if (overwriteDisplay)
    {
        clearDisplay();
    }

    // display new text
    display.setCursor(0, yLoc);
    display.print(text);
    display.display();
    display.setTextWrap(false);
}

void clearDisplay()
{
    display.clearDisplay();
}

void displayBegins()
{
    display.drawBitmap(0, 0, begins, 128, 64, WHITE);
    display.display();
}

void displayEnds()
{
    display.drawBitmap(0, 0, ends, 128, 64, WHITE);
    display.display();
}
