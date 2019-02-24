#include "Common.h"
#include "Connections.h"
#include "Ambient.h"

bool allDone = false;
const unsigned long baudrate = 115200;

bool runMainTasks()
{
	if (!ambient.getAmbientValues())
	{
		Serial.println(F("--------------------------"));
		Serial.print(F("Data aquisition Error!"));
		Serial.println();
		return false;
	}

	char* mqttTopic = parameters.mqttTopic;
	if (!connections.mqttPublishAmbientDataJson(mqttTopic, ambient.ambientData))
	{
		Serial.println(F("--------------------------"));
		Serial.print(F("Mqtt Publish Error!"));
		Serial.println();
		return false;
	}
	delay(3000);
	return true;
}

void setup() 
{
	Serial.begin(baudrate);
	pinMode(PIN_FLASH, INPUT_PULLUP);
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