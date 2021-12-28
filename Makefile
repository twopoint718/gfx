CFLAGS=-Wall -O0 -g -std=c99
SRCS = $(wildcard *.c)
# all object files except test.o
OBJS = $(patsubst test.%,,$(patsubst %.c, %.o, $(SRCS)))

main: $(OBJS)
	cc -o $@ $^

test: test.o gfx.o
	cc -o test test.o gfx.o
	./test

%.o : %.c
	cc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

.PHONY: clean
