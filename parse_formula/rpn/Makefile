CC=g++
CPPFLAGS=-g

SOURCE := $(shell ls *.cpp)
DEPS := $(shell ls *.hpp)
OBJ := $(SOURCE:.cpp=.o)

all:rpn

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

rpn: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -rf $(OBJ) rpn
