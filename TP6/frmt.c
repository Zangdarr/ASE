#include "drive.h"       


static void _void_handler() {
	return;
}
int main (int argc, char * argv[]){
	
	
	unsigned int i, j;
	unsigned int nbCylindres = 0;
	unsigned int nbSecteurs = 0;

if(!init_hardware("hardware.ini")){ 
		printf("Erreur lors de l'initialisation du disque virtuel\n");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<16; i++) {
		IRQVECTOR[i] = _void_handler;
	}
	_out(HDA_CMDREG, CMD_DSKINFO);

	nbCylindres = (_in(HDA_DATAREGS)<<8) + _in(HDA_DATAREGS+1);
	nbSecteurs = (_in(HDA_DATAREGS+2) <<8) + _in(HDA_DATAREGS+3);



	for(i = 0; i < nbCylindres; i++){

		for(j = 0; j < nbSecteurs; j++){
			printf("i : %d, j : %d \n",i,j);
			format_sector(i, j, 1, 0);
		}
	}

	return 0;
 }
