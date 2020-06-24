#ifndef DIALOGS_H
#define DIALOGS_H

void CreateDialogsTable();

void DropDialogsTable();

void CreateAccountsDialogsTable();

void DropAccountsDialogsTable();

int CreateDialog(char* name1, char* name2);

int GetDialogsCount(char* nickname);

void GetDialogs(char* nickname, int* outArray);

void GetDialogTwoMembers(int dialogId, char* outName1, char* outName2);

#endif //DIALOGS_H
