all:	ncurses sfml sdl

ncurses:
	@make --silent -C Ncurses/

sfml:
	@make --silent -C Sfml/

sdl:
	@make --silent -C Sdl/

clean:
	@make --silent -C Ncurses/ clean
	@make --silent -C Sfml/ clean
	@make --silent -C Sdl/ clean

fclean:
	@make --silent -C Ncurses/ fclean
	@make --silent -C Sfml/ fclean
	@make --silent -C Sdl/ fclean

re:
	@make --silent -C Ncurses/ re
	@make --silent -C Sfml/ re
	@make --silent -C Sdl/ re

.PHONY: all ncurses sfml sdl clean fclean re