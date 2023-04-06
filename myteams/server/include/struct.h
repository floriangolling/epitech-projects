/*
** EPITECH PROJECT, 2021
** include_struct
** File description:
** include struct for my_teams
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
#include "../../libs/myteams/logging_server.h"
#include <uuid/uuid.h>
#include "prototype.h"
#include <stdlib.h>
#include <time.h>

#ifndef INCLUDE_SERVER_MYTEAMS_H
#define INCLUDE_SERVER_MYTEAMS_H

enum connect_state {
    LOGIN,
    LOGOUT,
    LOGOUT_BUTKNOWN
};

typedef struct uuid_list_s {
    struct uuid_list_s *next;
    char *uuid;
} uuid_list_t;

typedef struct message_s {
    struct message_s *next;
    char *message;
    char *send_uuid;
    char *received_uuid;
    time_t time;
} message_t;

typedef struct user_s {
    struct user_s *next;
    int socket;
    struct sockaddr_in sin;
    char *uuid;
    char *user_name;
    int is_logged;
    char *context_one;
    char *context_two;
    char *context_three;
} user_t;

typedef struct reply_s {
    struct reply_s *next;
    char *comment_body;
    char *uuid;
    char *user_uuid;
    time_t time;
} reply_t;

typedef struct thread_s {
    struct thread_s *next;
    char *thread_title;
    char *thread_message;
    char *uuid;
    char *user_uuid;
    reply_t *reply_list;
    time_t time;
} thread_t;

typedef struct channel_s {
    struct channel_s *next;
    char *channel_name;
    char *channel_description;
    char *uuid;
    char *user_uuid;
    thread_t *thread_list;
} channel_t;

typedef struct teams_s {
    struct teams_s *next;
    char *team_name;
    char *team_description;
    char *uuid;
    char *user_uuid;
    uuid_list_t *list_uuid;
    channel_t *channel_list;
} teams_t;

typedef struct server_s {
    int socket;
    struct sockaddr_in sin;
    fd_set active;
    fd_set read_fd;
    user_t *user_list;
    teams_t *team_list;
    message_t *list_message;
} server_t;

typedef struct command_s {
    char *cmd;
    void (*func)(int, server_t *, char **);
} command_t;

#endif /* !include */