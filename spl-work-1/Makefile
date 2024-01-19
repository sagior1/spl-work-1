
# Compiler flags
CXXFLAGS := -g -Wall -Weffc++ -Werror

# Source files
SRCS := src/main.cpp src/volunteer.cpp src/BaseAction.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Dependencies
DEPS := $(SRCS:.cpp=.d)

all: clean compile link

link:
	g++ -o bin/main.o bin/work1.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/volunteer.o src/volunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/BaseAction.o src/BaseAction.cpp

output: main.o volunteer.o BaseAction.o
	g++ -g main.o volunteer.o BaseAction.o
clean:
	rm -f bin/*
# Dependency rule
%.d: %.cpp
	g++ $(CXXFLAGS) -MM -MT '$*.o' -MF $@ $<