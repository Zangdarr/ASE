CC = gcc
CFLAGS = -m32 -Wall
#cree lexecutable
all:proscons.o sem.o hw.o
	$(CC) proscons.o sem.o hw.o $(CFLAGS) -o sem
#displaystack.o: displaystack.c
#	$(CC) -c $< -o $@ $(CFLAGS)


proscons.o : proscons.c sem.h
	$(CC) -c $< -o $@ $(CFLAGS)

sem.o : sem.c sem.h
	$(CC) -c $< -o $@ $(CFLAGS)

hw.o : hw.c
	$(CC) -c $< -o $@ $(CFLAGS)
#sert à spécifier que clean et mrproper sont particulier au makefile
# et ne doivent pas etre consideres comme des noms de fichier
.PHONY: clean, mrproper
	
	
#supprime les fichiers .o
clean:
	rm -rf *.o
	
#lance clean et supprime l'executable
mrproper: clean
	rm -rf sem
	
	
