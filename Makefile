CC = gcc
CFLAGS = -g -O2 -pedantic -Wall -ansi

Prog : Inporte Lex Source


Recupe : Recuper Lex Source

Recuper : Main.o Fichier.o Arbre.o Affichage.o

Inporte :
	mv source/Main.o Main.o
	mv source/Fichier.o Fichier.o
	mv source/Arbre.o Arbre.o
	mv source/Affichage.o Affichage.o
	rm -rf source

Source : Main.o Fichier.o Arbre.o Affichage.o
	rm -rf source
	mkdir source
	mv Main.o source/Main.o
	mv Fichier.o source/Fichier.o
	mv Arbre.o source/Arbre.o
	mv Affichage.o source/Affichage.o

Lex : Main.o Fichier.o Arbre.o Affichage.o
	$(CC) $(CFLAGS) Main.o Fichier.o Arbre.o Affichage.o -o Lexique

Main.o : main.c
	$(CC) $(CFLAGS) -c main.c

Fichier.o : fichier.c
	$(CC) $(CFLAGS) -c fichier.c

Arbre.o : arbre.c
	$(CC) $(CFLAGS) -c arbre.c

Affichage.o : affichage.c
	$(CC) $(CFLAGS) -c affichage.c

clean:
	rm -f *.o
	rm -f source/*.o
	rm -rf source

Run : Prog
	./Lexique
