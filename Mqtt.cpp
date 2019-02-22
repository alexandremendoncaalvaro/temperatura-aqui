#include "Mqtt.h"

void Connections::mqttCallback(char* topic, byte* payload, unsigned int length)
{
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");

	for (int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
	}
}

bool Connections::mqttConnect()
{
	auto attempts = 0;
	auto port = atoi(parameters.mqttPort);

	Serial.println(F("Mqtt connect: "));

	while (!mqttClient.connected() && attempts < 5)
	{
		Serial.print(F("Attempting "));
		Serial.print(attempts + 1);
		Serial.print(F("..."));

		mqttClient.setServer(
			parameters.mqttServer,
			port
		);

		mqttClient.setCallback(mqttCallback);

		if (mqttClient.connect(parameters.deviceId))
		{
			Serial.println(F("connected!"));
			return true;
		}
		else
		{
			Serial.print(F("failed, rc="));
			Serial.print(mqttClient.state());
			Serial.println(F(" try again in 3 seconds"));
			delay(3000);
		}
		attempts++;
	}
	Serial.println(LOG_BREAK);
	return mqttClient.connected();
}

bool Connections::mqttPublishAmbientDataJson(char* baseTopic, AmbientData ambientData)
{
	if (!mqttConnect()) return false;
	auto done = false;
	StaticJsonBuffer<600> jsonBuffer;
	JsonObject& payload = jsonBuffer.createObject();
	char jsonBufferMessage[200];

	payload["t"] = (float)((int)(ambientData.temperature * 10) / 10.0);
	payload["u"] = (float)((int)(ambientData.humidity * 10) / 10.0);
	payload["p"] = (float)((int)(ambientData.pressure * 100) / 100.0);
	payload.printTo(jsonBufferMessage, sizeof(jsonBufferMessage));

	String topic = String(baseTopic);
	done = mqttClient.publish(topic.c_str(), jsonBufferMessage);

	return done;
}