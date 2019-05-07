.PHONY: clean dict
all: clean dict hw3
hw3: main.o 
		g++ -o bin/hw3 obj/main.o -lgtest -pthread
main.o: src/main.cpp src/*.h
		g++ -std=c++11 -c src/main.cpp -o obj/main.o
dict:
	mkdir -p obj bin
clean:
	rm -rf obj bin
