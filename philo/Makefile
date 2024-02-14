NAME = philo

SRCS = ./
INCLUDE = ./

CC = gcc
CFLAGS = -g -pthread#-Wall -Wextra -Werror -g -pthread

FILES = main.c routine.c states.c utils.c utils_philo.c
OBJECTS = $(addprefix $(SRCS), $(FILES:.c=.o))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -I $(INCLUDE)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all