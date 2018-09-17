#ifndef XPT2046_H_INCLUDED
#define XPT2046_H_INCLUDED

#include <stdint.h>

#define START_BIT                   0x80

/* table 8 on page 24 in datasheet */
#define PWDOWN_MODE_SEL_MASK        0x03    // power down mask
#define PWDOWN_BETWEEN_CONV         0x00    // power down between conversions
#define PWDOWN_REFOFF_ADCON         0x01    // reference is off, ADC on
#define PWDOWN_REFON_ADC_OFF        0x02    // reference is on, ADC off
#define PWDOWN_ALWAYSON             0x03    // reference and ADC always on


#define CHANN_SEL_MASK              0x70
#define CHANN_TEMP0                 (0x00<<4)
#define CHANN_XP0                   (0x01<<4)
#define CHANN_VBAT                  (0x02<<4)
#define CHANN_XP1                   (0x03<<4)
#define CHANN_YN                    (0x04<<4)
#define CHANN_YP                    (0x05<<4)
#define CHANN_AUX                   (0x06<<4)
#define CHANN_TEMP1                 (0x07<<4)

// conversion mode select bit
#define CONV_MODE_12BIT             (0x00<<3)
#define CONV_MODE_8BIT              (0x01<<3)

// single-ended/differential reference select bit
#define SELBIT_DIFFREF              (0x00<<2)
#define SELBIT_SEREF                (0x01<<2)



typedef struct {
    char OptionByte;

    uint16_t adc_x;
    uint16_t adc_y;
    uint16_t adc_p;
    uint16_t temperature;

    struct {
        FunctionalState IsEnabled;
        FlagStatus      IsPressed;
        FlagStatus      TouchTimeoutOver;
    } Options;

} XPT_TypeDef;

extern XPT_TypeDef XPT;




void    XPT_Init(void);
void    XPT_Process(void);

void    SoftSpiSend( char* data, uint8_t len);
void    SoftSpiReceive( char* data, uint8_t len);


#endif /* XPT2046_H_INCLUDED */
