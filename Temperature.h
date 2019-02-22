#pragma once
#include "Common.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Temperature
{
public:
	bool begin();
	float getCurrentTemperature();

private:

};

extern Temperature temperature;