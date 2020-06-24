#ifndef LOCKS_H
#define LOCKS_H

void CreateLocksTableTrigger();

void DropLocksTableTrigger();

void CreateLocksTrigger();

void Lock(char* lockname, int dialogId);

void Wait(char* lockname);

void Unlock(char* lockname);

void UnlockDialog(int dialogId);

#endif //LOCKS_H