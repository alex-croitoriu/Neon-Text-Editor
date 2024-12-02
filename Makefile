all:
	g++ main.cpp -o main.exe -Isrc/include -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system