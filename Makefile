
CFLAGS = -Wall -Wextra -g
PROG = DevAuth 
SRC = ${PROG}.c reg.c current_date.c
OBJ = DevAuth.o reg.o current_date.o
CC = gcc

${PROG}:${OBJ}
	${CC} -o ${PROG} ${OBJ} -lncurses
%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@  
.PHONY: clean
clean:
	rm -f ${OBJ} ${PROG} 
