
all: clean compile link

link:
	g++ -o bin/main.o bin/work1.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/someclass.o src/someclass.cpp

clean:
	rm -f bin/*
