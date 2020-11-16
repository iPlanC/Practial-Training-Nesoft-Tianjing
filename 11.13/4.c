#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct msgbuf {
    long mtype;
    char mtext[100];
} msgbuf;

int main() {
    key_t key = ftok("ftok", 1);
    if (key < 0) perror("ftok");
    int msqid = msgget(key, IPC_CREAT);
    if (msqid < 0) perror("msgget");

    msgbuf msgp = {key, "Hello"};
    msgsnd(msqid, (void *)&msgp, sizeof(msgp.mtext), 0);
    printf("send: %s\n", msgp.mtext);

    return 0;
}