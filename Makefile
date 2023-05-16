NAME = philo

SRCS = main.c utils.c init.c routine.c start.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

${NAME}:
		${CC} ${CFLAGS} -pthread ${SRCS} -lpthread -o ${NAME}

all:	${NAME}

clean:
		${RM} -f ${OBJS}

fclean:	clean
		${RM} -f ${NAME}

re:		fclean ${MAKE} ${NAME}

.PHONY: all clean fclean re
