all: compil clean start

compil: main.o funcs.o 
	g++ main.o funcs.o -o out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network 
	
main.o: main.cpp 
	g++ -c main.cpp

funcs.o: funcs.cpp 
	g++ -c funcs.cpp

start:
	./out

clean: 
	rm -rf *.o  
