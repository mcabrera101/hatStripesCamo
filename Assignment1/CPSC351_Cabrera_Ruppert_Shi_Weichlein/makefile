main: clean sender receiver tar
	./sender.out msg.txt & ./receiver.out

sender:	sender.cpp
	g++ -o sender.out sender.cpp

receiver: recv.cpp
	g++ -o receiver.out recv.cpp

clean:
	rm -f sender.out receiver.out recvfile.txt

tar:
	tar cvf CPSC351_Cabrera_Ruppert_Shi_Weichlein.tar *.cpp *.h makefile *.txt *.pdf
