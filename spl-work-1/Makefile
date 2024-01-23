all: clean compile link

link:
	g++ -o bin/Action.o bin/Customer.o  bin/Volunteer.o bin/WareHouse.o bin/main.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/Action.o /home/users/bsc/sagior/spl-work-1/spl-work-1/Skeleton/src/Action.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o /home/users/bsc/sagior/spl-work-1/spl-work-1/Skeleton/src/Customer.cpp
	
	g++ -g -Wall -Weffc++ -c -o bin/Volunteer.o /home/users/bsc/sagior/spl-work-1/spl-work-1/Skeleton/src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/WareHouse.o //home/users/bsc/sagior/spl-work-1/spl-work-1/Skeleton/src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/main.o //home/users/bsc/sagior/spl-work-1/spl-work-1/Skeleton/src/main.cpp

clean:
	rm -f bin/*