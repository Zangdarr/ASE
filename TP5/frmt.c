#include "drive.h"       



int main (int argc, char * argv[]){
	
	
	unsigned int sector_size;
	unsigned int i, j;
	unsigned int nbCylindres = 0;
	unsigned int nbSecteurs = 0;


	
	_out(HDA_CMDREG, CMD_DSKINFO);
	sector_size = (_in(HDA_DATAREGS+4)<<8) + _in(HDA_DATAREGS+5);
	nbCylindres = (_in(HDA_DATAREGS)<<8) + _in(HDA_DATAREGS+1);
	nbSecteurs = (_in(HDA_DATAREGS+2) <<8) + _in(HDA_DATAREGS+3);

	for(i = 0; i < nbCylindres; i++){
		for(j = 0; j < nbSecteurs; j++){
			format_sector(i, j, nbSecteurs, 5);
		}
	}

	return 0;
 }