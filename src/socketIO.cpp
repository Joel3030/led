
#include <Arduino.h>
#include "../lib/socketIO.h"

SocketIOclient socketIO;

void socketIOEvent(socketIOmessageType_t type, uint8_t *payload, size_t length)
{

	switch (type)
	{
	case sIOtype_DISCONNECT:
		Serial.printf("[IOc] Disconnected!\n");
		break;
	case sIOtype_CONNECT:
		Serial.printf("[IOc] Connected to url: %s\n", payload);

		// join default namespace (no auto join in Socket.IO V3)
		socketIO.send(sIOtype_CONNECT, "/");
		break;
	case sIOtype_EVENT:
		Serial.printf("[IOc] get event: %s\n", payload);
		break;
	case sIOtype_ACK:
		Serial.printf("[IOc] get ack: %u\n", length);
		hexdump(payload, length);
		break;
	case sIOtype_ERROR:
		Serial.printf("[IOc] get error: %u\n", length);
		hexdump(payload, length);
		break;
	case sIOtype_BINARY_EVENT:
		Serial.printf("[IOc] get binary: %u\n", length);
		hexdump(payload, length);
		break;
	case sIOtype_BINARY_ACK:
		Serial.printf("[IOc] get binary ack: %u\n", length);
		hexdump(payload, length);
		break;
	}
}

void socketIO_setup()
{
	socketIO.begin("10.11.100.100", 8880, "/socket.io/?EIO=4");

	socketIO.onEvent(socketIOEvent);
}