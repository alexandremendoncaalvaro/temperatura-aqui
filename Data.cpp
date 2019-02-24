#include "Data.h"

bool Parameters::mountFileSystem()
{
	Serial.print(F("Mounting system file.."));
	if (!SPIFFS.begin())
	{
		Serial.println(F("Fail!"));
		return false;
	}
	Serial.println(F("OK!"));
	return true;
}

bool Parameters::loadParameters()
{
	Serial.print(F("Load parameters from config file..."));

	File configFile = SPIFFS.open("/config.json", "r");

	if (!configFile)
	{
		Serial.println(F("Fail!"));
		return false;
	}

	size_t size = configFile.size();

	if (size > 1024)
	{
		Serial.println(F("The config file is to big!"));
		return false;
	}

	std::unique_ptr<char[]> buffer(new char[size]);

	configFile.readBytes(buffer.get(), size);

	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(buffer.get());

	if (!json.success())
	{
		Serial.println(F("Fail on parse to Json!"));
		return false;
	}

	strcpy(parameters.wifiSsid, json["wifiSsid"]);
	strcpy(parameters.wifiPassword, json["wifiPassword"]);
	strcpy(parameters.deviceId, json["deviceId"]);
	strcpy(parameters.minutesSleeping, json["minutesSleeping"]);
	strcpy(parameters.mqttServer, json["mqttServidor"]);
	strcpy(parameters.mqttPort, json["mqttPorta"]);
	strcpy(parameters.mqttUser, json["mqttUsuario"]);
	strcpy(parameters.mqttPassword, json["mqttPassword"]);
	strcpy(parameters.mqttTopic, json["mqttTopic"]);

	delay(1000);
	Serial.println(F("OK!"));
	configFile.close();
	return true;
}

bool Parameters::saveParameters()
{
	Serial.print(F("Saving parameters..."));

	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();

	json["wifiSsid"] = parameters.wifiSsid;
	json["wifiPassword"] = parameters.wifiPassword;
	json["deviceId"] = parameters.deviceId;
	json["minutesSleeping"] = parameters.minutesSleeping;

	File configFile = SPIFFS.open("/config.json", "w");

	if (!configFile)
	{
		Serial.println("Fail when open config file to write!");
		return false;
	}

	json.printTo(configFile);

	delay(1000);
	Serial.println(F("OK!"));
	configFile.close();
	return true;
}

void Parameters::printParameters()
{
	Serial.println(F("--------------------------"));
	Serial.println(F("CURRENT PARAMETERS:"));

	Serial.print(F("SSID: "));
	Serial.println(parameters.wifiSsid);
	Serial.print(F("Password: "));
	Serial.println(parameters.wifiPassword);

	Serial.print(F("Device ID: "));
	Serial.println(parameters.deviceId);

	Serial.print(F("Minutes Sleeping: "));
	Serial.println(parameters.minutesSleeping);

	Serial.print(F("MQTT Server: "));
	Serial.print(parameters.mqttServer);
	Serial.print(F(":"));
	Serial.println(parameters.mqttPort);

	Serial.print(F("MQTT User: "));
	Serial.println(parameters.mqttUser);
	Serial.print(F("MQTT Password: "));
	Serial.println(parameters.mqttPassword);

	Serial.print(F("MQTT Topic: "));
	Serial.println(parameters.mqttTopic);

	Serial.println(F("--------------------------"));
}

bool Parameters::begin()
{
	if (!parameters.mountFileSystem()) return false;
	if (!parameters.loadParameters()) return false;
	parameters.printParameters();
	return true;
}

Parameters parameters;