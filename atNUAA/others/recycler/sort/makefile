sort:prepair.o sort.o sortAchieve.o
	gcc -o sort prepair.o sort.o sortAchieve.o
	rm *.o

prepair.o:sort.h prepair.c
	gcc -c -O3 prepair.c

sort.o:sort.h sort.c
	gcc -c -O3 sort.c

sortAchieve.o:sort.h sortAchieve.c
	gcc -c -O3 sortAchieve.c
