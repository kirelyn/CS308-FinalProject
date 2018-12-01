CC = gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)

main: clean $(obj)
	$(CC) -o main $(obj) -lncurses

.PHONY: clean
clean:
	rm -f $(obj) main
