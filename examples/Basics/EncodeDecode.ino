#include "MessageDecoder.h"

MessageDecoder decoder;
char ** content = new char*[4];
char * output;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Encode message
  content[0] = "123";
  content[1] = "HELLO";
  content[2] = "WORLD";
  content[3] = "TO YOU";

  output = decoder.encode(content, 4);

  // {123|HELLO|WORLD|TO YOU}
  Serial.print("Output: ");
  Serial.println(output);

  // Decode message
  Serial.print("Decoding: ");
  
  for (byte i=0; i<strlen(output); i++) {
    if(decoder.decode(output[i])) {
      for (byte j=0; j<decoder.getFieldsCount(); j++) {
        Serial.println(decoder.getField(j));
      }
    }
  }

  delay(100);
}