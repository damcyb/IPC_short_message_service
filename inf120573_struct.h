#include <string.h>

#ifndef STRUCT_H
#define STRUCT_H

#define MESSAGE_MAX_LENGTH 1000
#define NUMBER_OF_USERS 9
#define NUMBER_OF_GROUPS 3

struct Message {
    long type;
    char text[MESSAGE_MAX_LENGTH];
    char senderLogin[100];
    int receiverId;
};
typedef struct Message Message;

struct LoginUserDetailsRequestModel {
    long type;
    char login[100];
    char password[100];
};
typedef struct LoginUserDetailsRequestModel LoginUserDetailsRequestModel;

struct User {
    long type;
    int id;
    char login[100];
    char password[100];
    int logStatus;
};
typedef struct User User;

struct LoggedUsers {
    long type;
    char login[900];
    int number;
};
typedef struct LoggedUsers LoggedUsers;

struct Group {
    long type;
    int id;
    char name[100];
    int members[NUMBER_OF_USERS];
};
typedef struct Group Group;

struct ExistingGroups {
    long type;
    char name[150];
};
typedef struct ExistingGroups ExistingGroups;

struct SignInToGroupStatus {
    long type;
    int result;
};
typedef struct SignInToGroupStatus SignInToGroupStatus;

struct SignOutFromGroupStatus {
    long type;
    int result;
};
typedef struct SignOutFromGroupStatus SignOutFromGroupStatus;

struct GroupMembers {
    long type;
    char login[900];
    int number;
};
typedef struct GroupMembers GroupMembers;

struct UserFoundResponse {
    long type;
    int isFound;
    int id;
};
typedef struct UserFoundResponse UserFoundResponse;

struct GroupFoundResponse {
    long type;
    int isFound;
    int id;
};
typedef struct GroupFoundResponse GroupFoundResponse;

struct pollfd clientPoll = {
        STDIN_FILENO,
        POLLIN | POLLPRI
};

#endif