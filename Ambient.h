#pragma once
#include "Common.h"
#include "Data.h"
#include "Temperature.h"
#include "BarometricPressure.h"

class Ambient
{
public:
	bool begin();
	bool getAmbientValues();
	AmbientData ambientData;

private:
	Ticker ticker;
	static void tick();
	unsigned long tickCounter;
	const unsigned long maxAttempts = 3;
	const unsigned long secondsToNextCall = 30;
};

extern Ambient ambient;