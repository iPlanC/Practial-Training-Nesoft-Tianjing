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
    int msqid = msgget(IPC_PRIVATE, IPC_CREAT);
    if (msqid < 0) perror("msgget");
    pid_t pid = fork();

    if (pid == 0) {
        msgbuf msgp = {1, "Hello"};
        msgsnd(msqid, (void *)&msgp, sizeof(msgp.mtext), 0);
        printf("send: %s\n", msgp.mtext);
    }

    if (pid > 0) {
        msgbuf msgp;
        msgrcv(msqid, (void *)&msgp, sizeof(msgp.mtext), 1, 0);
        printf("recived: %s\n", msgp.mtext);
        msgctl(msqid, IPC_RMID, NULL);
    }

    if (pid < 0) {
        perror("fork() error");
    }

    return 0;
}