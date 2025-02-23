//Receiver & Responder)
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
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    Message message;

    while (true) {
        // Receive a message
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        cout << "Process B received: " << message.msg_text << endl;

        if (strcmp(message.msg_text, "exit") == 0) break;

        // Respond with a message
        cout << "Process B: Enter reply: ";
        cin.getline(message.msg_text, sizeof(message.msg_text));

        message.msg_type = 2;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    }

    return 0;
}
