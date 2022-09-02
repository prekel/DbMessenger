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

#define DEFAULT_ADDRESS "db"
#define DEFAULT_PORT "5432"
#define DEFAULT_DBNAME "demo"
#define DEFAULT_DBUSER "postgres"
#define DEFAULT_DBPASSWORD "qwerty123"
#define DEFAULT_USER "User1"
#define DEFAULT_PASSWORD "qwerty"

int main(int argc, char** argv)
{
    srand(time(NULL));
    SetInputOutputToUtf8();
    SetUnbufferedOutput();

    char num[STRING_SIZE];
    char address[STRING_SIZE];
    char port[STRING_SIZE];
    char dbname[STRING_SIZE];
    char dbUser[STRING_SIZE];
    char dbPassword[STRING_SIZE];
    char user[STRING_SIZE];
    char password[STRING_SIZE];

    bool isSignedIn = false;
    bool success = true;

    int res = 0;
    printf("Введите IP сервера базы данных [" DEFAULT_ADDRESS "]: ");
    res = InputLine(address, STRING_SIZE);
    if (res == 0) strcpy(address, DEFAULT_ADDRESS);
    success = success && res >= 0;
    printf("Введите порт сервера базы данных [" DEFAULT_PORT "]: ");
    res = InputLine(port, STRING_SIZE);
    if (res == 0) strcpy(port, DEFAULT_PORT);
    success = success && res >= 0;
    printf("Введите название базы данных [" DEFAULT_DBNAME "]: ");
    res = InputLine(dbname, STRING_SIZE);
    if (res == 0) strcpy(dbname, DEFAULT_DBNAME);
    success = success && res >= 0;
    printf("Введите пользователя базы данных [" DEFAULT_DBUSER "]: ");
    res = InputLine(dbUser, STRING_SIZE);
    if (res == 0) strcpy(dbUser, DEFAULT_DBUSER);
    success = success && res >= 0;
    printf("Введите пароль пользователя базы данных [" DEFAULT_DBPASSWORD "]: ");
    res = InputLine(dbPassword, STRING_SIZE);
    if (res == 0) strcpy(dbPassword, DEFAULT_DBPASSWORD);
    success = success && res >= 0;

    if (!success)
    {
        fprintf(stderr,
                "Не удалось считать данные для подключения к базе данных\n");
        return 1;
    }

    if (!Connect(address, port, dbname, dbUser, dbPassword))
    {
        fprintf(stderr,
                "Не удалось подключиться к базе данных\n");
        return 1;
    }

    printf("Подключено к ");
    PrintDbVersion();

    printf("Выберите действие:\n");
    printf("1. Войти\n");
    printf("2. Зарегистрироваться\n");
    printf("3. Создать таблицы\n");
    printf("4. Удалить таблицы\n");
    printf("5. Заполнить пустую таблицу некоторыми данными\n");
    printf("6. Завершить все отложенные транзакции\n");

    InputLine(num, STRING_SIZE);
    int sucb = 0;
    int b = ParseInt(num, &sucb);
    if (sucb == 0)
    {
        fprintf(stderr,
                "Не считать номер действия\n");
        Disconnect();
        return 1;
    }

    if (b == 3)
    {
        EnsureCreated();
    }
    else if (b == 4)
    {
        DropTables();
    }
    else if (b == 5)
    {
        FillSomeData();
    }
    else if (b == 6)
    {
        UnlockAll();
    }
    else
    {
        printf("Введите логин [" DEFAULT_USER "]: ");
        res = InputLine(user, STRING_SIZE);
        if (res == 0) strcpy(user, DEFAULT_USER);
        success = success && res >= 0;
        printf("Введите пароль [" DEFAULT_PASSWORD "]: ");
        res = InputLine(password, STRING_SIZE);
        if (res == 0) strcpy(password, DEFAULT_PASSWORD);
        success = success && res >= 0;

        if (!success)
        {
            fprintf(stderr,
                    "Не считать логин или пароль\n");
            Disconnect();
            return 1;
        }

        if (b == 1)
        {
            isSignedIn = Login(user, password);
            if (!isSignedIn)
            {
                fprintf(stderr,
                        "Не правильный логин или пароль\n");
                Disconnect();
                return 1;
            }

            int accountId;
            char loginTime[STRING_SIZE];
            char registerTime[STRING_SIZE];
            GetAccountInfo(user, &accountId, loginTime, registerTime);
            printf("Текущий пользователь:\n");
            printf("Номер: %d\n", accountId);
            printf("Время входа:       %s\n", loginTime);
            printf("Время регистрации: %s\n", registerTime);

            printf("\nВыберите действие:\n");
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
                fprintf(stderr,
                        "Не считать номер действия\n");
                Disconnect();
                return 1;
            }

            if (c == 1)
            {
                printf("Введите имя себеседника: ");
                char name2[STRING_SIZE];
                res = InputLine(name2, STRING_SIZE);
                if (res <= 0)
                {
                    fprintf(stderr,
                            "Не считать имя собеседника\n");
                    Disconnect();
                    return 1;
                }
                int dialogId = CreateDialog(user, name2);
                printf("Создан диалог с номером %d", dialogId);
            }
            else if (c == 2)
            {
                int dialogsCount = GetDialogsCount(user);
                int* dialogs = (int*) malloc(sizeof(int) * dialogsCount);
                GetDialogs(user, dialogs);
                printf("Номера диалогов текущего пользователя: ");
                for (int i = 0; i < dialogsCount; i++)
                {
                    printf("%d ", dialogs[i]);
                }
                printf("\n");
                free(dialogs);
            }
            else if (c == 3)
            {
                printf("Введите номер диалога: ");
                int sucDialogId = 0;
                res = InputLine(num, STRING_SIZE);
                int dialogId = ParseInt(num, &sucDialogId);
                if (res <= 0 || sucDialogId == 0)
                {
                    fprintf(stderr,
                            "Не считать номер диалога\n");
                    Disconnect();
                    return 1;
                }
                char name1[STRING_SIZE];
                char name2[STRING_SIZE];
                GetDialogTwoMembers(dialogId, name1, name2);
                printf("Участники диалога №%d: %s; %s",
                       dialogId, name1, name2);
            }
            else if (c == 4)
            {
                int suc4 = 0;
                printf("Введите номер диалога: ");
                res = InputLine(num, STRING_SIZE);
                int dialogId = ParseInt(num, &suc4);
                printf("Введите, сколько последних сообщений нужно запросить (ничего для всех): ");
                res = InputLine(num, STRING_SIZE);
                int lastMessages = res == 0 ? -1 : ParseInt(num, &suc4);
                if ((res <= 0 || suc4 != 2) && lastMessages != -1)
                {
                    fprintf(stderr,
                            "Не считать номер диалога или сколько сообщений нужно запросить\n");
                    Disconnect();
                    return 1;
                }
                GetPrintMessages(dialogId, lastMessages);
            }
            else if (c == 5)
            {
                int suc5 = 0;
                printf("Введите номер диалога: ");
                res = InputLine(num, STRING_SIZE);
                int dialogId = ParseInt(num, &suc5);
                printf("Введите, сколько последних сообщений нужно запросить (ничего для всех): ");
                res = InputLine(num, STRING_SIZE);
                int lastMessages = res == 0 ? -1 : ParseInt(num, &suc5);
                if ((res <= 0 || suc5 != 2) && lastMessages != -1)
                {
                    fprintf(stderr,
                            "Не считать номер диалога или сколько сообщений нужно запросить\n");
                    Disconnect();
                    return 1;
                }
                StartReceivingMessages(dialogId, lastMessages);
            }
            else if (c == 6)
            {
                int suc6 = 0;
                printf("Введите номер диалога: ");
                res = InputLine(num, STRING_SIZE);
                int dialogId = ParseInt(num, &suc6);
                if (res <= 0 || suc6 != 1)
                {
                    fprintf(stderr,
                            "Не считать номер диалога\n");
                    Disconnect();
                    return 1;
                }
                StartSendingMessages(user, dialogId);
            }
        }
        if (b == 2)
        {
            Register(user, password);
            int accountId;
            char loginTime[STRING_SIZE];
            char registerTime[STRING_SIZE];
            GetAccountInfo(user, &accountId, loginTime, registerTime);
            printf("Текущий пользователь:\n");
            printf("Номер: %d\n", accountId);
            printf("Время входа:       %s\n", loginTime);
            printf("Время регистрации: %s\n", registerTime);
        }
    }

    Disconnect();

    return 0;
}
