all: clean dict hw7 run

hw7:test/* src/* obj/info_content_visitor.o obj/find_visitor.o obj/find_link_visitor.o obj/find_node_by_pathname_visitor.o
	g++ -std=c++11 test/ut_fs.cpp obj/info_content_visitor.o obj/find_visitor.o obj/find_link_visitor.o obj/find_node_by_pathname_visitor.o -o bin/hw7 -lgtest -pthread

obj/info_content_visitor.o:src/info_content_visitor.cpp src/info_content_visitor.h
	g++ -std=c++11 -c $< -o $@

obj/find_visitor.o:src/find_visitor.cpp src/find_visitor.h
	g++ -std=c++11 -c $< -o $@

obj/find_link_visitor.o:src/find_link_visitor.cpp src/find_link_visitor.h
	g++ -std=c++11 -c $< -o $@

obj/find_node_by_pathname_visitor.o:src/find_node_by_pathname_visitor.cpp src/find_node_by_pathname_visitor.h
	g++ -std=c++11 -c $< -o $@
run:
	bin/hw7

dict:
	mkdir -p obj bin
clean:
	rm -rf obj bin 