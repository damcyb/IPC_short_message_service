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
    int receive_queue = msgget(0x500, 0666 | IPC_CREAT);

    while(1) {
        printf("Read a message: \n");
        msgrcv(receive_queue, &mess, sizeof(mess.text), 1, 0);
        printf("%s\n", mess.text);
        //msgctl(receive_queue, IPC_RMID, NULL); //destroy the message queue
    }

    return 0;
}





