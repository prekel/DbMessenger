#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <stdbool.h>

void CreateAccountsTable();

void DropAccountsTable();

void Register(char* login, char* password);

bool Login(char* login, char* password);

void GetAccountInfo(char* nickname, int* outAccountId, char* outTimeLogin, char* outTimeRegister);

#endif //ACCOUNTS_H
