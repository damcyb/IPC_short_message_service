#include <stdio.h>
#include <stdlib.h>
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

User users[NUMBER_OF_USERS];
Group groups[NUMBER_OF_GROUPS];

void closeQueues(int signal) {
    for (int i = 0; i < 3; i++) {
        msgctl(queue[i], IPC_RMID, NULL);
    }
//    for (int i = 0; i < 16; i++) {
//        int mid = msgget(0x200 + i, 0);
//        msgctl(mid, IPC_RMID, NULL);
//    }
    exit(0);
}

int validateLogin(User user) {
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(!strcmp(user.login, users[i].login) && !strcmp(user.password, users[i].password)) {
            users[i].logStatus = 1;
            return users[i].id;
        }
    }
    return -1;
}

void loginUser() {

    LoginUserDetailsRequestModel loginUserDetailsRequestModel;
    User user;

    int internalRequestQueue = msgget(0x200, 0666);
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
    strcpy(loggedUsers.login, "");
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(users[i].logStatus == 1) {
            strcat(loggedUsers.login, users[i].login);
            strcat(loggedUsers.login, "\n");
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
    int internalRequestQueue = msgget(0x200, 0666);
    int receivedRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 4, IPC_NOWAIT);

    if(receivedRequest == -1) {
        //perror("Error: ");
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
        printf("%s", loggedUsers.login);
    }
}

ExistingGroups createListOfExistingGroups() {
    ExistingGroups existingGroups;
    strcpy(existingGroups.name, "");
    for(int i = 0; i < NUMBER_OF_GROUPS; i++) {
        strcat(existingGroups.name, groups[i].name);
        strcat(existingGroups.name, "\n");
    }
    return existingGroups;

}

void showListOfExistingGroups() {
    User user;
    int internalRequestQueue = msgget(0x200, 0666);
    int receivedRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 6, IPC_NOWAIT);
    if(receivedRequest == -1) {
        //perror("Error: ");
    }
    else {
        ExistingGroups existingGroups;
        existingGroups = createListOfExistingGroups();
        existingGroups.type = 7;
        int send = msgsnd(internalRequestQueue, &existingGroups, sizeof(existingGroups) - sizeof(long), 0);
        if(send == -1) {
            perror("Error ");
        }
        printf("%s", existingGroups.name);
    }
}

int validateSignInToGroup(User user, Group group) {
    if(groups[group.id - 1].members[user.id - 1] == 0) {
        return 1;
    } else {
        return 0;
    }
}

void addUserToGroup(User user, Group group) {
    groups[group.id -1].members[user.id - 1] = 1;
    printf("User %s added to group %s", user.login, groups[group.id - 1].name);
}

void signInToGroup() {
    User user;
    Group group;
    int internalRequestQueue = msgget(0x200, 0666);
    int receivedUserRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 8, IPC_NOWAIT);
    int receivedGroupRequest = msgrcv(internalRequestQueue, &group, sizeof(group) - sizeof(long), 10, IPC_NOWAIT);
    if(receivedUserRequest == -1) {
        //perror("User error: ");
    }
    else if(receivedGroupRequest == -1) {
        //perror("Group error: ");
    }
    else {
        SignInToGroupStatus signInToGroupStatus;
        signInToGroupStatus.type = 11;
        if(validateSignInToGroup(user, group)) {
            addUserToGroup(user, group);
            signInToGroupStatus.result = 1;
        }
        else {
            signInToGroupStatus.result = 0;
        }
        int send = msgsnd(internalRequestQueue, &signInToGroupStatus, sizeof(signInToGroupStatus) - sizeof(long), 0);
        if(send == -1) {
            perror("Error ");
        }
        printf("%d\n", send);
    }
}

int validateSignOutFromGroup(User user, Group group) {
    if(groups[group.id - 1].members[user.id - 1] == 1) {
        return 1;
    } else {
        return 0;
    }
}

void removeUserFromGroup(User user, Group group) {
    groups[group.id -1].members[user.id - 1] = 0;
    printf("User %s removed from group %s", user.login, groups[group.id - 1].name);
}

void signOutFromGroup() {
    User user;
    Group group;
    int internalRequestQueue = msgget(0x200, 0666);
    int receivedUserRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 12, IPC_NOWAIT);
    int receivedGroupRequest = msgrcv(internalRequestQueue, &group, sizeof(group) - sizeof(long), 14, IPC_NOWAIT);
    if(receivedUserRequest == -1) {
        //perror("User error: ");
    }
    else if(receivedGroupRequest == -1) {
        //perror("Group error: ");
    }
    else {
        SignOutFromGroupStatus signOutFromGroupStatus;
        signOutFromGroupStatus.type = 15;
        if(validateSignOutFromGroup(user, group)) {
            removeUserFromGroup(user, group);
            signOutFromGroupStatus.result = 1;
        }
        else {
            signOutFromGroupStatus.result = 0;
        }
        int send = msgsnd(internalRequestQueue, &signOutFromGroupStatus, sizeof(signOutFromGroupStatus) - sizeof(long), 0);
        if(send == -1) {
            perror("Error ");
        }
        printf("%d\n", send);
    }
}

GroupMembers findGroupMembers(int members[NUMBER_OF_USERS]) {
    GroupMembers groupMembers;
    strcpy(groupMembers.login, "");
    int iterator = 0;
    for(int i = 0; i < NUMBER_OF_USERS; i++) {
        if(members[i] == 1) {
            iterator++;
            strcat(groupMembers.login, users[i].login);
            strcat(groupMembers.login, "\n");
        }
    }
    groupMembers.number = iterator;
    return groupMembers;
}

void showUsersInGroup() {
    User user;
    int internalRequestQueue = msgget(0x200, 0666);
    int receivedUserRequest  = msgrcv(internalRequestQueue, &user, sizeof(user) - sizeof(long), 16, IPC_NOWAIT);
    if(receivedUserRequest == -1) {
        //perror("Error: ");
    }
    else {
        GroupMembers groupSportMembers;
        GroupMembers groupPoliticsMembers;
        GroupMembers groupBusinessMembers;

        groupSportMembers = findGroupMembers(groups[0].members);
        groupPoliticsMembers = findGroupMembers(groups[1].members);
        groupBusinessMembers = findGroupMembers(groups[2].members);

        groupSportMembers.type = 17;
        groupPoliticsMembers.type = 18;
        groupBusinessMembers.type = 19;

        msgsnd(internalRequestQueue, &groupSportMembers, sizeof(groupSportMembers) - sizeof(long), 0);
        msgsnd(internalRequestQueue, &groupPoliticsMembers, sizeof(groupPoliticsMembers) - sizeof(long), 0);
        msgsnd(internalRequestQueue, &groupBusinessMembers, sizeof(groupBusinessMembers) - sizeof(long), 0);

        printf("%s", groupSportMembers.login);
        printf("%s", groupPoliticsMembers.login);
        printf("%s", groupBusinessMembers.login);
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

void readGroups() {
    groups[0].id = 1;
    strcpy(groups[0].name, "Sport");
    groups[1].id = 2;
    strcpy(groups[1].name, "Politics");
    groups[2].id = 3;
    strcpy(groups[2].name, "Business");
}

#endif