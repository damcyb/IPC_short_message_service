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
#include <string.h>
#include "struct.h"

#ifndef SERVER_FUNCTION_H
#define SERVER_FUNCTION_H

#define NUMBER_OF_USERS 3
#define NUMBER_OF_GROUPS 3

User user;

void showOptions() {
    printf("Enter a number to do something: \n"
           "1 - SHOW LIST OF LOGGED USERS\n"
           "2 - SHOW ALL USERS IN YOUR GROUP\n"
           "3 - SHOW LIST OF GROUPS\n"
           "4 - SIGN IN TO GROUP\n"
           "5 - SIGN OUT FROM GROUP\n"
           "6 - SEND A MESSAGE TO USER\n"
           "7 - SEND A MESSAGE TO GROUP\n"
           "8 - READ MESSAGES\n"
           "9 - LOGOUT\n");

    //show list of logged users
    //show list of users in group
    //show list of groups
    //sign in to group
    //sign out from group
    //send a message to user
    //send a message to group
    //read messages
    //logout
}

LoginUserDetailsRequestModel inputLoginData() {

    LoginUserDetailsRequestModel userInputData;
    printf("Enter your login \n");
    scanf("%s", userInputData.login);
    printf("Enter your password \n");
    scanf("%s", userInputData.password);

    return userInputData;
}

void loginUserRequest(LoginUserDetailsRequestModel loginUserDetails) {

    int bridge = msgget(0x600, 0666);
    loginUserDetails.type = 2;
    msgsnd(bridge, &loginUserDetails, sizeof(LoginUserDetailsRequestModel) - sizeof(long), 0);
    //sleep(1);
    //User user;
    int received = msgrcv(bridge, &user, sizeof(user) - sizeof(long), 3, 0);
    if(received == -1) {
        perror("Error: ");
    }
    if(user.logStatus == 1) {
        printf("Login successful, welcome back %s \n", user.login);
    }
    else {
        printf("Login unsuccessful, validate input data \n");
    }
}

void showLoggedUsersRequest() {
    int bridge = msgget(0x600, 0);
    user.type = 4;

    msgsnd(bridge, &user, sizeof(user) - sizeof(long), 0);
    sleep(1);
    LoggedUsers loggedUsers;
    int received = msgrcv(bridge, &loggedUsers, sizeof(loggedUsers) - sizeof(long), 5, 0);
    if(received == -1) {
        perror("Error: ");
    }
    else {
        for(int i = 0; i < loggedUsers.number; i++) {
            printf("%s\n", loggedUsers.login[i]);
        }
    }
}

void showListOfGroupsRequest() {
    int bridge = msgget(0x600, 0);
    user.type = 6;

    int send = msgsnd(bridge, &user, sizeof(user) - sizeof(long), 0);
    if(send == -1) {
        perror("Send Error: ");
    }
    sleep(1);
    ExistingGroups existingGroups;
    int received = msgrcv(bridge, &existingGroups, sizeof(existingGroups) - sizeof(long), 7, 0);
    if(received == -1) {
        perror("Error: ");
    }
    else {
        for(int i = 0; i < NUMBER_OF_GROUPS; i++) {
            printf("%s\n", existingGroups.name[i]);
        }
    }
}

#endif