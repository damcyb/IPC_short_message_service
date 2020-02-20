server: inf120573_s.o
	gcc inf120573_s.o -o server
	./server
inf120573_s.o: inf120573_s.c inf120573_serverFunction.h inf120573_struct.h
	gcc -c inf120573_s.c
client: inf120573_c.o
	gcc inf120573_c.o -o client
	./client
inf120573_c.o: inf120573_c.c inf120573_clientFunction.h inf120573_struct.h
	gcc -c inf120573_c.c
clean:
	rm -f *.gch *.o *.out