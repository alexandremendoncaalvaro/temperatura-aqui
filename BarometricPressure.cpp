#include "BarometricPressure.h"

bool BarometricPressure::begin()
{
	Serial.print(F("Configuring BME280 sensor..."));
	Wire.begin();
	if (!bme.begin()) {
		Serial.println(F("Not found!"));
		return false;
	}
	Serial.println(F("OK!"));

	return true;
}

AmbientData BarometricPressure::getCurrentData()
{
	float temp(NAN), hum(NAN), pres(NAN);

	BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
	BME280::PresUnit presUnit(BME280::PresUnit_Pa);

	bme.read(pres, temp, hum, tempUnit, presUnit);

	AmbientData data{
		temp,
		hum,
		pres
	};

	//Serial.print("Temp: ");
	//Serial.print(temp);
	//Serial.print("*" + String(tempUnit == BME280::TempUnit_Celsius ? 'C' : 'F'));
	//Serial.print("\t\tHumidity: ");
	//Serial.print(hum);
	//Serial.print("% RH");
	//Serial.print("\t\tPressure: ");
	//Serial.print(pres);
	//Serial.println(" Pa");

	return data;
}

BarometricPressure barometricPressure;