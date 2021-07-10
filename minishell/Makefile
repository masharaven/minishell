.PHONY	:	all clean fclean re

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	*.c */*.c

OBJ		=	*.o

HEADERS	=	*.h */*.h

all		:	$(NAME)

$(NAME)	:	$(SRC) $(HEADERS)
	brew reinstall readline
	gcc $(CFLAGS) -c $(SRC)
	gcc $(CFLAGS) -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline -o $(NAME) $(OBJ)

clean	:
	rm -f *.o

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all
