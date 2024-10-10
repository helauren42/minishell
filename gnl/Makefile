NAME = gnl.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRCS = get_next_line_bonus.c \
		get_next_line_utils_bonus.c \

OBJS = $(SRCS:.c=.o)

RM = rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

.c.o:
	$(CC) -g $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean all