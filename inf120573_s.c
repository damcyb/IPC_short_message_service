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

#include "inf120573_struct.h"
#include "inf120573_serverFunction.h"

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
    return 0;
}