CC=gcc
SOURCE_DIR=src
OBJECT_DIR=obj
BIN_DIR=bin
LIB_DIR=lib
CFLAGS=-g -c

all:parse_formula test_trim static_lib share_lib

objects=${OBJECT_DIR}/parse.o ${OBJECT_DIR}/collect.o ${OBJECT_DIR}/math_wapper.o
test_objects=${OBJECT_DIR}/collect.o ${OBJECT_DIR}/test_trim.o

parse_formula:${objects} ${OBJECT_DIR}/main.o
	${CC} -g ${objects} ${OBJECT_DIR}/main.o -o ${BIN_DIR}/parse_formula -lreadline -lm

static_lib:${objects}
	ar -r ${LIB_DIR}/libparseformula.a ${objects}

share_lib:${objects}
	gcc -shared -o ${LIB_DIR}/libparseformula.so ${objects}

test_trim:${test_objects}
	${CC} ${test_objects} -o ${BIN_DIR}/test_trim

${OBJECT_DIR}/parse.o:create_dir ${SOURCE_DIR}/parse.c ${SOURCE_DIR}/parse_formula.h
	${CC} ${CFLAGS} -o ${OBJECT_DIR}/parse.o ${SOURCE_DIR}/parse.c

${OBJECT_DIR}/collect.o:create_dir ${SOURCE_DIR}/collect.c ${SOURCE_DIR}/collect.h ${SOURCE_DIR}/macro.h
	${CC} ${CFLAGS} -o ${OBJECT_DIR}/collect.o ${SOURCE_DIR}/collect.c

${OBJECT_DIR}/math_wapper.o:create_dir ${SOURCE_DIR}/math_wapper.c ${SOURCE_DIR}/math_wapper.h
	${CC} ${CFLAGS} -o ${OBJECT_DIR}/math_wapper.o ${SOURCE_DIR}/math_wapper.c

${OBJECT_DIR}/main.o:create_dir ${SOURCE_DIR}/main.c ${SOURCE_DIR}/parse_formula.h
	${CC} ${CFLAGS} -o ${OBJECT_DIR}/main.o ${SOURCE_DIR}/main.c

${OBJECT_DIR}/test_trim.o:create_dir ${SOURCE_DIR}/test_trim.c ${SOURCE_DIR}/collect.h
	${CC} ${CFLAGS} -o ${OBJECT_DIR}/test_trim.o  ${SOURCE_DIR}/test_trim.c

test:
	bin/test_trim

create_dir:
	mkdir -p ${OBJECT_DIR}
	mkdir -p ${BIN_DIR}
	mkdir -p ${LIB_DIR}

clean:
	rm -rf ${BIN_DIR} ${OBJECT_DIR} ${LIB_DIR} 

