#include "Arduino.h"
#include "MessageDecoder.h"

MessageDecoder::MessageDecoder()
{
	startDelimiter = '{';
	fieldDelimiter = '|';
	endDelimiter = '}';
	numOfParam = 0;
	currentParamIndex = 0;
	started = false;
	ended = false;
	isNumOfParam = false;
	isFieldLength = false;
}

MessageDecoder::~MessageDecoder()
{
	releaseMemory();
}

void MessageDecoder::releaseMemory()
{
	for (byte i = 0; i < numOfParam; i++)
	{
		delete fieldPtr[i];
	}

	delete[] fieldPtr;
	numOfParam = 0;
}

char * MessageDecoder::encode(char **arr, byte numOfParameters)
{
	encoderTotalLength = 2 + numOfParameters;
	currentIndex = 2;

	for (byte i = 0; i < numOfParameters; i++)
	{
		encoderTotalLength += strlen(arr[i]) + 1;
	}

	delete message;
	message = new char[encoderTotalLength + 1];
	message[0] = '{';
	message[1] = char(numOfParameters);
	message[encoderTotalLength - 1] = '}';
	message[encoderTotalLength] = '\0';

	for (byte i = 0; i < numOfParameters; i++)
	{
		message[currentIndex++] = char(strlen(arr[i]));

		for (byte j = 0; j < strlen(arr[i]); j++)
		{
			message[currentIndex++] = arr[i][j];
		}

		if (i + 1 < numOfParameters)
		{
			message[currentIndex++] = '|';
		}
	}

	return message;
}

bool MessageDecoder::decode(char c)
{
	if (started)
	{
		if (c == endDelimiter)
		{
			started = false;
			ended = true;
		}
		else
		{
			if (isNumOfParam)
			{
				isNumOfParam = false;
				isFieldLength = true;
				numOfParam = byte(c);
				currentParamIndex = 0;
				fieldPtr = new char *[numOfParam];
			}
			else if (isFieldLength)
			{
				isFieldLength = false;
				currentFieldIndex = 0;
				fieldLength = byte(c);
				fieldPtr[currentParamIndex] = new char[fieldLength + 1];
				fieldPtr[currentParamIndex][fieldLength] = '\0';
			}
			else if (c == fieldDelimiter)
			{
				isFieldLength = true;
				currentParamIndex++;
			}
			else
			{
				fieldPtr[currentParamIndex][currentFieldIndex++] = c;
			}
		}
	}
	else if (c == startDelimiter)
	{
		started = true;
		ended = false;
		isNumOfParam = true;
		isFieldLength = false;
		releaseMemory();
	}

	return !started && ended;
}

byte MessageDecoder::getFieldsCount()
{
	return numOfParam;
}

char *MessageDecoder::getField(byte index)
{
	return fieldPtr[index];
}