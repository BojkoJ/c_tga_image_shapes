# Definování kompilátoru
CC=gcc

# Příznaky pro kompilaci
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g -fsanitize=address

# Příznaky pro linker
LDFLAGS=-lm -fsanitize=address

# Jméno výsledného spustitelného souboru
TARGET=program

# Soubory pro kompilaci
OBJS=main.c image.c shapes.c

# Pravidlo pro výchozí build
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Pravidlo pro vymazání sestavených souborů
clean:
	rm -f $(TARGET) *.o