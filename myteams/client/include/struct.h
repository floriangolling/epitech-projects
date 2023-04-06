/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-jean-baptiste.roesch
** File description:
** struct
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>
#include "../../libs/myteams/logging_client.h"
#include <uuid/uuid.h>
#include "prototype.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE

#ifndef STRUCT_H_
#define STRUCT_H_

static volatile sig_atomic_t catch_signal = 1;

enum connect_state {
    LOGIN,
    LOGOUT,
    LOGOUT_BUTKNOWN
};

typedef struct client_s {
    int socket;
    struct sockaddr_in addr;
    char *uuid;
    char *user_name;
    int is_logged;
    char *message;
} client_t;

typedef struct command_s {
    char *cmd;
    void (*func)(client_t *, char **, char *);
} command_t;

#endif /* !STRUCT_H_ */