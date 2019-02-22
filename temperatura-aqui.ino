#include "Common.h"
#include "Connections.h"
#include "Ambient.h"

bool allDone = false;
const unsigned long baudrate = 115200;

void interruptConfigPortal()
{
	Serial.println(F("Configuration Portal button pressed!"));
	ledControl.ToggleOneColor(LED_COLOR::RED, LED_STATUS::ON);
	connections.callOnDemandConfigPortal();
}

bool runMainTasks()
{
	if (!ambient.getAmbientValues())
	{
		Serial.println(LOG_BREAK);
		Serial.print(F("Data aquisition Error!"));
		Serial.println();
		return false;
	}

	char* mqttTopic = parameters.mqttTopic;
	if (!connections.mqttPublishAmbientDataJson(mqttTopic, ambient.ambientData))
	{
		Serial.println(LOG_BREAK);
		Serial.print(F("Mqtt Publish Error!"));
		Serial.println();
		return false;
	}
	return true;
}

void setup() 
{
	Serial.begin(baudrate);
	pinMode(PIN_FLASH, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_FLASH), interruptConfigPortal, FALLING);
	ambient.begin();
	connections.begin(digitalRead(PIN_FLASH) == LOW);
	allDone = runMainTasks();
	if (!allDone)
	{
		Serial.println(F("Restarting ESP..."));
		ESP.restart();
	}
	Serial.println(F("All done! Going to sleep..."));
	ESP.deepSleep(connections.sleep_time);
}

void loop() {}