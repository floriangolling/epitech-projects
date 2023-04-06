/*
** EPITECH PROJECT, 2021
** proto
** File description:
** proto
*/

#ifndef INCLUDE_PROTOTYPE_H
#define INCLUDE_PROTOTYPE_H

#include "struct.h"

int check_contexts(user_t *user, server_t *srv, char **buff);
void next_create_conditions(int fd, server_t *srv, char **buff, user_t *user);
void print_channel_event(channel_t *channel, server_t *srv, int fd,
                                                                teams_t *team);
void add_node_channel(teams_t *team, int fd, char **buff, server_t *srv);
void create_channel(int fd, server_t *srv, char **buff, user_t *user);
void create_thread(int fd, server_t *srv, char **buff, user_t *user);
void create_replies(int fd, server_t *srv, char **buff, user_t *user);
void create_rest(int fd, server_t *srv, char **buff);
teams_t *find_team_by_uuid(server_t *srv, char *uuid);
int check_if_atleast_login(server_t *srv, char *uuid);
int count_uuid(server_t *srv, char *uuid);
void messages_fct(int fd, server_t *srv, char **buff);
void send_fct(int fd, server_t *srv, char **buff);
void check_for_users(int fd, user_t *user, char **buff, server_t *srv);
void load_user(server_t *srv, char **buffer);
int check_length_login(char *buff, int fd);
char *concat_in_chain(message_t *mess, char *str, char *buffer);
char *remove_n(char *str);
void send_unknown_uuid(int fd, char *uuid);
void send_user(int fd, char *user_name, char *uuid, server_t *srv);
void send_code(int fd);
teams_t *find_team_name(server_t *srv, char *name);
void init_user(server_t *srv);
void user_fct(int fd, server_t *srv, char **buff);
void help_fct(int fd, server_t *srv, char **buff);
void list_fct(int fd, server_t *srv, char **buff);
void unknown_command(int fd, server_t *srv, char **buffer);
char **my_str_to_word_array(char *str, char separator);
void login_fct(int fd, server_t *srv, char **buff);
void create_fct(int fd, server_t *srv, char **buff);
void create_team_fct(int fd, server_t *srv, char **buff);
void logout_fct(int fd, server_t *srv, char **buff);
void remove_node_ghettobyfd(user_t *user, server_t *srv);
char *check_double_quote(char *arg);
char **clean_command(char **tab);
void already_exist(int fd);
user_t *find_user_by_uuid(char *uuid, server_t *srv);
int check_string(char *buffer);
int tab_len(char **tab);
int check_only_space(char *str);
char *generate_uuid(void);
void use_fct(int fd, server_t *srv, char **buff);
user_t *find_user_name(char *str, server_t *srv);
user_t *find_user_by_fd(int fd, server_t *srv);
void login_fct(int fd, server_t *srv, char **buff);
void set_user(int fd, server_t *srv, char *buff, user_t *user);
void logout_fct(int fd, server_t *srv, char **buff);
int handle_message(int fd, server_t *srv);
int print_help(void);
int check_port(char *port);
int check_args(int ac, char **av, server_t *srv);
int init_server(server_t *srv, char *port);
void create_new_user(int fd, server_t *srv, char *str, char *uuid);
int push_client(server_t *srv, int fd);
void remove_node_ghettobyfd(user_t *user, server_t *srv);
int check_logout(int i, server_t *srv, user_t *user);
void unauthorized(int fd);
void users_fct(int fd, server_t *srv, char **buff);
void not_enough_arguments(int fd);
void too_long_body(int fd);
void subscribe_fct(int fd, server_t *srv, char **buff);
void unsubscribe_fct(int fd, server_t *srv, char **buff);
int is_there_already(teams_t *team, char *uuid);
channel_t *find_channel_uuid(server_t *srv, char *uuid, teams_t *team);
thread_t *find_thread_uuid(server_t *srv, char *uuid, teams_t *team,
                                                        channel_t *channel);
#endif //INCLUDE_PROTOTYPE_H