all: testApp

testApp: test.o
	g++ -std=c++14 test.o -o testApp

test.o: test.cpp knife.h
	g++ -std=c++14 -c test.cpp

clean:
	rm *.o testApp