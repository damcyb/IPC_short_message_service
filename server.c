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

int request_queue;
int receive_queue;
int send_queue;
int queue[3];

#include "struct.h"
#include "serverFunction.h"

#define True 1
#define False 0

int main() {

    printf("Server is running...\n");

    request_queue = msgget(0x200, 0666 | IPC_CREAT);
    receive_queue = msgget(0x201, 0666 | IPC_CREAT);
    send_queue = msgget(0x202, 0666 | IPC_CREAT);

    queue[0] = request_queue;
    queue[1] = receive_queue;
    queue[2] = send_queue;

    createIndividualQueues();

    signal(2, closeQueues);

    readUserDataFromFile();
    readGroups();

    while(True) {
        loginUser();
        showListOfLoggedUsers();
        showListOfExistingGroups();
        signInToGroup();
        signOutFromGroup();
        showUsersInGroup();
        userToUserValidator();
        userToUserMessage();
        userToGroupValidator();
        userToGroupMessage();
        logoutUser();
        sleep(1);
    }
//    struct message msg;
//
//    int send_queue = msgget(0x500, 0666 | IPC_CREAT);
//    int receive_queue = msgget(0x501, 0666 | IPC_CREAT);
//    int request_queue = msgget(0x502, 0666 | IPC_CREAT);
//
//    while(1) {
//        msgrcv(receive_queue, &msg, sizeof(msg.text), 1, 0);
//        msgsnd(send_queue, &msg, sizeof(msg.text), 0);
////        printf("Message processing...\n");
//        sleep(1);
//    }

//    struct message myMessage;
//    myMessage.type = 1;

//    if(fork() == 0) {
//        printf("Send a short message\n");
//        scanf("%s", myMessage.text);
////        printf("Wypisano %s\n", myMessage.text);
//        int send = msgsnd(send_queue, &myMessage, sizeof(myMessage.text), 0);
//    }
//    else {
//        wait(NULL);
//        struct message receivedMessage;
//        int receive = msgrcv(send_queue, &receivedMessage, sizeof(receivedMessage.text), 1, 0);
//        printf("Wyslano %s\n", receivedMessage.text);
//    }

    return 0;
}