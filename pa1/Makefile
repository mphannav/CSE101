#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

ListTest : ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

clean :
	rm -f Lex ListTest ListClient *.txt *.o blah3
	echo "Removed Files!"

submit :
	git add Lex.c List.c List.h README.md Makefile ListTest.c
	git commit -m "updating"
	git push

checkClient : 
	valgrind --leak-check=full ListClient

checkTest :
	make ListTest
	valgrind --leak-check=full ListTest
	make clean

checkLex :
	make Lex
	valgrind --leak-check=full Lex in3 blah3
	make clean
