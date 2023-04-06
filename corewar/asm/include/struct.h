/*
** EPITECH PROJECT, 2020
** lib
** File description:
** myh
*/

#ifndef STRUCT_H_
#define STRUCT_H_

# define PROG_NAME_LENGTH 128
# define COMMENT_LENGTH 2048
# define COREWAR_EXEC_MAGIC 0xea83f3
# define BIT_SWAP(x) ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) \
    | ((x >> 8) & 0xff00) | ((x << 24) & 0xff000000)
# define MAX_ARGS_NUMBER 4
# define COMMENT_CHAR '#'
# define REGISTER 'r'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
# define REG 1
# define DIR 2
# define IND 4

typedef char args_type_t;
typedef unsigned char bytes[2];

typedef struct op_s
{
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
} op_t;

typedef enum state_s
{
    NAME,
    COMMENT,
    REST,
} state_t;

typedef struct header_s
{
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

typedef struct node_s
{
    struct node_s *next;
    char *line;
    int state;
} node_t;

typedef struct info_s
{
    char *file_name;
    int fd;
    node_t *head;
    header_t header;
    int loop;
    int size;
} info_t;

#endif /* !STRUCT_H */