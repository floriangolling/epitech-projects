##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

## ========================================================================== ##
PATH_SOURCE_SERVER	=	server/src/
PATH_SOURCE_CLIENT	=	client/src/
## ========================================================================== ##

SOURCE_SERVER			=	main.c 			\
							find_user.c 	\
							init_server.c 	\
							login.c 		\
							logout.c 		\
							parse.c 		\
							prog_args.c 	\
							utils.c 		\
							subscribe.c 	\
							node_user.c 	\
							push_user.c 	\
							unknown.c 		\
							users.c 		\
							list.c 			\
							help.c 			\
							load.c 			\
							send.c 			\
							create.c 		\
							create_team.c 	\
							send_code.c 	\
							use_fct.c 		\
							concat.c 		\
							messages.c 		\
							user.c 			\
							error_code.c 	\
							find_fct.c		\
							utils_create.c 	\
							thread.c 		\
							replies.c 		\
							channels.c 		\
                            lib/str_to_word_array.c  \
							unsubscribe.c	\
                            lib/str_to_array_quote.c  \

SOURCE_CLIENT			= 	main.c				\
							login.c 			\
                            parse.c             \
							channel.c 			\
							reply.c 			\
                            send_message.c      \
							utils.c 			\
							client.c 			\
							thread.c 			\
                            signal_handler.c    \
							unknown.c 			\
							subscribe_message.c	\
							users.c 			\
							messages.c 			\
							other_logout.c 		\
							user.c 				\
							team_created.c 		\
                            ../../server/src/lib/str_to_word_array.c  \


## ========================================================================== ##
INC_PATH=include
## ========================================================================== ##
SRC_CLIENT	=	$(addprefix $(PATH_SOURCE_CLIENT), $(SOURCE_CLIENT))
SRC_SERVER 	= 	$(addprefix $(PATH_SOURCE_SERVER), $(SOURCE_SERVER))
## ========================================================================== ##
NAME_SERVER	=		myteams_server
NAME_CLIENT =		myteams_cli
## ========================================================================== ##
OBJ_SERVER		=		$(SRC_SERVER:.c=.o)
OBJ_CLIENT 		=		$(SRC_CLIENT:.c=.o)
## ========================================================================== ##
CFLAGS	 		+= -Wall -Werror -I./libs/myteams/
LDFLAGS 		+= -L./libs/myteams/ -lmyteams -luuid
## ========================================================================== ##

all:	myteams_server myteams_cli

$(NAME_SERVER):	$(OBJ_SERVER)
		@clang -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS) $(LDFLAGS)
		@echo -e "\n\033[01;38;5;10mCompiling $(NAME_SERVER): Done\033[0;0m"

$(NAME_CLIENT): $(OBJ_CLIENT)
		@clang -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS) $(LDFLAGS)
		@echo -e "\n\033[01;38;5;10mCompiling $(NAME_CLIENT): Done\033[0;0m"

myteams_cli:		$(NAME_CLIENT)

myteams_server:	 	$(NAME_SERVER)

clean:
		@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean:	clean
		@echo "###############################"
		@echo "#Removing lib and vgcore files#"
		@echo "###############################"
		@rm -f $(NAME_SERVER) $(NAME_CLIENT)
		@rm -f vgcore*

re: fclean all

debug:
	@gcc -o $(NAME_CLIENT) $(SRC_CLIENT) $(CFLAGS) $(LDFLAGS) $(DEBUG) -g
	@gcc -o $(NAME_SERVER) $(SRC_SERVER) $(CFLAGS) $(LDFLAGS) $(DEBUG) -g
	@echo "Valgrind compilation: Done"

.PHONY:	all clean fclean re
