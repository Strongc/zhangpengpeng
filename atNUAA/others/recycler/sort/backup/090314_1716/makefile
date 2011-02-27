sort:prepair.o sort.o sortAchieve.o
	gcc -o sort prepair.o sort.o sortAchieve.o
	rm *.o
	./sort

prepair.o:sort.h prepair.c
	gcc -c prepair.c

sort.o:sort.h sort.c
	gcc -c sort.c

sortAchieve.o:sort.h sortAchieve.c
	gcc -c sortAchieve.c
