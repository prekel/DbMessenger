#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pgtypes_timestamp.h>

int InputLine(char* stringToInput, int maxStringLength)
{
    unsigned long stringLength = 0;
    bool isError = false;
    while (true)
    {
        char* fgetsReturn = fgets(stringToInput, maxStringLength, stdin);
        if (fgetsReturn == NULL)
        {
            return -2;
        }

        stringLength = strlen(stringToInput);

        if (stringToInput[stringLength - 1] != '\n')
        {
            isError = true;
        }
        else
        {
            break;
        }
    }
    if (!isError)
    {
        stringToInput[stringLength - 1] = '\0';
        return (int) stringLength - 1;
    }
    return -1;
}


void OutputMessage(char* author, char* message, timestamp time)
{
    char* timestr = PGTYPEStimestamp_to_asc(time);

    printf("%-26s %15s: %s\n", timestr, author, message);
    fflush(stdout);

    PGTYPESchar_free(timestr);
}