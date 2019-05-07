.PHONY: clean dict

BIN=bin
SRC=src
TEST=test
OBJ=obj
LIBS=-lgtest -lpthread

all:clean dict  ${OBJ}/shape.o ${OBJ}/complex_shapes.o ${OBJ}/find_area_visitor.o  ${BIN}/midterm
 
${BIN}/midterm: ${OBJ}/ut_midterm.o
	g++ -std=c++11 ${OBJ}/shape.o ${OBJ}/complex_shapes.o ${OBJ}/find_area_visitor.o -o $@ $< -lgtest -pthread

${OBJ}/ut_midterm.o: ${TEST}/ut_midterm.cpp
	g++ -std=c++11 -c ${TEST}/ut_midterm.cpp -o $@

${OBJ}/shape.o: ${SRC}/shape.cpp ${SRC}/shape.h ${SRC}/ellipse.h ${SRC}/circle.h ${SRC}/rectangle.h
	g++ -std=c++11 -c ${SRC}/shape.cpp -o $@

${OBJ}/find_area_visitor.o: ${SRC}/find_area_visitor.cpp ${SRC}/find_area_visitor.h
	g++ -std=c++11 -c ${SRC}/find_area_visitor.cpp -o $@

${OBJ}/complex_shapes.o: ${SRC}/complex_shapes.cpp ${SRC}/complex_shapes.h
	g++ -std=c++11 -c ${SRC}/complex_shapes.cpp -o $@

dict:
	mkdir -p bin obj
clean:
	rm -f bin/* obj/*
