
CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include
PARSE_LEX_FILES = src/parser.tab.o src/lexer.yy.o src/parser.tab.o

all : bin/compiler bin/print_canonical

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp $(PARSE_LEX_FILES)
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

bin/print_canonical : src/print_canonical.o $(PARSE_LEX_FILES)
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

clean :
	rm -f src/*.o
	rm -f bin/*
	rm src/*.tab.cpp
	rm src/*.tab.hpp
	rm src/*.yy.cpp
