




all: sequencial
	./*.o

sequencial:
	gcc mergeSort.c -o mergeSort.o -Wall -O3

clean:
	rm *.o