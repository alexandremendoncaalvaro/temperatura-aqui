#pragma once
#include "Common.h"

struct AmbientData
{
	float temperature;
	float humidity;
	float pressure;
};

class Parameters {
public:
	char wifiSsid[50] = "";
	char wifiPassword[50] = "";
	char deviceId[50] = "";
	char minutesSleeping[3] = "";
	char mqttServer[50] = "";
	char mqttPort[5] = "";
	char mqttUser[50] = "";
	char mqttPassword[50] = "";
	char mqttTopic[50] = "";
	bool mountFileSystem();
	bool loadParameters();
	bool saveParameters();
	void printParameters();
	bool begin();
private:
};

extern Parameters parameters;