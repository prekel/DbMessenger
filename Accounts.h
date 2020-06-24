#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <stdbool.h>

void Register(char* login, char* password);

bool Login(char* login, char* password);

#endif //ACCOUNTS_H
