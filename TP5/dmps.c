
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hardware.h"


#define HDA_CMDREG  0x3F6        
#define HDA_DATAREGS   0x110        
#define HDA_IRQ       14           


static void _void_handler() {
	return;
}


int main (int argc, char * argv[]){
	unsigned int cylindre;
	unsigned int sector;
	unsigned int sector_size;
	int i;
	int cpt;
	
	unsigned char* buffer;


	cpt = 1;


	
	if(argc != 3){
		printf("Nombre d'arguments : %d\n", argc);
		printf("Cette fonction necessite deux arguments numeriques non signes\n");
		return -1;
	}
	


	
	if(!init_hardware("hardware.ini")){ 
		printf("Erreur lors de l'initialisation du disque virtuel\n");
		exit(EXIT_FAILURE);
	}

	
	cylindre = atoi(argv[1]);
	sector = atoi(argv[2]);


	for(i=0; i<16; i++) {
		IRQVECTOR[i] = _void_handler;
	}
	
	_out(HDA_CMDREG, CMD_DSKINFO);

	
	sector_size = (_in(HDA_DATAREGS+4)<<8) + _in(HDA_DATAREGS+5);

	/* placement de la tete de lecture*/
	_out(HDA_DATAREGS, (cylindre>>8)&0xFF);
	_out(HDA_DATAREGS+1, cylindre&0xFF);	
	_out(HDA_DATAREGS+2, (sector>>8) & 0xFF);
	_out(HDA_DATAREGS+3, sector & 0xFF);
	_out(HDA_CMDREG,CMD_SEEK);

	_sleep(HDA_IRQ);

	for (i = 0; i < sector_size; ++i)
	{
		MASTERBUFFER[i] = 'a';
		fflush(stdout);
		
	}
	
	_out(HDA_DATAREGS, 0);
	_out(HDA_DATAREGS+1, 1);
	_out(HDA_CMDREG,CMD_WRITE);
	_sleep(HDA_IRQ);

	_out(HDA_DATAREGS, 0);
	_out(HDA_DATAREGS+1, 1);
	_out(HDA_CMDREG,CMD_READ);
	_sleep(HDA_IRQ);

	

	printf("SECTORSIZE %d\n", sector_size);
	fflush(stdout);

	buffer = (unsigned char *)malloc(sector_size);

	for (i = 0; i < sector_size; ++i)
	{
		buffer[i] = MASTERBUFFER[i];
		
		printf("MASTERBUFFER : %c\n", MASTERBUFFER[i]);
		fflush(stdout);
	}

	printf("ça affiche maggle : %s\n", buffer);
	
	return 0;
 }