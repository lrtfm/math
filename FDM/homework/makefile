all: main.o fdm.o
	g++ -g -o main main.o fdm.o

main.o: main.cpp fdm.hpp
	g++ -g -c main.cpp -o main.o

fdm.o: fdm.cpp fdm.hpp
	g++ -g -c fdm.cpp -o fdm.o


clean:
	rm -rf fdm.o main.o main
