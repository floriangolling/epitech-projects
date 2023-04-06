##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

## ========================================================================== ##
PATH_CORE				=	./source/core/
CORE					=	corewar_bonus_core.c					\
							core_run.c						\
							core_ref.c

## ========================================================================== ##
PATH_WARRIOR			=	./source/core/warrior/
WARRIOR					=	core_warrior.c

## ========================================================================== ##
PATH_MEMORY				=	./source/core/memory/
MEMORY					=	core_memory.c					\
							memory_fill.c

## ========================================================================== ##
PATH_PROCESS			=	./source/core/process/
PROCESS					=	core_process.c					\
							process_run.c

## ========================================================================== ##
PATH_FETCH				=	./source/core/process/fetch/
FETCH					=	process_fetch.c					\
							fetch_merge_4b.c				\
							fetch_merge_2b.c				\
							fetch_particular.c

## ========================================================================== ##
PATH_EXECUTE			=	./source/core/process/execute/
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
PATH_IT					=	./source/core/process/it/
IT						=	process_it.c

## ========================================================================== ##
PATH_CYCLE				=	./source/core/cycle/
CYCLE					=	core_cycle.c					\
							cycle_verification.c

## ========================================================================== ##
PATH_BONUS				=	./source/origin/
BONUS					=	main.c							\
							bonus_origin.c

## ========================================================================== ##
PATH_REVEAL				=	./source/reveal/
REVEAL					=	bonus_reveal.c					\
							reveal_board.c

## ========================================================================== ##
PATH_WINDOW				=	./source/reveal/window/
WINDOW					=	reveal_window.c

## ========================================================================== ##
PATH_EVENT				=	./source/reveal/event/
EVENT					=	reveal_event.c

## ========================================================================== ##
PATH_CELL				=	./source/reveal/cell/
CELL					=	reveal_cell.c

## ========================================================================== ##
PATH_INFO				=	./source/reveal/info/
INFO					=	reveal_info.c					\
							info_text.c						\
							info_rectangle.c				\
							info_data.c						\
							info_cycle.c					\
							info_cmd.c						\
							info_arg.c

SRC	=	$(addprefix $(PATH_CORE), $(CORE))					\
		$(addprefix $(PATH_WARRIOR), $(WARRIOR))			\
		$(addprefix $(PATH_MEMORY), $(MEMORY))				\
		$(addprefix $(PATH_PROCESS), $(PROCESS))			\
		$(addprefix $(PATH_FETCH), $(FETCH))				\
		$(addprefix $(PATH_EXECUTE), $(EXECUTE))			\
		$(addprefix $(PATH_IT), $(IT))						\
		$(addprefix $(PATH_CYCLE), $(CYCLE))				\
		$(addprefix $(PATH_BONUS), $(BONUS))				\
		$(addprefix $(PATH_REVEAL), $(REVEAL))				\
		$(addprefix $(PATH_WINDOW), $(WINDOW))				\
		$(addprefix $(PATH_EVENT), $(EVENT))				\
		$(addprefix $(PATH_CELL), $(CELL))					\
		$(addprefix $(PATH_INFO), $(INFO))

NAME	=		vm

OBJ		=		$(SRC:.c=.o)

CFLAGS	=		-L ../lib/basics/ -lbasics -I ./include/ -Wall -Werror -lm

LDFLAGS	= 	-lcsfml-graphics \
			-lcsfml-system \
			-lcsfml-window

$(NAME):	$(OBJ)
		@make	-sC	../lib/basics
		@gcc -o $(NAME) $(OBJ) $(LDFLAGS) $(CFLAGS)
		@echo -e "\033[01;38;5;10m================Compiling: Done\033[0;0m"

all:	$(NAME)

.PHONY:	clean

clean:
		@rm -f $(OBJ)
		@$(MAKE)	-s	-C	../lib/basics fclean

fclean:	clean
		@rm -f $(NAME)
		@rm -f vgcore*

re: fclean all

debug:
	@$(MAKE)	-s	-C	../lib/basics
	@gcc -o $(NAME) $(SRC) $(LDFLAGS) $(CFLAGS) $(DEBUG) -g
	@echo -e "\033[01;38;5;45m============Valgrind compilation: Done\033[0;0m"