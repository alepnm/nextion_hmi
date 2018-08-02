#ifndef XPT2046_H_INCLUDED
#define XPT2046_H_INCLUDED


void    XPT_Process(void);

void    SoftSpiSend( uint8_t* data, uint8_t len);
void    SoftSpiReceive( uint8_t* data, uint8_t len);


#endif /* XPT2046_H_INCLUDED */
