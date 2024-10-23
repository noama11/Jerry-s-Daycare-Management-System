JerryBoree:Jerry.o KeyValuePair.o LinkedList.o HashTable.o MultiValueHashTable.o JerryBoreeMain.o
	gcc *.c -o JerryBoree
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c KeyValuePair.c LinkedList.c
JerryBoreeMain.o: JerryBoreeMain.c HashTable.h Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h Jerry.h
	gcc -c JerryBoreeMain.c HashTable.c Jerry.c LinkedList.c MultiValueHashTable.c
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h
	gcc -c MultiValueHashTable.c HashTable.c LinkedList.c
clean:
	$(RM) *.o
	$(RM) JerryBoree