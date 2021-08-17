SHELL = /bin/sh
CC=clang++
CFLAGS= -g 
EXEC=main

#window:CC=g++
#window:CFLAGS=-Wall -lgdi32 -lm
#-mwindows
#window:EXEC=main.exe
 
$(EXEC): io.o parser.o string2.o main.o inter.o
	$(CC) io.o parser.o string2.o main.o inter.o $(CFLAGS) -o $(EXEC)
io.o:src/io.cpp
	$(CC) -c src/io.cpp
parser.o:src/parser.cpp
	$(CC) -c src/parser.cpp	
string2.o:src/string2.cpp
	$(CC) -c src/string2.cpp
inter.o:src/inter.cpp
	$(CC) -c src/inter.cpp
main.o:src/main.cpp
	$(CC) -c src/main.cpp
#*.o:src/*.cpp
#	$(CC) -c src/*.cpp
clean: 
	rm *.o 

	


	
