soduku:soduku.o main.o rules.o wayViolent.o
	gcc soduku.o main.o rules.o wayViolent.o -o soduku

soduku.o:soduku.h soduku.c
	gcc -c soduku.c -o soduku.o

main.o:soduku.h main.c
	gcc -c main.c -o main.o

rules.o:soduku.h rules.c
	gcc -c rules.c -o rules.o

wayViolent.o:soduku.h wayViolent.c
	gcc -c wayViolent.c -o wayViolent.o

clean:
	rm *.o

