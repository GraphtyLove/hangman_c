# Makefile

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
TARGET = game
SRC = main.c game.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)
