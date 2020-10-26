#Makefile
#-o:大概可以自定義生成的可知性文件叫什麼名字。
#-c:只生成.o文件。
#not yet!! but I am tired.
all: poly_parser

poly_parser: poly_parser.o bigfloat.o
	g++ -pg -g -o poly_parser poly_parser.o bigfloat.o

poly_parser.o: poly_parser.cpp
	g++ -pg -g -c poly_parser.cpp

bigfloat.o: bigfloat.cpp
	g++ -pg -g -c bigfloat.cpp

clean:
	rm -rf *.o main