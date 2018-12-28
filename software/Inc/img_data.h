#ifndef IMG_DATA_H_INCLUDED
#define IMG_DATA_H_INCLUDED

 typedef struct {
     const uint16_t     *data;
     uint16_t           width;
     uint16_t           height;
     uint8_t            dataSize;
} tImage;


extern const tImage tulips;

#endif /* IMG_DATA_H_INCLUDED */
