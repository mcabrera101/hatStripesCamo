run: simulator.cpp
	rm -f out.txt
	g++ -o simulator.o simulator.cpp
	./simulator.o
	rm -f simulator.o
