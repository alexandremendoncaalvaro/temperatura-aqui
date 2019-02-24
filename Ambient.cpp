#include "Ambient.h"

bool Ambient::begin()
{
	if (!temperature.begin()) return false;
	if (!barometricPressure.begin()) return false;
	return true;
}

void Ambient::tick()
{
	ambient.tickCounter++;
	Serial.print(F("Aquisition nr. "));
	Serial.print(ambient.tickCounter);
	Serial.print(F(" / "));
	Serial.print(ambient.maxAttempts);
	Serial.println(F(" :"));

	AmbientData bmeData = barometricPressure.getCurrentData();

	float currentTemperature = temperature.getCurrentTemperature();

	float currentTemperature2 = bmeData.temperature;
	float currentHumidity = bmeData.humidity;
	float currentPressure = bmeData.pressure;

	Serial.print(F("Dallas: "));
	Serial.print(currentTemperature);
	Serial.println(F(" *C"));

	Serial.print(F("BME:   "));
	Serial.print(currentTemperature2);
	Serial.println(F(" *C"));

	Serial.print(F("BME:   "));
	Serial.print(currentHumidity);
	Serial.println(F(" %"));

	Serial.print(F("BME:   "));
	Serial.print(currentPressure);
	Serial.println(F(" hPa"));

	if (ambient.tickCounter > 1)
	{
		currentTemperature = (ambient.ambientData.temperature + currentTemperature + currentTemperature2) / 3;
		currentHumidity = (ambient.ambientData.humidity + currentHumidity) / 2;
		currentPressure = (ambient.ambientData.pressure + currentPressure) / 2;
	}

	ambient.ambientData = {
			currentTemperature,
			currentHumidity,
			currentPressure
	};

	Serial.print(F("Next aquisition in "));
	Serial.print(ambient.secondsToNextCall);
	Serial.println(F(" seconds"));
	Serial.println(F("--------------------------"));
}

bool Ambient::getAmbientValues()
{
	tickCounter = 0;
	ambient.tick();
	ticker.attach(secondsToNextCall * SECOND_S, ambient.tick);
	while (tickCounter < maxAttempts) {
		yield();
	}
	ticker.detach();

	Serial.println(F("AVERAGE:"));

	Serial.print(F("Temperature: "));
	Serial.print(ambient.ambientData.temperature);
	Serial.println(F(" *C"));

	Serial.print(F("Humidity: "));
	Serial.print(ambient.ambientData.humidity);
	Serial.println(F(" %"));

	Serial.print(F("Pressure: "));
	Serial.print(ambient.ambientData.pressure);
	Serial.println(F(" hPa"));

	Serial.println(F("--------------------------"));

	return true;
}



Ambient ambient;