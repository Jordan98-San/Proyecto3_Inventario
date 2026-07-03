CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC = $(wildcard src/*.c) \
      $(wildcard src/menu/*.c) \
      $(wildcard src/models/*.c) \
      $(wildcard src/services/*.c) \
      $(wildcard src/storage/*.c)

OBJ = $(SRC:.c=.o)

TARGET = build/inventario

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
