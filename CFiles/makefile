CFLAGS = -g -Wall

JerryBoree:Jerry.o KeyValuePair.o LinkedList.o HashTable.o MultiValueHashTable.o JerryBoreeMain.o
	gcc *.c -o JerryBoree $(CFLAGS)
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c KeyValuePair.c LinkedList.c $(CFLAGS)
JerryBoreeMain.o: JerryBoreeMain.c HashTable.h Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h Jerry.h
	gcc -c JerryBoreeMain.c HashTable.c Jerry.c LinkedList.c MultiValueHashTable.c $(CFLAGS)
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c $(CFLAGS)
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c $(CFLAGS)
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c $(CFLAGS)
MultiValueHashTable.o: MultiValueHashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h
	gcc -c MultiValueHashTable.c HashTable.c LinkedList.c $(CFLAGS)
clean:
	$(RM) *.o
	$(RM) JerryBoree
