# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 15:36:09 by gasroman          #+#    #+#              #
#    Updated: 2024/11/16 20:11:23 by gasroman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================== VARIABLES ================================== #
NAME = philo
CC = cc
RM = rm -rf
MAKE = make --no-print-directory
FLAGS = -Wall -Wextra -Werror -O2 -g -pthread #-fsanitize=thread

# =========================== SOURCES ======================================== #
SRC_PATH = src/
SRC = philo.c parse.c routine.c general_utils.c parse_utils.c
INC =	-I ./inc/

# =========================== DIRECTORIES ==================================== #
DIR_OBJ = $(SRC_PATH)obj/
OBJ = $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ), $(SRC:.c=.d))


# =========================== BOLD COLORS ==================================== #

E = \033[m
R = \033[31m
G = \033[32m
Y = \033[33m
B = \033[34m
P = \033[35m
C = \033[36m
#Font
ligth = \033[1m
dark = \033[2m
italic = \033[3m


# ========================== MAKE RULES ===================================== #
all: dir $(NAME)

-include $(DEP)

dir:
	@mkdir -p $(DIR_OBJ)

print:
	@echo "$(DIR_OBJ)"
	@echo "$(OBJ)"

$(DIR_OBJ)%.o: $(SRC_PATH)%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
	@printf "\r$(G)$<$(E) to $(P)$@$(E)                           "

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -no-pie -o $(NAME) $(INC)
	@echo "\n$(G)$(NAME) succesfully compiled...$(E)"


# ========================== CLEAN   ===================================== #

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(DIR_OBJ)
re: fclean all
.PHONY: clean fclean re
.SILENT:
