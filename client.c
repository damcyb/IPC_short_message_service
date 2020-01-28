#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "struct.h"
#include "clientFunction.h"

#define True 1
#define False 0

//struct message {
//    long type;
//    char text[10];
//};

int main() {

//    struct message mess;
//    mess.type = 1;
//    int send_queue = msgget(0x103, 0666 | IPC_CREAT);
//
//    printf("Write a message: \n");
//    scanf("%s", mess.text);
//    msgsnd(send_queue, &mess, sizeof(mess.text), 0);

    char keyboardInput[50];
    printf("Welcome to IPC chat, enjoy yourself \n");
    printf("Please log in \n");

    while(user.logStatus != 1) {
        LoginUserDetailsRequestModel loggingUser = inputLoginData();
        loginUserRequest(loggingUser);
    }

    showOptions();
    while(True) {
        if (poll(&clientPoll, 1, 1000)) {
            scanf("%s", keyboardInput);

            if(!strcmp(keyboardInput, "1")) {
                showLoggedUsersRequest();
            }

            else if(!strcmp(keyboardInput, "2")) {
                //showUsersInGroupRequest();
            }

            else if(!strcmp(keyboardInput, "3")) {
                showListOfGroupsRequest();
            }

            else if(!strcmp(keyboardInput, "4")) {
                signInToGroupRequest();
            }

//            if(!strcmp(keyboardInput, "9")) {
//                printf("logout\n");
//                //logoutUserRequest();
//            }
        }
    }





    return 0;
}