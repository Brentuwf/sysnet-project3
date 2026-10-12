CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
LDFLAGS = -pthread
CC = g++

OBJS = lizards.o lizardsUni.o 
SRC = lizards.cpp lizardsUni.cpp 
HDR = lizards.hpp lizardsUni.hpp 
BINARY = lizards lizardsUni 

${BINARY}: ${OBJS} 
	${CC} ${LDFLAGS} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} ${RANGE} ${NUMTHREADS} 

clean:
	rm -f ${BINARY} *.o
