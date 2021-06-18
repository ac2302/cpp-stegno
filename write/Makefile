GPPPARAMS = '-Wall'
OBJECTS = main.o

%.o: %.cpp
	g++  $(GPPPARAMS) -o $@ -c $<

build: $(OBJECTS)
	g++ $(OBJECTS) -o cpswrite 

clean:
	rm cpswrite *.o
