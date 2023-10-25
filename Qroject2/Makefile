project2: main.o fraction.o calcFunctions.o dictionary.o 
	g++ -o project2 main.o fraction.o calcFunctions.o dictionary.o 

project2.o: main.cc fraction.h stack.h dictionary.h calcFunctions.h
	g++ -c main.cc 

fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc 

calcFunctions.o: calcFunctions.cc calcFunctions.h
	g++ -c calcFunctions.cc

dictionary.o: dictionary.cc dictionary.h
	g++ -c dictionary.cc 

