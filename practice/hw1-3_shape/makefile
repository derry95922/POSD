# hw1-2
# all: clean dict hw1
# hw1:ut_main.o
# 		g++ -o bin/hw1 obj/ut_main.o -lgtest -pthread
# ut_main.o: test/ut_main.cpp src/*.h
# 		g++ -std=c++11 -c test/ut_main.cpp -o obj/ut_main.o

all:clean dict hw3

hw3:src/main.cpp src/*.h
	g++ -std=c++11 src/main.cpp -o bin/hw3 -lgtest -pthread
dict: 
	mkdir -p obj bin
clean: 
	rm -rf obj bin


# all:clean dict hw3
# hw3: main.o
# 	g++ -o bin/hw3 obj/main.o -lgtest -pthread
# main.o:src/main.cpp src/*.h
# 	g++ -std=c++11 -c src/main.cpp -o obj/main.o
# dict: 
# 	mkdir -p obj bin
# clean: 
# 	rm -rf obj bin
