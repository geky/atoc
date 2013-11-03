
TARGET = atoc

#CFLAGS = -g -Wall -DADDR_SIZE=12
CFLAGS = -O3 -Wall -DADDR_SIZE=12

SRC := $(wildcard *.c)


all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(CFLAGS) $^ -o $@

clean:
	-rm $(TARGET)
