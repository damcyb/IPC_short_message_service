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

User users[NUMBER_OF_USERS];

int validateLogin(User user) {
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(!strcmp(user.login, users[i].login) && !strcmp(user.password, users[i].password)) {
            users[i].logStatus = 1;
//            printf("User id: %d\n", users[i].id);
//            printf("Login status: %d\n", users[i].logStatus);
            return users[i].id;
        }
    }
    return -1;
}

void loginUser() {

    LoginUserDetailsRequestModel loginUserDetailsRequestModel;
    User user;

    int internalRequestQueue = msgget(0x500, 0666);
    int receivedRequest  = msgrcv(internalRequestQueue, &loginUserDetailsRequestModel,
            sizeof(loginUserDetailsRequestModel) - sizeof(long), 2, IPC_NOWAIT);
    if(receivedRequest == -1) {
        //perror("Error: ");
    }
    if(receivedRequest != -1) {
        strcpy(user.login, loginUserDetailsRequestModel.login);
        strcpy(user.password, loginUserDetailsRequestModel.password);
        user.type = 3;
        printf("User login: %s\n", user.login);
        printf("User password: %s\n", user.password);
        int validationCode = validateLogin(user);
        if(validationCode != -1) {
            user.logStatus = 1;
            user.id = validationCode;
            printf("User id: %d\n", user.id);
        }
        else {
            user.logStatus = 0;
            printf("Login unsuccessful \n");
        }
        msgsnd(internalRequestQueue, &user, sizeof(user) - sizeof(long), 0);
    }
}

LoggedUsers createListOfLoggedUsers() {
    LoggedUsers loggedUsers;
    int iterator = 0;
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(users[i].logStatus == 1) {
            strcpy(loggedUsers.login[iterator], users[i].login);
            iterator++;
        }
    }
    return loggedUsers;
}

int countNumberOfLoggedUsers() {
    int counter = 0;
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(users[i].logStatus == 1) {
            counter++;
        }
    }
    return counter;
}

void showListOfLoggedUsers() {
    LoggedUsers loggedUsers;
    User user;

    int internalRequestQueue = msgget(0x500, 0666);
    int receivedRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 4, IPC_NOWAIT);

    if(receivedRequest == -1) {
        perror("Error: ");
    }
    else {
        LoggedUsers loggedUsers;
        loggedUsers = createListOfLoggedUsers();
        loggedUsers.number = countNumberOfLoggedUsers();
        loggedUsers.type = 5;
        int send = msgsnd(internalRequestQueue, &loggedUsers, sizeof(loggedUsers) - sizeof(long), 0);
        if(send == -1) {
            perror("Error ");
        }
        printf("%d\n", send);
        for(int i = 0; i < loggedUsers.number; i++) {
            printf("%s\n", loggedUsers.login[i]);
        }
    }
}

void readUserDataFromFile() {
    FILE * stream;
    stream = fopen("users.txt", "r");
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        fscanf(stream, "%d", &users[i].id);
        fscanf(stream, "%s", users[i].login);
        fscanf(stream, "%s", users[i].password);
    }
    fclose(stream);
}

#endif