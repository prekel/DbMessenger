#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pgtypes_timestamp.h>

#ifdef _MSC_VER
#include <Windows.h>
#elif _WIN32
#include <windows.h>
#endif

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

        if (stringLength == 0 || stringToInput[stringLength - 1] != '\n')
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

    PGTYPESchar_free(timestr);
}

bool TryParseInt(char* string, int* pResult)
{
    size_t length = strlen(string);

    int position;

    int sscanfReturns = sscanf(string, "%d%n", pResult, &position);

    if (position != length || sscanfReturns < 0)
    {
        return false;
    }

    return true;
}

int ParseInt(char* string, int* pSuccessfulCount)
{
    int result;
    bool tryParseInt = TryParseInt(string, &result);
    if (pSuccessfulCount != NULL && tryParseInt)
    {
        (*pSuccessfulCount)++;
    }
    if (!tryParseInt)
    {
        return 0;
    }
    return result;
}

void SetInputOutputToUtf8()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void SetUnbufferedOutput()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}
