#------------------------------------------------------------------------------------------------------------------------------
# COMMANDS:
# make -> creates Arithmetic executable
# make clean -> removes all .o, .d, .txt, and executables
# make BigIntegerTest -> creates testing harness for BigInteger ADT
# make ListTest -> creates testing harness for the long ADT
#------------------------------------------------------------------------------------------------------------------------------
targets = ListClient Arithmetic ListTest BigIntegerTest *Client
objs = List.o BigInteger.o

CC = g++
CFLAGS = -std=c++17 -Wall 

COMPILE = $(CC) $(CFLAGS) -g -c  
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

Arithmetic: Arithmetic.o $(objs)
	$(LINK) $@ $^

BigIntegerClient: BigIntegerClient.o $(objs)
	$(LINK) $@ $^

ListClient: ListClient.o $(objs)
	$(LINK) $@ $^

ListTest: ListTest.o $(objs)
	$(LINK) $@ $^

BigIntegerTest: BigIntegerTest.o $(objs)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt