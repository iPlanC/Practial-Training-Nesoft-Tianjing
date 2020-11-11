#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = 0;
    char buf[100];

    if (mkfifo("fifo", 666) == 0) {
        printf("reding\n");

        fd = open("fifo", O_RDWR);
        if (fd != -1) {
            while (1) {
                read(fd, buf, sizeof(buf));
                printf("read from fifo: \"%s\"", buf);
                sleep(1);
            }
        }
        else {
            perror("open error");
        }
    }
    else {
        perror("fifo error");
    }
}
