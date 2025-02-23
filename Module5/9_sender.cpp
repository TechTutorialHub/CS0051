//message queue (parent)
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
    key_t key = ftok("msgqueue", 65); // Generate unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue

    Message message;
    message.msg_type = 1; // Type 1 message

    cout << "Enter message to send: ";
    cin.getline(message.msg_text, sizeof(message.msg_text));

    msgsnd(msgid, &message, sizeof(message.msg_text), 0); // Send message
    cout << "Message sent: " << message.msg_text << endl;

    return 0;
}
