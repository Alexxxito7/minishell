# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghazary <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 12:41:29 by rghazary          #+#    #+#              #
#    Updated: 2025/04/14 12:41:31 by rghazary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c string.c error.c env_list.c input_list.c

NAME = minishell
FLAGS = -Wall -Wextra -Werror -g
LIB_DIR = src/libft
LIB = $(LIB_DIR)/libft.a
LDFLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lncurses
CC = cc

LEAK = valgrind --leak-check=full  --track-origins=yes

OBJ = $(SRC:%.c=%.o)

all: $(LIB) $(NAME)
	rm -f $(OBJ)
$(NAME): $(OBJ) $(LIB)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) $(LDFLAGS)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

d : fclean all
	lldb ./$(NAME)
l : fclean all
	$(LEAK) ./$(NAME)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	./$(NAME)

.PHONY: all clean fclean re
