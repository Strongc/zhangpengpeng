sort:sort.h intial.o sort.o
	gcc -g intial.o sort.o -o sort

intial.o:sort.h intial.c
	gcc -c -g intial.c 

sort.o:sort.h sort.c
	gcc -c -g sort.c

clean:
	rm *.o
