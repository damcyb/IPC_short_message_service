#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "struct.h"
#include "inf120573_clientFunction.h"

#define True 1
#define False 0

int main() {

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

            if(!strcmp(keyboardInput, "0")) {
                showOptions();
            }

            else if(!strcmp(keyboardInput, "1")) {
                showLoggedUsersRequest();
            }

            else if(!strcmp(keyboardInput, "2")) {
                showUsersInGroupRequest();
            }

            else if(!strcmp(keyboardInput, "3")) {
                showListOfGroupsRequest();
            }

            else if(!strcmp(keyboardInput, "4")) {
                signInToGroupRequest();
            }

            else if(!strcmp(keyboardInput, "5")) {
                signOutFromGroupRequest();
            }

            else if(!strcmp(keyboardInput, "6")) {
                writeMessageToUserRequest();
            }

            else if(!strcmp(keyboardInput, "7")) {
                writeMessageToGroupRequest();
            }

            else if(!strcmp(keyboardInput, "8")) {
                readMessageRequest();
            }

            else if(!strcmp(keyboardInput, "9")) {
                logoutUserRequest();
            }

            else {
                printf("Wrong command, try again\n");
            }
        }
        sleep(1);
    }
    return 0;
}