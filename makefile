main: clean sender receiver
	./sender.out msg.txt & ./receiver.out

sender:	sender.cpp
	g++ -o sender.out sender.cpp

receiver: recv.cpp
	g++ -o receiver.out recv.cpp

clean:
	rm -f sender.out receiver.out recvfile.txt
