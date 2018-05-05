Handler.out: Handler.o
	g++ -o Handler.out Handler.o

Handler.o: Handler.cpp	
	g++ -std=c++11 -c Handler.cpp
	
clean:
	rm -f *.o *.out