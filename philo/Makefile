# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:57:36 by mdiallo           #+#    #+#              #
#    Updated: 2021/08/07 19:17:16 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBS = -lpthread

SRC_NAME = eat.c forks.c exit.c init.c messages.c main.c utils.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) ${LIBS} $^ -o $@
	@echo "Executable "$(NAME)" made"

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) || true
	@echo "$(OBJ_PATH) supprimé !"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable de "$(NAME)" supprimé !"

re: fclean all
	@echo "Make re done !"