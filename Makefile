CC = gcc
FILES = main.c traverseFiles.c
FLAGS = -Wall -Werror -pthread

backup: $(FILES)
		$(CC) -o backup $(FILES) $(FLAGS)