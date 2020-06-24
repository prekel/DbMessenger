#ifndef CONTEXT_H
#define CONTEXT_H

void EnsureCreated();

void DropTables();

int Connect(char* address, char* port, char* dbname, char* dbUser, char* dbUserPassword);

#endif //CONTEXT_H
