//Process A (Sender & Receiver)

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
        // Send a message
        cout << "Process A: Enter message (type 'exit' to quit): ";
        cin.getline(message.msg_text, sizeof(message.msg_text));
        
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        if (strcmp(message.msg_text, "exit") == 0) break;

        // Receive a message
        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);
        cout << "Process A received: " << message.msg_text << endl;
    }

    msgctl(msgid, IPC_RMID, NULL); // Remove queue when done
    return 0;
}
