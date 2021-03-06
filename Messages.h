#ifndef MESSAGES_H
#define MESSAGES_H

#define MESSAGE_SIZE 1024

void CreateMessagesTable();

void DropMessagesTable();

void AddMessage(int authorId, int dialogId, char* message);

void SendMessage(int authorId, int dialogId, char* message);

void StartSendingMessages(char* nickname, int dialogId);

void GetPrintMessages(int dialogId, int lastMessages);

void ReceiveMessage(int dialogId);

void StartReceivingMessages(int dialogId, int lastMessages);

#endif //MESSAGES_H
