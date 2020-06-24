#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pgtypes_timestamp.h>

#ifdef _MSC_VER
#include <Windows.h>
#include <io.h> 
#include <fcntl.h>
#elif _WIN32

#include <windows.h>
#include <io.h>
#include <fcntl.h>

#endif

#ifdef _WIN32

// https://stackoverflow.com/a/38161749
static char* mygets(char* str, int wlen)
{
    int save = _setmode(_fileno(stdin), _O_U16TEXT);
    wchar_t* wstr = malloc(wlen * sizeof(wchar_t));
    fgetws(wstr, wlen, stdin);

    //make UTF-8:
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, 0, 0, 0, 0);
    if (!len) return NULL;
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, 0, 0);
    free(wstr);

    _setmode(_fileno(stdin), save);
    return str;
}

#endif

int InputLine(char* stringToInput, int maxStringLength)
{
    unsigned long stringLength = 0;
    bool isError = false;
    while (true)
    {
#ifdef _WIN32
        char* fgetsReturn = mygets(stringToInput, maxStringLength);
#else
        char* fgetsReturn = fgets(stringToInput, maxStringLength, stdin);
#endif
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
