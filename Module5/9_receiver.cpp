//child
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

using namespace std;

struct Message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("msgqueue", 65); // Generate the same key as sender
    int msgid = msgget(key, 0666 | IPC_CREAT); // Get message queue

    Message message;
    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0); // Receive message

    cout << "Received message: " << message.msg_text << endl;

    msgctl(msgid, IPC_RMID, NULL); // Remove message queue after reading

    return 0;
}
