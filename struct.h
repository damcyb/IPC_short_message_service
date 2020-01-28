#include <string.h>

#ifndef STRUCT_H
#define STRUCT_H

#define MESSAGE_MAX_LENGTH 1000

struct Message {
    long type;
    char text[MESSAGE_MAX_LENGTH];
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
    char login[3][50];
    int number;

};
typedef struct LoggedUsers LoggedUsers;

struct pollfd clientPoll = {
        STDIN_FILENO,
        POLLIN | POLLPRI
};

#endif