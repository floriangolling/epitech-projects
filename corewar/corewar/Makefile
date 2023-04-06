##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

## ========================================================================== ##
PATH_ROOT				=	source/root/
ROOT					=	corewar_root.c					\
							main.c

## ========================================================================== ##
PATH_CORE				=	source/core/
CORE					=	corewar_core.c					\
							core_run.c						\
							core_ref.c

## ========================================================================== ##
PATH_WARRIOR			=	source/core/warrior/
WARRIOR					=	core_warrior.c

## ========================================================================== ##
PATH_MEMORY				=	source/core/memory/
MEMORY					=	core_memory.c					\
							memory_fill.c

## ========================================================================== ##
PATH_PROCESS			=	source/core/process/
PROCESS					=	core_process.c					\
							process_run.c

## ========================================================================== ##
PATH_FETCH				=	source/core/process/fetch/
FETCH					=	process_fetch.c					\
							fetch_merge_4b.c				\
							fetch_merge_2b.c				\
							fetch_particular.c

## ========================================================================== ##
PATH_EXECUTE			=	source/core/process/execute/
EXECUTE					=	process_execute.c				\
							execute_divide.c				\
							execute_param.c					\
							execute_live.c					\
							execute_load.c					\
							execute_store.c					\
							execute_arithmetic.c			\
							execute_operators.c				\
							execute_fork.c

## ========================================================================== ##
PATH_IT					=	source/core/process/it/
IT						=	process_it.c

## ========================================================================== ##
PATH_CYCLE				=	source/core/cycle/
CYCLE					=	core_cycle.c					\
							cycle_verification.c

SRC	=	$(addprefix $(PATH_ROOT), $(ROOT))					\
		$(addprefix $(PATH_CORE), $(CORE))					\
		$(addprefix $(PATH_WARRIOR), $(WARRIOR))			\
		$(addprefix $(PATH_MEMORY), $(MEMORY))				\
		$(addprefix $(PATH_PROCESS), $(PROCESS))			\
		$(addprefix $(PATH_FETCH), $(FETCH))				\
		$(addprefix $(PATH_EXECUTE), $(EXECUTE))			\
		$(addprefix $(PATH_IT), $(IT))						\
		$(addprefix $(PATH_CYCLE), $(CYCLE))

NAME	=		corewar

OBJ		=		$(SRC:.c=.o)

CFLAGS	=		-L ./lib/basics/ -lbasics -I ./include/ -Wall -Werror -lm

$(NAME):	$(OBJ)
		@make	-sC	lib/basics
		@gcc -o $(NAME) $(OBJ) $(CFLAGS)
		@echo -e "\033[01;38;5;10m================Compiling: Done\033[0;0m"

all:	$(NAME)

.PHONY:	clean

clean:
		@rm -f $(OBJ)
		@$(MAKE)	-s	-C	lib/basics fclean

fclean:	clean
		@rm -f $(NAME)
		@rm -f vgcore*

re: fclean all

debug:
	@$(MAKE)	-s	-C	lib/basics
	@gcc -o $(NAME) $(SRC) $(CFLAGS) $(DEBUG) -g
	@echo -e "\033[01;38;5;45m============Valgrind compilation: Done\033[0;0m"