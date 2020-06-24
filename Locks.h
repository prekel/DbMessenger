#ifndef LOCKS_H
#define LOCKS_H

void Lock(char* lockname, int dialogId);

void Wait(char* lockname);

void Unlock(char* lockname);

void UnlockAll(int dialogId);

void CreateLocksTrigger();

#endif //LOCKS_H
