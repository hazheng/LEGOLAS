CFLAGS = -Wall 
LIBS = `pkg-config --cflags --libs opencv`
legolas: main.cpp
	g++ main.cpp -g3 -o legolas.out $(CFLAGS) $(LIBS)
