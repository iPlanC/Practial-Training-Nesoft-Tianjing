#include <unistd.h>
#include <stdio.h>

extern char **const environ;

int main() {
    printf("program running");
    execve("./hello.out", NULL, (char **const)environ);
    printf("program done");
}