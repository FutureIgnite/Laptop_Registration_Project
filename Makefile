
CFLAGS = -Wall -g
PROG = DevAuth 
SRC = ${PROG}.c reg.c
OBJ = DevAuth.o reg.o
CC = gcc

${PROG}:${OBJ}
	${CC} -o ${PROG} ${OBJ}
%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@ 
.PHONY: clean
clean:
	rm -f ${OBJ} ${PROG} 