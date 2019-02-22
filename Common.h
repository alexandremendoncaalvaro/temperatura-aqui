#pragma once
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Ticker.h>

//Debug
const char LOG_BREAK[] PROGMEM = "--------------------------";

//Time definition
const long SECOND_S = 1;
const long MINUTE_S = SECOND_S * 60;
const long HOUR_S = MINUTE_S * 60;
const long SECOND_MS = 1000;
const long MINUTE_MS = SECOND_MS * 60;
const long HOUR_MS = MINUTE_MS * 60;
const long SECOND_US = 1000000;
const long MINUTE_US = SECOND_US * 60;
const long HOUR_US = MINUTE_US * 60;

//Pin definition
const uint8_t PIN_FLASH = 0;
const uint8_t PIN_LED_BUILTIN = 2;
const uint8_t PIN_ONE_WIRE = D4;
const uint8_t PIN_LED_RED = D5;
const uint8_t PIN_LED_GREEN = D6;
const uint8_t PIN_LED_BLUE = D7;


enum LED_STATUS
{
	ON = LOW,
	OFF = HIGH
};

enum LED_COLOR
{
	RED = PIN_LED_RED,
	GREEN = PIN_LED_GREEN,
	BLUE = PIN_LED_BLUE
};

class LedControl
{
public:
	LedControl();
	void TurnAllOff();
	void ToggleOneColor(LED_COLOR color, LED_STATUS status);
private:

};

extern LedControl ledControl;