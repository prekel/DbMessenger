#ifndef MESSAGES_H
#define MESSAGES_H

#define MESSAGE_SIZE 1024

void CreateMessagesTable();

void DropMessagesTable();

void SendMessage(int authorId, int dialogId, char* message);

void StartSendingMessages(int authorId, int dialogId);

void GetPrintMessages(int dialogId, int lastMessages);

void ReceiveMessage(int dialogId);

void StartReceivingMessages(int dialogId, int lastMessages);

#endif //MESSAGES_H
