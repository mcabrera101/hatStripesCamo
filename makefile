main: sender receiver
	./sender.out msg.txt

sender:	sender.cpp
	g++ -o sender.out sender.cpp

receiver: recv.cpp
	g++ -o receiver.out recv.cpp

clean:
	rm sender.out receiver.out
