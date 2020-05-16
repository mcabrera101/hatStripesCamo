run: simulator.cpp
	g++ -o simulator.o simulator.cpp
	./simulator.o

clean:
	rm -f simulator.o
