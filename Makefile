all: compile link

compile:
	g++ -Isrc/include -c player.cpp  game.cpp main.cpp
link:
	g++ main.o game.o player.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system