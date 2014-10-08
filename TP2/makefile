CC = gcc
CFLAGS = -m32 -Wall
#cree lexecutable
all:switch_to.o
	$(CC) switch_to.o  $(CFLAGS) -o switch_to

#displaystack.o: displaystack.c
#	$(CC) -c $< -o $@ $(CFLAGS)


	
switch_to.o : switch_to.c 
	$(CC) -c $< -o $@ $(CFLAGS)




#sert à spécifier que clean et mrproper sont particulier au makefile
# et ne doivent pas etre consideres comme des noms de fichier
.PHONY: clean, mrproper
	
	
#supprime les fichiers .o
clean:
	rm -rf *.o
	
#lance clean et supprime l'executable
mrproper: clean
	rm -rf displaystack
	
	
