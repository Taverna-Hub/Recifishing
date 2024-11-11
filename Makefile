CC = gcc
SRC = $(shell find src -name '*.c')  
OBJ = $(SRC:.c=.o)  
TARGET = Recifishing
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

all: $(TARGET)

run: clean all
	clear
	./$(TARGET)
