project: main.o grep.o readline.o help.o count.o method.o option_select.o file_type.o option_file_sort.o recurse_grep.o
	cc main.o grep.o readline.o help.o count.o method.o option_select.o file_type.o option_file_sort.o recurse_grep.o -Wall -o project
main.o: main.c grep.h
	cc -c  main.c -Wall
grep.o: grep.c grep.h
	cc -c grep.c -Wall
readline.o: readline.c grep.h
	cc -c readline.c -Wall
help.o: help.c grep.h
	cc -c help.c -Wall
count.o: count.c grep.h
	cc -c count.c -Wall
method.o: method.c grep.h
	cc -c method.c -Wall
option_select.o: option_select.c grep.h
	cc -c option_select.c -Wall	
file_type.o: file_type.c grep.h
	cc -c file_type.c -Wall
option_file_sort.o: option_file_sort.c grep.h
	cc -c option_file_sort.c -Wall
recurse_grep.o: recurse_grep.c grep.h
	cc -c recurse_grep.c -Wall
clean:
	rm *.o project
