#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct message {
    long msg_type;    
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    key = ftok("msgqueuefile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("Child received: %s\n", msg.msg_text);

        msg.msg_type = 2;
        strcpy(msg.msg_text, "Hello from Child!");
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
    }
    else {
        struct message msg;
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello from Parent!");
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        wait(NULL);
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 2, 0);
        printf("Parent received: %s\n", msg.msg_text);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}

