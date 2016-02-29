CC=g++
CPPFLAGS=-g

TARGET := test
SOURCE := $(wildcard *.cpp)
DEPS := $(wildcard *.hpp)
OBJ := $(SOURCE:.cpp=.o)
#OBJ := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all:$(TARGET)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -rf $(OBJ) $(TARGET)
