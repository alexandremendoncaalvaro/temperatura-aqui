#include "Temperature.h"

OneWire oneWire(PIN_ONE_WIRE);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorAddress;

bool Temperature::begin()
{
	sensors.begin();
	Serial.print(F("Locate temperature devices..."));

	auto devicesCount = sensors.getDeviceCount();

	Serial.print(" Found ");
	Serial.print(devicesCount, DEC);
	Serial.println(" devices.");

	if (devicesCount = 0) return false;

	Serial.print(F("Configuring temperature sensor..."));
	if (!sensors.getAddress(sensorAddress, 0))
	{
		Serial.println(F("Error!"));
		return false;
	}
	Serial.println(F("OK!"));

	return true;
}

float Temperature::getCurrentTemperature()
{
	sensors.requestTemperatures();
	float currentTemperature = sensors.getTempC(sensorAddress);
	return currentTemperature;
}

Temperature temperature;