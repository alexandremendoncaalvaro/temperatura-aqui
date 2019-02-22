#include "Common.h"

LedControl::LedControl()
{
	pinMode(PIN_LED_BUILTIN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
	TurnAllOff();
}

void LedControl::TurnAllOff()
{
	digitalWrite(PIN_LED_BUILTIN, LED_STATUS::OFF);
	digitalWrite(PIN_LED_RED, LED_STATUS::OFF);
	digitalWrite(PIN_LED_GREEN, LED_STATUS::OFF);
	digitalWrite(PIN_LED_BLUE, LED_STATUS::OFF);
}

void LedControl::ToggleOneColor(LED_COLOR color, LED_STATUS status)
{
	TurnAllOff();
	digitalWrite(color, status);
}

LedControl ledControl;