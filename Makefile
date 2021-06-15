build: main.cpp
	g++ main.cpp -o stegno `pkg-config --cflags --libs opencv4`

