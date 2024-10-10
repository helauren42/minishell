SRCS	= $(shell find -iname "*.c" -not -path "./libft/*")
NAME	= minishell
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
RM		= rm -f

PUMPKIN_EMOJI = 🎃
SKELETON = 💀
GHOST_EMOJI = 👻
SPIDER = 🕷️
all: ${NAME}

${NAME}: ${SRCS:.c=.o}
	@make -C libft -s
	@${CC} ${FLAGS} -o ${NAME} ${SRCS:.c=.o} ./libft/libft.a ./gnl/gnl.a -lreadline
	@echo "\t\033[38;5;208m$                          _,\033[0m"
	@echo "\t\033[38;5;208m$  I'm  MINIHELL ...       .' /\\033[0m"
	@echo "\t\033[38;5;208m$  of ur 42 Past\"..._ | ;  .-''\"\"-.._\\033[0m"
	@echo "\t\033[38;5;208m$                 _.-'\"\"'._|''_         '.\033[0m"
	@echo "\t\033[38;5;208m$              .'   _.-'   '. '  ''-.    '.\033[0m"
	@echo "\t\033[38;5;208m$            .'   .' ./        \\.    '.    \\033[0m"
	@echo "\t\033[38;5;208m$            |   /  //|        |\\     \\    ;\\033[0m"
	@echo "\t\033[38;5;208m$           ;      ;/_;    |   ;_\\       _  |\\033[0m"
	@echo "\t\033[38;5;208m$          |       L.._\\  /'  /_..J    _.'|  |\\033[0m"
	@echo "\t\033[38;5;208m$          |   ._        |_.\\      __  >| ;  '\\033[0m"
	@echo "\t\033[38;5;208m$           ;   \\'-.   ..___    _.'  '' //  /          _\\033[0m"
	@echo "\t\033[38;5;208m$            \   \ \\\\__/   |/__|  _.-||.'  /       .-.' )\\033[0m"
	@echo "\t\033[38;5;208m$    _        '.  '.\  _/|'-.   _/\\  '   .'      .' /.-'_)\033[0m"
	@echo "\t\033[38;5;208m$   ( '.-.      '.   ''--'  '--'''    _.'        |  ) -'.\\033[0m"
	@echo "\t\033[38;5;208m$  (_'-.\ '.      '-.._,\\__,___,;_/-''         _.'   /-._)\\033[0m"
	@echo "\t\033[38;5;208m$   .'- (  |        .\" / |''-''|  \\  \\      _.7|L /-'\033[0m"
	@echo "\t\033[38;5;208m$  (_.-\\   '._     /  < .'     :  7   '._,-'  |\\_]\\033[0m"
	@echo "\t\033[38;5;208m$       '\\-_/|'._ / .-' ||     '.  >_  /|     \\ /|\\033[0m"
	@echo "\t\033[38;5;208m$         L_.'   '\\  \\  .'      | //\\   ' _,.--''\\033[0m"
	@echo "\t\033[38;5;208m$          \\|         ' |       |; | '._.'\\033[0m"
	@echo "\t\033[38;5;208m$           '---...__/| '       ;| |     and I Am Coming\\033[0m"
	@echo "\t\033[38;5;208m$                   '.7'         . :      To Get YOU!!!\\033[0m"
	@echo "\t\033[38;5;208m$                  / //          |' |\\033[0m"
	@echo "\t\033[38;5;208m$                .'.'|'-._      _>\\  \\033[0m" > /dev/null 2>&1

%.o: %.c
	@echo -n "$(SPIDER)$ "
	@echo -n " "
	@${CC} -g ${FLAGS} -o $@ -c $<

clean:
	@${RM} ${SRCS:.c=.o}
	@make -C libft fclean -s

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all re clean fclean
