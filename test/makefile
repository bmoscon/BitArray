# Makefile for bit array test program
# 
# Jan 2013 - Bryant Moscon


array_test: array_test.o
	g++ -o array_test array_test.o

array_test.o: array_test.cpp ../src/bit_array.hpp
	g++ -c array_test.cpp

clean:
	rm array_test array_test.o
