/*
** EPITECH PROJECT, 2020
** lemin Project
** File description:
** include
*/

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "struct.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void find_name_file(char *av, info_t *info);
int asm_prog(char *av);
int error_file(char *av);
char *getnextline(int fd);
int open_files(char *av, info_t *info);
int create_file(info_t *info);
char *concat(char *str1, char *str2);
int reader(info_t *info, int fd);
node_t *create_node(info_t *glob, node_t *node, char *info);
int add_node(info_t *glob, char *info);
void remove_first_spaces(info_t *globale);
void space_padding(info_t *globale);
int find_header_name(info_t *info);
int find_header_comment(info_t *info);
void epur_name(info_t *info);
void epur_comment(info_t *info);
void write_header(info_t *info);
void first_write(info_t *info, char *av);
void value(char *str, info_t *infos);
int reg(int value, info_t *infos);
void live(info_t *infos, char **av);
void add(info_t *infos, char **av);
void sub(info_t *infos, char **av);
void ld(info_t *info, char **av);
char *loop_binary(info_t *info, char **av, char *result);
void swap_bytes(void *value);
void st(info_t *info, char **av);
void and(info_t *info, char **av);
void xor(info_t *info, char **av);
void or(info_t *info, char **av);
void aff(info_t *info, char **av);
void lld(info_t *info, char **av);
void sti(info_t *info, char **av);
void double_v(info_t *info, char **av, int i);
void double_reg(info_t *info, char **av, int i);
void first_reg(info_t *info, char **av, int i);
void last_reg(info_t *info, char **av, int i);
int loop(info_t *info);
int converter(int binary);
char *char_type_first(info_t *info, char **av);

#endif /* !INCLUDE_H_ */
