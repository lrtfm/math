ifdef DEBUG
DFLAG=-DDEBUG
else
DFLAG=
endif

CPPFLAG=-g -W ${DFLAG}
all: main


main: main.cpp GradientDescent.hpp  Mfunction.hpp  Mmatrix.hpp  Mvector.hpp  OneDimSearch.hpp Mcommon.hpp
	g++ ${CPPFLAG} main.cpp -o main

test: test.cpp GradientDescent.hpp  Mfunction.hpp  Mmatrix.hpp  Mvector.hpp  OneDimSearch.hpp Mcommon.hpp
	g++ ${CPPFLAG} test.cpp -o test

#g++ -g -Wl,--heap,200000000,--stack,8000000 test.cpp -o test

bigfile: Mcommon.hpp GradientDescent.hpp  main.cpp  Makefile  Mfunction.hpp  Mmatrix.hpp  Mvector.hpp  OneDimSearch.hpp  test.cpp 
	cat Mcommon.hpp Mmatrix.hpp Mvector.hpp Mfunction.hpp OneDimSearch.hpp GradientDescent.hpp main.cpp \
		| grep -v "^#ifndef" | grep -v "^#include.*hpp" | grep -v "^#endif"> code.cpp

clean: 
	rm -rf main test code.cpp
