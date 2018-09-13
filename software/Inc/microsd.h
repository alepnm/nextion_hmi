#ifndef MICROSD_H_INCLUDED
#define MICROSD_H_INCLUDED



uint8_t SD_init(void);
uint8_t SD_ReadSector(uint32_t block, uint8_t *buff);
uint8_t SD_WriteSector(uint32_t block, uint8_t *buff);

#endif /* MICROSD_H_INCLUDED */
