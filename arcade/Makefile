all:	core games graphicals

core:
	@mkdir -p lib/
	@make --silent -C core/

games:
	@mkdir -p lib/
	@make --silent -C GamesLib/Menu/
	@make --silent -C GamesLib/

graphicals:
	@mkdir -p lib/
	@make --silent -C GraphicalLib/

clean:
	@make --silent -C core/ clean
	@make --silent -C GraphicalLib/ clean
	@make --silent -C GamesLib/Menu/ clean
	@make --silent -C GamesLib/ clean

fclean:
	@make --silent -C core/ fclean
	@make --silent -C GraphicalLib/ fclean
	@make --silent -C GamesLib/Menu/ fclean
	@make --silent -C GamesLib/ fclean

re:
	@mkdir -p lib/
	@make --silent -C core/ re
	@make --silent -C GraphicalLib/ re
	@make --silent -C GamesLib/Menu/ re
	@make --silent -C GamesLib/ re

.PHONY: all core clean fclean re