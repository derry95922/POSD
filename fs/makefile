# .PHONY: clean dirs

# BIN=bin
# SRC=src
# TEST=test
# OBJ=obj
# LIBS=-lgtest -lpthread

# all: clean dirs bin/hw7 run

# bin/hw7: test/ut_fs.cpp test/ut_fs.h src/*.h obj/info_content_visitor.o obj/find_visitor.o obj/find_link_visitor.o obj/find_node_by_pathname_visitor.o
# 	g++ -std=c++11 $< obj/info_content_visitor.o obj/find_visitor.o obj/find_link_visitor.o obj/find_node_by_pathname_visitor.o -o $@ -lgtest -lpthread

# obj/info_content_visitor.o: src/info_content_visitor.cpp src/info_content_visitor.h
# 	g++ -std=c++11 -c $< -o $@

# obj/find_visitor.o:src/find_visitor.cpp src/find_visitor.h
# 	g++ -std=c++11 -c $< -o $@

# obj/find_link_visitor.o:src/find_link_visitor.cpp src/find_link_visitor.h
# 	g++ -std=c++11 -c $< -o $@

# obj/find_node_by_pathname_visitor.o::src/find_node_by_pathname_visitor.cpp src/find_node_by_pathname_visitor.h
# 	g++ -std=c++11 -c $< -o $@

# dirs:
# 	mkdir -p src test bin obj

# run:
# 	bin/hw7

# clean:
# 	rm -rf bin obj

# stat:
# 	wc src/* test/*

BIN=bin
OBJ=obj
all:clean dirs $(BIN)/tree_test run

$(BIN)/tree_test: src/tree_test.cpp src/tree_test.h src/tree_frame.h | $(BIN)
	g++ $< `wx-config --libs` `wx-config --cxxflags` -o $@

run:
	$(BIN)/tree_test test_data

dirs:
	mkdir -p $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)