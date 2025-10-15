CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c src/map_io.c src/map.c src/pathfinding.c src/game_console.c
TARGET = so_long_min

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) src/*.o

.PHONY: all clean
