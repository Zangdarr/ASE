void read_sector(unsigned int cylinder, unsigned int sector, unsigned char * buffer);
void writre_sector(unsigned int cylinder, unsigned int sector, const unsigned char * buffer);
void format_sector(unsigned int cylinder, unsigned int nsector, unsigned int value);
void seek_sector(unsigned int cylinder, unsigned int sector);