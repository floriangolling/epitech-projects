##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## lib
##

RM		=		rm -fr

NAME	=		libmy.a

OBJ		=		$(SRC:.c=.o)

SRC		=		my_getnbr.c					\
				my_isneg.c					\
				my_putchar.c				\
				my_put_nbr.c				\
				my_putstr.c					\
				my_revstr.c					\
				my_strcat.c					\
				my_strcmp.c					\
				my_strcpy.c					\
				my_strlen.c					\
				my_strncat.c				\
				my_strncmp.c				\
				my_strncpy.c				\
				my_strstr.c					\
				my_swap.c					\
				my_min.c					\
				on_lowercase.c				\
				on_uppercase.c				\
				my_strdup.c					\
				check_fd.c					\
				my_nbrtoarray.c				\
				my_int_size.c

$(NAME):	$(OBJ)

			ar rc $(NAME) $(OBJ)
			cp libmy.a ../

all:		$(NAME)

clean:
			@$(RM) $(OBJ)
			@$(RM) *~
			@$(RM) *.o

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) ../libmy.a

re:			fclean all
