programa: funcoes.o main.o
	gcc -o programa funcoes.o main.o

main.o: main.c funcoes.h
	gcc -c -Wall main.c

funcoes.o: funcoes.h funcoes.c
	gcc -c -Wall funcoes.c