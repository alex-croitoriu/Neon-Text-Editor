all:
	g++ src/*.cpp -o main.exe -Isrc/include -Iinclude -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lcomdlg32