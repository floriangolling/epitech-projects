##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

all:
		@make -C ./asm
		@make -C ./corewar

.PHONY:	clean

clean:
		@make clean -C ./asm
		@make clean -C ./corewar

fclean:	clean
		@make fclean -C ./asm
		@make fclean -C ./corewar
		@echo "###############################"
		@echo "#Removing lib and vgcore files#"
		@echo "###############################"

re: fclean all