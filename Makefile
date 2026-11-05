CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
LDFLAGS = -pthread
CC = g++

OBJS = lizards.o  
SRC = lizards.cpp  
BINARY = lizards  

${BINARY}: ${OBJS} 
	${CC} ${LDFLAGS} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC}  
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} -d 

clean:
	rm -f ${BINARY} *.o
