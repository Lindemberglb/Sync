CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: sync_car

sync_car: sync_car.c sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) -D_DEFAULT_SOURCE -Wno-unused-parameter sync_car.c sync_car-runner.c -o sync_car

clean:
	rm -f sync_car

.PHONY: all clean
