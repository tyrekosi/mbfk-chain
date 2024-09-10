CC = gcc
CFLAGS = -Wall -O2
TARGET = mbf_compiler

all: $(TARGET)

$(TARGET): mbf_compiler.c
	$(CC) $(CFLAGS) -o $(TARGET) mbf_compiler.c

clean:
	rm -f $(TARGET)
