CC=g++
SRC=main.cpp CPU_sched.cpp
OBJ=${SRC:.cpp=.o}


all:${OBJ}


build: CPU_sched.h
	${CC} -c ${SRC}

${OBJ}:build
	${CC} -o lab4 ${OBJ}


clean:
	rm -rf ${OBJ} lab4
