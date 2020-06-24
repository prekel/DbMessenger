#ifndef LOCKS_H
#define LOCKS_H

#include <stdbool.h>

void CreateLocksTableTrigger();

void DropLocksTableTrigger();

void CreateLocksTrigger();

void Lock(char* lockname, int dialogId);

void Wait(char* lockname);

void Unlock(char* lockname, bool isUpdateNeeded);

void UnlockDialog(int dialogId);

void UnlockAll();

#endif //LOCKS_H