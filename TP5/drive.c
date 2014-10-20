#include "drive.h"


void read_sector(unsigned int cylinder, unsigned int sector, unsigned char * buffer){

	memcpy(MASTERBUFFER, buffer, HDB_SECTORSIZE);
	seek_sector(cylinder, sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1, 1);
	_out(HDA_CMDREG, CMD_READ);
	sleep(HDA_IRQ);
}



void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char * buffer){

	memcpy(MASTERBUFFER, buffer, HDB_SECTORSIZE);
	seek_sector(cylinder, sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1, 1);
	_out(HDA_CMDREG, CMD_WRITE);
	sleep(HDA_IRQ);

}

void format_sector(unsigned int cylinder, unsigned int nsector, unsigned int value){

	memcpy(MASTERBUFFER, buffer, HDB_SECTORSIZE);
	seek_sector(cylinder, sector);
	
}


void seek_sector(unsigned int cylinder, unsigned int sector){

	_out(HDA_DATAREGS, (cylindre>>8)&0xFF);
	_out(HDA_DATAREGS+1, cylindre&0xFF);
	_out(HDA_DATAREGS+2, (sector>>8) & 0xFF);
	_out(HDA_DATAREGS+3, sector & 0xFF);
	_out(HDA_CMDREG,CMD_SEEK);
	_sleep(HDA_IRQ);
}