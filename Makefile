# Makefile
proj1 : main.o library.o member.o resource.o space.o
	g++ -std=c++11 -o proj main.o library.o member.o resource.o space.o

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

library.o : library.cpp
	g++ -std=c++11 -c library.cpp

member.o : member.cpp
	g++ -std=c++11 -c member.cpp

resource.o : resource.cpp
	g++ -std=c++11 -c resource.cpp
	
space.o : space.cpp
	g++ -std=c++11 -c space.cpp
	
clean :
	rm main.o library.o member.o resource.o space.o proj