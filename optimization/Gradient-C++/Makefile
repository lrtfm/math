ifdef DEBUG
DFLAG=-DDEBUG
else
DFLAG=
endif

CPPFLAG=-g -W ${DFLAG}
all: main

FILE=Mcommon.hpp Mmatrix.hpp Mvector.hpp Mfunction.hpp OneDimSearch.hpp GradientDescent.hpp main.cpp


main: main.cpp GradientDescent.hpp  Mfunction.hpp  Mmatrix.hpp  Mvector.hpp  OneDimSearch.hpp Mcommon.hpp
	g++ ${CPPFLAG} main.cpp -o main

test: test.cpp GradientDescent.hpp  Mfunction.hpp  Mmatrix.hpp  Mvector.hpp  OneDimSearch.hpp Mcommon.hpp
	g++ ${CPPFLAG} test.cpp -o test

#g++ -g -Wl,--heap,200000000,--stack,8000000 test.cpp -o test

bigfile: $(FILE)
	for i in $(FILE); do cat -n $$i >> code.cpp; done
#	cat -n Mcommon.hpp Mmatrix.hpp Mvector.hpp Mfunction.hpp OneDimSearch.hpp GradientDescent.hpp main.cpp > code.cpp
#	cat Mcommon.hpp Mmatrix.hpp Mvector.hpp Mfunction.hpp OneDimSearch.hpp GradientDescent.hpp main.cpp \
#		| grep -v "^#ifndef" | grep -v "^#include.*hpp" | grep -v "^#endif"> code.cpp

clean: 
	rm -rf main test code.cpp
