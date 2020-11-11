#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("input some arguments\n");
        exit(EXIT_FAILURE);
    }

    int fd = 0;

    fd = open("fifo", O_WRONLY);
    if (fd != -1) {
        write(fd, argv[1], sizeof(argv[1]));
        printf("write to fifo: \"%s\"", argv[1]);
    }
    return 0;
}