NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS =	srcs/main.c \
		srcs/philo/lifecycle.c \
		srcs/philo/monitor_routine.c \
		srcs/philo/routine.c \
		srcs/utils/specific_error_case.c \
		srcs/utils/ft_ternaries.c \
		srcs/utils/ft_utils.c \
		srcs/utils/init.c \
		srcs/utils/parsing.c \
		srcs/utils/time.c

OBJDIR = objs
OBJS = $(SRCS:srcs/%.c=$(OBJDIR)/%.o)

INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Preparing the table for the philosophers"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "The table is ready"

$(OBJDIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
