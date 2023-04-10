SRCS = pipe.c pipe_utils.c here_doc.c
OBJ = $(SRCS:.c=.o)
LIBFT = -C ./libft --no-print-directory
NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf
CC = cc

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -Llibft -lft -o $(NAME)
	@echo "DONE!"

#$(LIBFT):
#	@make $(LIBFT)
#	@make bonus $(LIBFT)
#	@make clean $(LIBFT)

all: $(NAME)

target:
	$(MAKE) -C target

clean:

fclean:
	$(RM) $(NAME)

re: fclean all