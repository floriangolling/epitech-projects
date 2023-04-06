/*
** EPITECH PROJECT, 2021
** proto
** File description:
** prot
*/

#ifndef INCLUDE_PROTOTYPE_H
#define INCLUDE_PROTOTYPE_H

#include "struct.h"

void other_logout(client_t *client, char **buffer, char *str);
void already_subscribed(client_t *client, char **buffer, char *str);
void unknown_team_uuid(client_t *client, char **buffer, char *str);
void team_subscribed(client_t *client, char **buffer, char *str);
char **my_str_to_word_array(char *str, char separator);
void handle_message(char *buffer, client_t *client);
void signal_handler(int dummy);
void other_login(client_t *client, char **buffer, char *str);
int contain_n(char *str);
void thread_created_me(client_t *client, char **buffer, char *str);
void thread_created(client_t *client, char **buffer, char *str);
void channel_created_me(client_t *client, char **buffer, char *str);
int check_args(char **argv);
int help_arg(void);
void reply_created(client_t *client, char **buffer, char *str);
void reply_created_me(client_t *client, char **buffer, char *str);
void channel_created(client_t *client, char **buffer, char *str);
void unknown_channel(client_t *client, char **buffer, char *str);
void unknown_thread(client_t *client, char **buffer, char *str);
void unsubscribed_to_team(client_t *client, char **buffer, char *str);
int send_message(client_t *client);
void login(client_t *client, char **buffer, char *str);
void logout(client_t *client, char **buffer, char *str);
void unauthorized(client_t *client, char **buffer, char *str);
void users(client_t *client, char **buffer, char *str);
void help(client_t *client, char **buffer, char *str);
void close_client(client_t *client);
void close_signal(client_t *client);
void unknown_uuid(client_t *client, char **buffer, char *str);
void multiple_mess(client_t *client, char **buffer, char *str);
void user_only(client_t *client, char **buffer, char *str);
void team_created(client_t *client, char **buffer, char *str);
void team_created_every_user(client_t *client, char **buffer, char *str);
char *remove_n(char *str);
void send_mess(client_t *client, char **buffer, char *str);
void this_already_exist(client_t *client, char **buffer, char *str);

#endif //INCLUDE_PROTOTYPE_H