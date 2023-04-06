##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

SRC 	=	my_atoi.c			\
			my_itoa.c			\
			my_atof.c			\
			my_ftoa.c			\
			my_putchar.c		\
			my_putstr.c			\
			my_putnbr.c			\
			my_putfloat.c		\
			my_swap.c			\
			my_cpy.c			\
			my_revstr.c			\
			my_strlen.c			\
			my_strcat.c			\
			my_strcmp.c			\
			my_isalpha_num.c	\
			my_occur.c			\
			my_len.c			\
			my_free.c			\
			my_malloc.c			\
			my_base.c			\
			my_dir.c			\
			my_case.c			\
			my_env.c			\
			my_otoo.c			\
			my_ooto.c			\
			my_stack.c			\
			my_count.c			\
			my_getfile.c		\
			my_error.c			\
			my_str.c			\
			my_endian.c

OBJ 	=	$(SRC:.c=.o)

NAME 	= 	libbasics.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp basics.h ./../../include/
	cp basics.h ./../../bonus/include/
	cp $(NAME) ./../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ./../$(NAME)

re: fclean all