SRCS = srcs/main.c srcs/initialisation.c srcs/utils.c srcs/activity.c srcs/time.c
SRCS_BONUS	= 
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-pthread
CFLAGS += -Iincludes
NAME = philo
NAME_BONUS =
RM = rm -f
LIBS = #-fsanitize=thread

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS)

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
		$(CC) -o $(NAME_BONUS) $(OBJS_BONUS)

debug: CFLAGS+=-g
debug: re

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all fclean clean re debug bonus