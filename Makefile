SRCS = pipe.c
OBJ = $(SRCS:.c=.o)
NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf
CC = cc

.c.o:
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "DONE!"

all: $(NAME)

clean:

fclean:
	$(RM) $(NAME)

re: fclean all