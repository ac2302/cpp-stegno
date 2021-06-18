GPPPARAMS = '-Wall'
OBJECTS = main.o

%.o: %.cpp
	g++  $(GPPPARAMS) -o $@ -c $<

build: $(OBJECTS)
	g++ $(OBJECTS) -o stegno 

clean:
	rm stegno *.o
