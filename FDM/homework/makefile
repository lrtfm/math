CC=g++
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=main.cpp fdm_solver.cpp first_solver.cpp leapforg.cpp neumann_solver.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=solver

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf $(OBJECTS) $(EXECUTABLE)

#
#all: main.o fdm_solver.o first_solver.o leapforg.o
#	g++ -g -o main main.o fdm_solver.o first_solver.o leapforg.o
#
#main.o: main.cpp first_solver.hpp
#	g++ -g -c main.cpp -o main.o
#
#fdm_solver.o: fdm_solver.cpp fdm_solver.hpp
#	g++ -g -c fdm_solver.cpp -o fdm_solver.o
#
#first_solver.o: first_solver.cpp first_solver.hpp fdm_solver.hpp
#	g++ -g -c first_solver.cpp -o first_solver.o
#
#leapforg.o: leapforg.cpp leapforg.hpp fdm_solver.hpp
#	g++ -g -c leapforg.cpp -o leapforg.o
#
#clean:
#	rm -rf fdm_solver.o first_solver.o leapforg.o main.o main
