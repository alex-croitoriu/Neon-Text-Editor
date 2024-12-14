all:
	g++ main.cpp precompute.cpp button.cpp -o main.exe -Isrc/include -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system