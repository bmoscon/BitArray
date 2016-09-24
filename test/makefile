# Makefile for bit array test program
# 
# Jan 2013 - Bryant Moscon


array_test: array_test.o
	g++ -g -Wall -o array_test array_test.o

array_test.o: array_test.cpp
	g++ -g -Wall -c array_test.cpp -I../src

clean:
	rm array_test array_test.o
