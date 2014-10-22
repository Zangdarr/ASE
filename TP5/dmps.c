#include "drive.h"       


static void _void_handler() {
	return;
}


int main (int argc, char * argv[]){
	unsigned int cylindre;
	unsigned int sector;
	unsigned int sector_size;
	int i;
	unsigned char* buffer;


	/* Gestion des exceptions*/
	if(argc != 3){
		printf("Nombre d'arguments : %d\n", argc);
		printf("Cette fonction necessite deux arguments numeriques non signes\n");
		return -1;
	}
	
	
	if(!init_hardware("hardware.ini")){ 
		printf("Erreur lors de l'initialisation du disque virtuel\n");
		exit(EXIT_FAILURE);
	}

	/* Initialisation des variable*/
	
	
	cylindre = atoi(argv[1]);
	sector = atoi(argv[2]);

	for(i=0; i<16; i++) {
		IRQVECTOR[i] = _void_handler;
	}
	
	_out(HDA_CMDREG, CMD_DSKINFO);
	sector_size = (_in(HDA_DATAREGS+4)<<8) + _in(HDA_DATAREGS+5);

	buffer = (unsigned char *)malloc(sector_size);
	/* lit le contenu d'un secteur et le stock dans le buffer*/

	read_sector(cylindre, sector, buffer);
	
	

	for (i = 0; i < sector_size; ++i)
		printf("Sector[%d] = 0x%x\n",i,buffer[i]);


	return 0;
 }