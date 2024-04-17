# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 18:18:03 by okrahl            #+#    #+#              #
#    Updated: 2024/04/17 16:43:08 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS FOR PRINTING
GREEN = \033[0;32m
RESET = \033[0m

# DIRECTORIES
OBJ_DIR = obj
SRC_DIR = src
INCL_DIR = incl

# EXECUTABLE NAME
NAME = philo

# SOURCE FILES
SRCS =  philosophers.c \
		helper.c \
		handle_forks.c \
		init_data.c \
		activities.c \
		update_time.c \
		routine.c \
		clean_up.c \
		handle_one.c \
		main.c

# OBJECT FILES
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# COMPILER
CC = gcc

# COMPILATION FLAGS
CFLAGS = -Wall -Wextra -Werror -I$(INCL_DIR)

# COMMANDS
RM = rm -f
MKDIR = mkdir -p

# RULES
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)./$(NAME) is ready!$(RESET)"

fclean : clean
	@$(RM) $(NAME)

clean :
	@$(RM) -r $(OBJ_DIR)

re : fclean all

.PHONY : all clean fclean re