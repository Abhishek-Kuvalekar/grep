grep: main.o grep.o
	cc main.o grep.o -Wall -o grep
main.o: main.c grep.h
	cc -c  main.c -Wall
grep.o: grep.c grep.h
	cc -c grep.c -Wall
