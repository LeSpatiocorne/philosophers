NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = $(shell find srcs -name "*.c")

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
