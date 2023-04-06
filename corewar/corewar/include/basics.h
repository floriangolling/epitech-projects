/*
** EPITECH PROJECT, 2020
** lib
** File description:
** basics
*/

#ifndef BASICS_H_
#define BASICS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

/************\
*   BASICS   *
\************/

void my_putchar(char c);
//swap int
void my_swapi(int *a, int *b);
//swap float
void my_swapf(float *a, float *b);
//swap double
void my_swapd(double *a, double *b);
// reverse a string
void my_revstr(char *str);

////////////////////////////////////////////////////////////
/// \brief free management
/// \param one = 1 (str maybe to free)
/// \param two = 3 (str maybe to free)
/// \param three = 5 (str maybe to free)
/// \param release have to add the number
/// to choose which one to free
////////////////////////////////////////////////////////////
void my_free(char *one, char *two, char *three, int release);
//free a double array
void my_free_oo(char **oo);
//allow to free any double array type
void my_free_typoo(void **oo);

////////////////////////////////////////////////////////////
/// \brief put str with color
/// \param str string you want to display
/// \param color choose which color
/// \param option different options
/// \param release free or not free
///////////////////////////////////////////////////////////
int my_intlen(int nb);
int my_occur(char *str, char element);
int my_putnbr(int nb);
//put a float
void my_putfloat(float nb);

int my_putstr(char *str);
//put and then free the string
int nl_putstr(char *str);
//put a string on the error output
void my_putrstr(char *str, int release);
//put a string in color or with an option
void my_putcstr(char *str, char *color, int option, int release);
//put a double array
void my_putoo(char **oo);


int my_strlen(char const *str);
//len between the start and the first occurence of character
int my_limlen(char *str, char lim, int release);
//len between the start and when the nb of character is reach
int my_nlimlen(char *str, char lim, int occurence, int release);
//len between the first occurence of the character start and the end
int my_stlen(char *str, char start, int release);
//len of a double array
int my_oolen(char **oo);


int my_atoi(char const *str);
//atoii but free the str
int nl_atoi(char *str);
//convert a decimal nb in string into a float
float my_atof(char *str, int release);
//convert float to char *
char *my_ftoa(float nb);
//convert float to char * without malloc
char *nm_ftoa(char *number, float nb);
//convert int to char *
char *my_itoa(int nb);
//convert int to char * without malloc
char *nm_itoa(char in[10], int nb);

int my_strcmp(char *s1, char *s2, int release);
int my_cmp(char *s1, char *s2, int release);
int my_ncmp(char *s1, char *s2, int n, int release);
int my_strcmp_low(char *s1, char *s2, int release);

int my_isalpha_num(char *str);
//check if all the character of a string is inside a given range
int my_isin(char *str, char open, char close, int release);
int my_isnum(char character);
int my_isalpha(char character, char open, char close);
int my_isinstr(char c, char *str, int release);

void my_putbase(int nb, char *base, int len_base);
char *my_ch_base(int nb, char *base);

char *my_intchar(int nb);

char *my_cpy(char *src, int release);
char *my_cpy_st(char *str, char start, int release);
char *my_cpy_lim(char *original, char lim, int release);
//copy a double array
char **my_oocpy(char **oo);

//cat two string
char *my_cat(char *one, char *two, int release);
//cat two string without malloc
char *nm_cat(char *sum, char *one, char *two, int release);
//cat two string and add a character between
char *my_cat_in(char *bread, char *sausage, char ketchup, int release);
//cat three string
char *my_catside(char *one, char *two, char *three, int release);


char **my_malloc_db(int height, int width);
unsigned char **my_malloc_udb(int height, int width);
int **my_malloc_db_int(int height, int width);
//allow to malloc any type in double array
//size_db is the sizeof(type *) and size equal to sizeof(type)
void **my_malloc_type(int height, int width, int size_db, int size);


//count nb of file in a folder
int my_nbfile(char *path, int release);
//check if is a dir
int my_isdir(char *path, int release);
//count nb of folder inside a folder
int my_nbdir(char *path, int release);

void my_lowcase(char *str);
void my_upcase(char *str);

char *my_getenv(char *term, char **env);

//count nb of character in a string
int my_count_co(char *str, char character);
//count nb of character in a double array
int my_count_coo(char **str, char character);
//count nb of character inside an range
int my_count_too(char **str, char open, char close);


typedef struct otoo_s
{
    int e;
    int o;
    int i;
    int nb_part;
    int *space;
    char **otoo;
}otoo_t;
//change an string in a double array with two separator
char **my_otoo(char *str, char sep_one, char sep_two, int *nb_of_part);
//change a double array into a string and add a character between each line
char *my_ooto(char **oo, char ramification);


//add a string at the end of a double array
char **my_push(char **oo, char *o);
//remove a string of a double array
char **my_pop(char **oo, char *o);

//get a file with the stat function
char **my_getfile_stat(char *path, int release);

//put an error message on the error output and return 1
int error(char *str);
//put an error message on the error output and return -1
int errorc(char *str);
//put an error message on the error output and return 84
int errorm(char *str);
//put an error message on the error output and return null
void *errorn(char *str);
//put message on variable output and return value given
int info(char *str, int output, int return_value);

//check if a str contain an other str
int my_str_isin(char *base, char *inside, int release);

//change a nb in big_endian value
void big_endian(int *nb);

/************\
*   COLORS   *
\************/

#define RED ";31m"

#define GREEN ";32m"

#define BLUE ";34m"

#define YELLOW ";33m"

#define MAGENTA ";35m"

#define CYAN ";36m"

#define WHITE ";37m"

#define RESET "\033[0m"

#endif /* !BASICS_H_ */