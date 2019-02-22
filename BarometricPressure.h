#pragma once
#include "Common.h"
#include <BME280I2C.h>
#include <Wire.h>
#include "Data.h"

class BarometricPressure
{
public:
	bool begin();
	AmbientData getCurrentData();
private:
	BME280I2C bme;
};

extern BarometricPressure barometricPressure;