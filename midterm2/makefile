# hw1-2
all: clean dict hw1 run
hw1:ut_main.o
		g++ -o bin/hw1 obj/ut_main.o -lgtest -pthread

ut_main.o: test/ut_main.cpp	src/*.h
		g++ -std=c++11 -c test/ut_main.cpp -o obj/ut_main.o
dict: 
	mkdir -p obj bin
clean: 
	rm -rf obj bin
run:
	bin/hw1