#ifndef IO_H
#define IO_H

#include <pgtypes_timestamp.h>

int InputLine(char* stringToInput, int maxStringLength);
void OutputMessage(char* author, char* message, timestamp time);

#endif //IO_H
