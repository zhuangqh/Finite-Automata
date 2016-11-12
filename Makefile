SRCS = main.cpp
SRCS += ./src/NFA.cpp
SRCS += ./src/RegexConverter.cpp

OBJS=$(SRCS:.cpp=.o)

CXX=g++ -std=c++11

all: $(OBJS)
	$(CXX) -o ./bin/test $(OBJS)

NFA.o: ./include/NFA.hpp

RegexConverter.o: ./include/RegexConverter.hpp

clean:
	rm ./src/*.o ./bin/test
