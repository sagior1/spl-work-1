all:  compile link clesnObjAndRun

link:
		g++ -o bin/wow bin/Action.o bin/Order.o bin/Customer.o bin/Volunteer.o bin/WareHouse.o bin/main.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/Action.o src/Action.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall  -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp

clean:
	rm -f bin/*.O

clesnObjAndRun:
	rm -f *.O
	clear
	valgrind --leak-check=full --show-reachable=yes ./bin/wow "/home/users/bsc/sagior/Downloads/configFileExample.txt"
