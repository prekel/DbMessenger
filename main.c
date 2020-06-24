#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#include <pgtypes.h>
#include <pgtypes_timestamp.h>
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>

#include "IO.h"
#include "Dialogs.h"
#include "Accounts.h"
#include "Context.h"
#include "Messages.h"
#include "Locks.h"


int main(int argc, char** argv)
{
    srand(time(NULL));

    char num[STRING_SIZE];
    InputLine(num, STRING_SIZE);
    int a = ParseInt(num, NULL);

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
    success = res >= 0;
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
        Drop();
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



    if (a == -1)
    {
        EnsureCreated();
    }
    if (a == 0)
    {
        EnsureCreated();
        Register("qwerty", "123456");
        Register("Vladislav213", "123456");
        CreateDialog("Vladislav213", "qwerty");
    }
    if (a == 1)
    {
        Drop();
    }
    if (a == 2)
    {
        Register("Vladislav213", "123456");
    }
    if (a == 2123)
    {
        Register("qwerty", "123456");
    }
    if (a == 3)
    {
        Login("Vladislav213", "1234516");
    }
    if (a == 10)
    {
        Lock("qwerty5", 1);
    }
    if (a == 11)
    {
        Wait("qwerty5");
    }
    if (a == 12)
    {
        Unlock("lockname");
        Unlock("lockname1");
    }
    if (a == 20)
    {
        Lock("qwerty3", 1);
    }
    if (a == 21)
    {
        Wait("qwerty3");
    }
    if (a == 22)
    {
        Unlock("qwerty3");
    }
    if (a == 30)
    {
        CreateLocksTrigger();
    }
    if (a == 40)
    {
        CreateDialog("Vladislav213", "qwerty");
    }
    if (a == 50)
    {
        int c = GetDialogsCount("Vladislav213");
        int* a = (int*) malloc(c * sizeof(int));
        GetDialogs("Vladislav213", a);
        for (int i = 0; i < c; i++)
        {
            printf("%d ", a[i]);
        }
        free(a);
    }
    if (a == 60)
    {
        char name1[1000];
        char name2[1000];

        GetDialogTwoMembers(1, name1, name2);

        printf("%s %s ", name1, name2);
    }
    if (a == 70)
    {
        timestamp t = PGTYPEStimestamp_from_asc("1999-01-08 04:05:06", NULL);
        OutputMessage("daddad", "dasdasdadad", t);
    }
    if (a == 80)
    {
        SendMessage(1, 1, "message5");
    }
    if (a == 90)
    {
        ReceiveMessage(1);
    }
    if (a == 100)
    {
        StartReceivingMessages(1, 5);
    }
    if (a == 110)
    {
        GetPrintMessages(1, -1);
    }
    if (a == 120)
    {
        StartSendingMessages(1, 1);
    }

    return 0;
}
