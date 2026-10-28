CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
LDFLAGS = -pthread
CC = g++

OBJS = lizards.o lizard.o cat.o
SRC = lizards.cpp lizard.cpp cat.cpp
HDR = lizard.hpp lizard.hpp cat.hpp sharedstate.hpp
BINARY = lizards 

${BINARY}: ${OBJS} 
	${CC} ${LDFLAGS} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} ${RANGE} ${NUMTHREADS} 

clean:
	rm -f ${BINARY} *.o
