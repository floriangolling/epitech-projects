##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

## ========================================================================== ##
PATH_SOURCE			=	src/
SOURCE				=	main.c					\
						error.c					\
						create_file.c 			\
						find_name.c 			\
						getline.c 				\
						node.c 					\
						open_file.c 			\
						clean_strings.c 		\
						write_header.c 			\
						fcts_one.c 				\
						add_values.c 			\
						main_two.c 				\
						fcts_two.c 				\
						fcts_three.c 			\
						fcts_four.c 			\

## ========================================================================== ##

INC_PATH=include

SRC	=	$(addprefix $(PATH_SOURCE), $(SOURCE))			\

NAME	=		asm

OBJ		=		$(SRC:.c=.o)

CFLAGS	=		-Wall -Werror -I. -I$(INC_PATH) -g

LIBS	=		-L ./lib/my -lmy

OFLAGS	=		-O2

$(NAME):	$(OBJ)
		@$(MAKE)	-s -C	lib/my
		@clang -o $(NAME) $(OBJ) $(LIBS) $(CFLAGS) $(OGLAGS)
		@echo -e "\n\033[01;38;5;10mCompiling : Done\033[0;0m"

all:	$(NAME)

.PHONY:	clean

clean:
		@rm -f $(OBJ)
		@$(MAKE)	-s	-C	lib/my fclean

fclean:	clean
		@echo "###############################"
		@echo "#Removing lib and vgcore files#"
		@echo "###############################"
		@rm -f $(NAME)
		@rm -f vgcore*

re: fclean all

debug:
	@$(MAKE)	-s	-C	lib/my
	@gcc -o $(NAME) $(SRC) $(LIBS) $(CFLAGS) $(DEBUG) -g
	@echo "Valgrind compilation: Done"