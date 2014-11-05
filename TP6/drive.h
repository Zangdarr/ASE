
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hardware.h"

#define HDA_CMDREG  0x3F6        
#define HDA_DATAREGS   0x110        
#define HDA_IRQ       14    

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char * buffer);
void writre_sector(unsigned int cylinder, unsigned int sector, const unsigned char * buffer);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value);
void seek_sector(unsigned int cylinder, unsigned int sector);
void
dump(unsigned char *buffer,
unsigned int buffer_size,
int ascii_dump,
int octal_dump);