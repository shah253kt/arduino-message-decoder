#include "Arduino.h"

class MessageDecoder {
  public:
    MessageDecoder();
    ~MessageDecoder();
    char * encode(char ** arr, byte numOfParameters);
    bool decode(char c);
    byte getFieldsCount();
    char *getField(byte index);

  private:
    char startDelimiter, fieldDelimiter, endDelimiter;
    char **fieldPtr, *message;
    byte numOfParam, currentParamIndex, fieldLength, currentFieldIndex;
    bool started, ended, isNumOfParam, isFieldLength;
    byte encoderTotalLength, currentIndex;

    void releaseMemory();
};