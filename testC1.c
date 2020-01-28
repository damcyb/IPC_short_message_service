#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/wait.h>

struct message {
    long type;
    char text[100];
};

int main() {

    struct message mess;
    mess.type = 1;
    int send_queue = msgget(0x501, 0666 | IPC_CREAT);
    int receive_queue = msgget(0x500, 066 | IPC_CREAT);

    char option[100];
    struct pollfd myPoll = {STDIN_FILENO, POLLIN | POLLPRI};

    while(1) {
//        if (poll(&myPoll, 1, 1000)) {
//            scanf("%s", option);
//            if(!strcmp(option, "!")) {
//                printf("Write a message: \n");
//                scanf("%s", mess.text);
//                msgsnd(send_queue, &mess, sizeof(mess.text), 0);
//            }
//        }
        printf("Write a message: \n");
        scanf("%s", mess.text);
        msgsnd(send_queue, &mess, sizeof(mess.text), 0);
        printf("Received message: ");
        msgrcv(receive_queue, &mess, sizeof(mess.text), 1, 0);
        printf("%s\n", mess.text);


    }

    return 0;
}