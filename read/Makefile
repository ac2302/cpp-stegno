GPPPARAMS = '-Wall'
OBJECTS = main.o

%.o: %.cpp
	g++  $(GPPPARAMS) -o $@ -c $<

build: $(OBJECTS)
	g++ $(OBJECTS) -o cpsread 

clean:
	rm cpsread *.o
