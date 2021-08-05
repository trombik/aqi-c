CFLAGS+=	--std=c99 -Wall -Werror -I ../../src

all: example

example: aqi.o main.o
	${CC} ${CFLAGS} -o example main.o aqi.o

main.o: main.c
	${CC} ${CFLAGS} -o main.o -c main.c

aqi.o: ../../src/aqi.c
	${CC} ${CFLAGS} -o aqi.o -c ../../src/aqi.c

clean:
	rm -f example main.o aqi.o
