CC = gcc
FILES = main.c
FLAGS = -Wall -Werror -pthread

backup: $(FILES)
		$(CC) -o backup $(FILES) $(FLAGS)