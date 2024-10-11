CDEMO : main.o TinyFrame.o
	gcc -o CDEMO main.o TinyFrame.o

main.o : main.c TinyFrame.h
	gcc -c main.c

TinyFrame.o : TinyFrame.c TinyFrame.h
	gcc -c TinyFrame.c

clean : 
	rm CDEMO main.o TinyFrame.o