#include "drive.h"


void read_sector(unsigned int cylinder, unsigned int sector, unsigned char * buffer){
	
	int sector_size = 0;

	_out(HDA_CMDREG, CMD_DSKINFO);
	sector_size = (_in(HDA_DATAREGS+4)<<8) + _in(HDA_DATAREGS+5);
	seek_sector(cylinder, sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1, 1);
	_out(HDA_CMDREG, CMD_READ);
	_sleep(HDA_IRQ);
	memcpy(buffer, MASTERBUFFER, sector_size);


}



void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char * buffer){


	int sector_size =0;
	_out(HDA_CMDREG, CMD_DSKINFO);
	sector_size = (_in(HDA_DATAREGS+4)<<8) + _in(HDA_DATAREGS+5);
	
	memcpy(MASTERBUFFER, buffer, sector_size);

	seek_sector(cylinder, sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1, 1);
	_out(HDA_CMDREG, CMD_WRITE);
	_sleep(HDA_IRQ);

}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value){

	seek_sector(cylinder,sector);
	_out(HDA_DATAREGS, (nsector>>8)&0xFF);
	_out(HDA_DATAREGS+1, nsector & 0xFF);
	_out(HDA_DATAREGS+2, (value>>24)&0xFF);
	_out(HDA_DATAREGS+3, (value>>16)&0xFF);
	_out(HDA_DATAREGS+4, (value>>8)&0xFF);
	_out(HDA_DATAREGS+5, value & 0xFF);
	_out(HDA_CMDREG, CMD_FORMAT);
	_sleep(HDA_IRQ);
		
	
} 


void seek_sector(unsigned int cylinder, unsigned int sector){

	_out(HDA_DATAREGS, (cylinder>>8)&0xFF);
	_out(HDA_DATAREGS+1, cylinder&0xFF);
	_out(HDA_DATAREGS+2, (sector>>8) & 0xFF);
	_out(HDA_DATAREGS+3, sector & 0xFF);
	_out(HDA_CMDREG,CMD_SEEK);
	_sleep(HDA_IRQ);
}

