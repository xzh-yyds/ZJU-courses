parser: scanner.cpp parser.cpp grammartree.h func.h
	clang++ -g scanner.cpp parser.cpp -o cmm.out `llvm-config --cxxflags --ldflags --libs` -lpthread

scanner:scanner.cpp
	clang -o scanner.cpp

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l 

parser.cpp: parser.y
	bison -vdty parser.y -o parser.cpp

clean:
	rm scanner.c scanner parser.cpp out.txt y.output y.tab.h y.tab.c parser parser.cpp parser.hpp parser.output scanner.cpp

run:
	./cmm.out demo.cpp