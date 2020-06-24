#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "IO.h"
#include "Dialogs.h"
#include "Accounts.h"
#include "Context.h"
#include "Messages.h"
#include "Locks.h"

int main(int argc, char** argv)
{
    srand(time(NULL));
    ConsoleToUtf8();

    char num[STRING_SIZE];
    char address[STRING_SIZE];
    char port[STRING_SIZE];
    char dbname[STRING_SIZE];
    char dbUser[STRING_SIZE];
    char dbPassword[STRING_SIZE];
    char user[STRING_SIZE];
    char password[STRING_SIZE];

    int res = 0;
    bool success;
    printf("Введите IP сервера базы данных [localhost]: ");
    fflush(stdout);
    res = InputLine(address, STRING_SIZE);
    if (res == 0) strcpy(address, "localhost");
    success = success && res >= 0;
    printf("Введите порт сервера базы данных [5432]: ");
    fflush(stdout);
    res = InputLine(port, STRING_SIZE);
    if (res == 0) strcpy(port, "5432");
    success = success && res >= 0;
    printf("Введите название базы данных [dbmessenger]: ");
    fflush(stdout);
    res = InputLine(dbname, STRING_SIZE);
    if (res == 0) strcpy(dbname, "dbmessenger");
    success = success && res >= 0;
    printf("Введите пользователя базы данных [postgres]: ");
    fflush(stdout);
    res = InputLine(dbUser, STRING_SIZE);
    if (res == 0) strcpy(dbUser, "postgres");
    success = success && res >= 0;
    printf("Введите пароль пользователя базы данных [qwerty123]: ");
    fflush(stdout);
    res = InputLine(dbPassword, STRING_SIZE);
    if (res == 0) strcpy(dbPassword, "qwerty123");
    success = success && res >= 0;

    if (!success)
    {
        return 10;
    }

    if (!Connect(address, port, dbname, dbUser, dbPassword))
    {
        return 11;
    }

    printf("Выберите действие:\n");
    printf("1. Войти\n");
    printf("2. Зарегистрироваться\n");
    printf("3. Создать таблицы\n");
    printf("4. Удалить таблицы\n");

    InputLine(num, STRING_SIZE);
    int sucb = 0;
    int b = ParseInt(num, &sucb);
    if (sucb == 0)
    {
        return 13;
    }

    if (b == 3)
    {
        EnsureCreated();
        return 0;
    }
    if (b == 4)
    {
        DropTables();
        return 0;
    }

    printf("Введите логин [User1]: ");
    fflush(stdout);
    res = InputLine(user, STRING_SIZE);
    if (res == 0) strcpy(user, "User1");
    success = success && res >= 0;
    printf("Введите пароль [qwerty]: ");
    fflush(stdout);
    res = InputLine(password, STRING_SIZE);
    if (res == 0) strcpy(password, "qwerty");
    success = success && res >= 0;

    if (!success)
    {
        return 12;
    }

    bool isSignedIn;
    if (b == 1)
    {
        isSignedIn = Login(user, password);
        if (!isSignedIn)
        {
            return 14;
        }
        printf("Выберите действие:\n");
        printf("1. Создать диалог\n");
        printf("2. Вывести диалоги текущего пользователя\n");
        printf("3. Вывести участников диалога\n");
        printf("4. Запросить сообщения\n");
        printf("5. Принимать сообщения\n");
        printf("6. Отправлять сообщения\n");


        InputLine(num, STRING_SIZE);
        int succ = 0;
        int c = ParseInt(num, &succ);
        if (succ == 0)
        {
            return 123;
        }


    }
    if (b == 2)
    {
        Register(user, password);
    }

    return 0;
}
