#include "MessageDecoder.h"

MessageDecoder decoder;
char ** content = new char*[3];
char * output;

void setup() {
	Serial.begin(9600);
}

void loop() {
	// Encode message
	content[0] = "123";
	content[1] = "HELLO";
	content[2] = "WORLD";

	output = decoder.encode(content);

	Serial.println(output);

	// Decode message
	for (byte i=0; i<strlen(output); i++) {
		if(decoder.decode(output[i])) {
			for (byte j=0; j<decoder.getFieldsCount(); j++) {
				Serial.println(decoder.getField(j));
			}
		}
	}

	delay(5000);
}