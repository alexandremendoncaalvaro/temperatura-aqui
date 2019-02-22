#include "Connections.h"

void Connections::tick()
{
	int state = digitalRead(PIN_LED_BUILTIN);
	digitalWrite(PIN_LED_BUILTIN, !state);
}

void Connections::configModeCallback(WiFiManager *myWifiManager)
{
	Serial.println(LOG_BREAK);
	Serial.println("Entered config mode");
	connections.ticker.attach(0.2, connections.tick);
}

void Connections::saveConfigCallback()
{
	Serial.println(F("Should save config"));
	connections.shouldSaveConfig = true;
}

void Connections::callOnDemandConfigPortal()
{
	wifiConnect(true);
}

void Connections::wifiConnect(bool onDemandPortal)
{
	WiFiManager wifiManager;
	wifiManager.setConfigPortalTimeout(180);
	wifiManager.setSaveConfigCallback(saveConfigCallback);
	wifiManager.setAPCallback(configModeCallback);

	WiFiManagerParameter customDeviceId("deviceId", "Id Dispositivo", parameters.deviceId, sizeof(parameters.deviceId));
	WiFiManagerParameter customMinutesSleeping("minutesSleeping", "Minutos Hibernando", parameters.minutesSleeping, sizeof(parameters.minutesSleeping));

	wifiManager.addParameter(&customDeviceId);
	wifiManager.addParameter(&customMinutesSleeping);

	if (onDemandPortal)
	{
		if (!wifiManager.startConfigPortal("Medidor temperatura", "12345678"))
		{
			Serial.println(F("Failed to connect and hit timeout"));
			Serial.println(F("Going to sleep..."));
			ESP.deepSleep(sleep_time);
		}
	}
	else {
		if (!wifiManager.autoConnect("Medidor temperatura", "12345678"))
		{
			Serial.println(F("Failed to connect and hit timeout"));
			Serial.println(F("Going to sleep..."));
			ESP.deepSleep(sleep_time);
		}
	}

	strcpy(parameters.deviceId, customDeviceId.getValue());
	strcpy(parameters.minutesSleeping, customMinutesSleeping.getValue());

	if (shouldSaveConfig)
	{
		parameters.saveParameters();
	}

	if (WiFi.isConnected()) {
		Serial.print(F("MAC: "));
		Serial.println(WiFi.macAddress());
		Serial.println(LOG_BREAK);
		Serial.println();
		Serial.print(F("WiFi conectado! IP: "));
		Serial.println(WiFi.localIP());
		Serial.println(LOG_BREAK);
		Serial.println();
	}

	connections.ticker.detach();
	ledControl.TurnAllOff();
}

void Connections::begin(bool OnDemandConfigPortal)
{
	shouldSaveConfig = false;

	ledControl.ToggleOneColor(LED_COLOR::RED, LED_STATUS::ON);

	if (!parameters.begin()) return;

	sleep_time = atoi(parameters.minutesSleeping) * MINUTE_US;

	wifiConnect(OnDemandConfigPortal);

	if (!mqttConnect()) return;
}

Connections connections;