#pragma once
#include "Common.h"
#include "Data.h"
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>


class Connections {
public:
	bool shouldSaveConfig = false;
	void begin(bool OnDemandConfigPortal = false);
	void callOnDemandConfigPortal();
	bool mqttPublishAmbientDataJson(char* baseTopic, AmbientData ambientData);
	unsigned long sleep_time;
private:
	Ticker ticker;
	WiFiClientSecure client;
	PubSubClient mqttClient = PubSubClient(client);
	void wifiConnect(bool onDemandPortal = false);
	static void saveConfigCallback();
	static void configModeCallback(WiFiManager *myWifiManager);
	static void mqttCallback(char *topic, byte *payload, unsigned int length);
	static void tick();
	bool mqttConnect();
};

extern Connections connections;