#ifndef IO_H
#define IO_H

#include <stdbool.h>

#include <pgtypes_timestamp.h>

#define STRING_SIZE 256

int InputLine(char* stringToInput, int maxStringLength);

void OutputMessage(char* author, char* message, timestamp time);

bool TryParseInt(char* string, int* pResult);

int ParseInt(char* string, int* pSuccessfulCount);

void ConsoleToUtf8();

#endif //IO_H
