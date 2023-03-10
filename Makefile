CFLAGS= -Wall -g -lm
SRC= main.c basic.c edit.c draw_functions.c
DEPS= bmp_header.h utils.h 

build: bmp
bmp: $(SRC) $(DEPS)
	gcc $(SRC) $(CFLAGS) -o $@
run: bmp
	./$<

clean:
	rm -f bmp