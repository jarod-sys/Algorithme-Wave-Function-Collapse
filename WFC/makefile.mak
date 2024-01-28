CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

# Vérifier si le système d'exploitation est Windows
ifeq ($(OS),Windows_NT)
    RM=del /Q
else
    RM=rm -f
endif

all: main

main: main.o Patterns.o Grille.o Utils_wfc.o ColorImage.o Image.o Color.o
	$(CC) $(CFLAGS) -o main main.o Patterns.o Grille.o Utils_wfc.o ColorImage.o Image.o Color.o

main.o: main.c utils.h Utils_wfc.h Color.h Image.h ColorImage.h Patterns.h Grille.h
	$(CC) $(CFLAGS) -c main.c

Patterns.o: Patterns.c Patterns.h Utils_wfc.h Image.h ColorImage.h utils.h
	$(CC) $(CFLAGS) -c Patterns.c

Grille.o: Grille.c Grille.h Utils_wfc.h utils.h
	$(CC) $(CFLAGS) -c Grille.c

Utils_wfc.o: Utils_wfc.c Utils_wfc.h utils.h
	$(CC) $(CFLAGS) -c Utils_wfc.c

ColorImage.o: ColorImage.c ColorImage.h Image.h Color.h utils.h
	$(CC) $(CFLAGS) -c ColorImage.c

Image.o: Image.c Image.h utils.h
	$(CC) $(CFLAGS) -c Image.c

Color.o: Color.c Color.h Image.h utils.h
	$(CC) $(CFLAGS) -c Color.c

clean:
	$(RM) *.o main
