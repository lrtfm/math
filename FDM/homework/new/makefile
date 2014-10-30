all: main.o fdm_solver.o first_solver.o
	g++ -g -o main main.o fdm_solver.o first_solver.o

main.o: main.cpp first_solver.hpp
	g++ -g -c main.cpp -o main.o

fdm_solver.o: fdm_solver.cpp fdm_solver.hpp
	g++ -g -c fdm_solver.cpp -o fdm_solver.o

first_solver.o: first_solver.cpp first_solver.hpp fdm_solver.hpp
	g++ -g -c first_solver.cpp -o first_solver.o

clean:
	rm -rf fdm_solver.o first_solver.o main.o main
