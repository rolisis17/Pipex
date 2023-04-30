SRCS = pipe.c pipe_utils.c here_doc.c
OBJ = $(SRCS:.c=.o)
LIBFT = -C ./libft --no-print-directory
LIB = ./libft/libft.a
NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME):$(LIB)
	@$(CC) $(CFLAGS) $(SRCS) -Llibft -lft -o $(NAME)
	@echo "DONE!"

$(LIB):
	@make $(LIBFT)
	@make bonus $(LIBFT)
	@make clean $(LIBFT)


target:
	$(MAKE) -C target

clean:
	@echo "	Nothing to clean;"

fclean:
	@$(RM) $(NAME)
	@make fclean $(LIBFT)
	@echo "if (pipex)\n	rm -rf pipex;\nelse\n	printf('Nothing to clean.');"

re: fclean all