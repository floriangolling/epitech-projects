all:	highscore howtoplay pacman snake

highscore:
	@make --silent -C Highscore/

howtoplay:
	@make --silent -C HowToPlay/

pacman:
	@make --silent -C Pacman/

snake:
	@make --silent -C Snake/

clean:
	@make --silent -C Pacman/ clean
	@make --silent -C Snake/ clean
	@make --silent -C HowToPlay/ clean
	@make --silent -C Highscore/ clean

fclean:
	@make --silent -C Pacman/ fclean
	@make --silent -C Snake/ fclean
	@make --silent -C HowToPlay/ fclean
	@make --silent -C Highscore/ fclean

re:
	@make --silent -C Pacman/ re
	@make --silent -C Snake/ re
	@make --silent -C HowToPlay/ re
	@make --silent -C Highscore/ re

.PHONY: all highscore howtoplay pacman snake clean fclean re