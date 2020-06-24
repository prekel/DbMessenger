#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>

void EnsureCreated();

void FillSomeData();

void DropTables();

bool Connect(char* address, char* port, char* dbname, char* dbUser, char* dbUserPassword);

void PrintDbVersion();

void Disconnect();

#endif //CONTEXT_H
