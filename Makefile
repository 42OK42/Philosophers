# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 18:18:03 by okrahl            #+#    #+#              #
#    Updated: 2024/03/25 13:37:47 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS			=	philosophers.c \
					helper.c \
					handle_forks.c \
					init_data.c \
					activities.c \
					update_time.c \
					routine.c \
					clean_up.c \
					handle_one.c \
					main.c

OBJS			=	${SRCS:.c=.o}

HEAD			=	-I includes

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra #-g3 -fsanitize=address

%.o: %.c
	${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(NAME)			:	${OBJS}
					${CC} ${OBJS} ${CFLAGS} -o ${NAME}

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re