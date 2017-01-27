NAME = lem-in

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = construct1.c ft_strsplit.c func1.c func2.c func3.c func4.c \
	  func5.c func6.c func7.c get_next_line.c solve.c solve2.c \
	  solve3.c solve4.c lem_in.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(SRC) -c 
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm  $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: clean
