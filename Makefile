# Compiler and Flags
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g

# Project name
NAME   = philo

# Source and Object files
SRCS   = main.c args.c monitor.c routine.c utils.c
OBJS   = $(SRCS:.c=.o)

# Header files
HEADERS = philo.h

# Default rule
all: $(NAME)

# Linking the binary
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation rule for .c to .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean only object files
clean:
	rm -f $(OBJS)

# Clean everything (including the binary)
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
