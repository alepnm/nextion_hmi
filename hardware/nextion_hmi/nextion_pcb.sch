EESchema Schematic File Version 4
LIBS:nextion_hmi-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ics:STM32F051C8Tx U2
U 1 1 5C091A1A
P 5900 3750
F 0 "U2" H 5850 3500 50  0000 L CNN
F 1 "STM32F051C8Tx" H 5600 3400 50  0000 L CNN
F 2 "" H 9350 4200 50  0001 R TNN
F 3 "www.st.com/resource/en/datasheet/stm32f051t8.pdf" H 8650 3900 50  0001 C CNN
F 4 "ZELM144" H 5900 3450 60  0001 C CNN "ventcode"
F 5 "-" H 7700 4100 60  0001 C CNN "Nominalas"
F 6 "0" H 8700 4000 60  0001 C CNN "Kaina"
F 7 "LQFP-48" H 9100 4000 60  0001 C CNN "Korpusas"
F 8 "1" H 9500 4000 60  0001 C CNN "Aukstis"
F 9 "-" H 7850 4100 60  0001 C CNN "Marke"
F 10 "Mikroschema" H 7950 4250 60  0001 C CNN "Pavadinimas"
F 11 "STM32F051C8Tx" H 8700 4250 60  0001 C CNN "Gamintojo Kodas"
F 12 "-" H 8050 4100 60  0001 C CNN "Nuoroda"
F 13 "SMD" H 8400 4000 60  0001 C CNN "Korpuso tipas"
F 14 "FLASH 64kB, RAM 16kB" H 8850 4100 60  0001 C CNN "Parametras"
F 15 "-" H 8200 4100 60  0001 C CNN "Komentaras"
	1    5900 3750
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-IC-Memory:W25Q32FVSS U5
U 1 1 5C091A22
P 2200 5000
F 0 "U5" H 1800 5300 45  0000 C CNN
F 1 "W25Q32FVSS" H 2200 5300 45  0000 C CNN
F 2 "" H 2200 5350 20  0001 C CNN
F 3 "" H 2200 5000 50  0001 C CNN
F 4 "IC-13229" H 2200 5331 60  0001 C CNN "Field4"
	1    2200 5000
	1    0    0    -1  
$EndComp
$Comp
L Driver_Display:XPT2046TS U4
U 1 1 5C091A29
P 5650 6950
F 0 "U4" H 5350 7400 50  0000 C CNN
F 1 "XPT2046TS" H 5950 7400 50  0000 C CNN
F 2 "" H 5650 6350 50  0001 C CIN
F 3 "http://www.xptek.com.cn/uploadfile/download/201707171401161883.pdf" H 5850 6400 50  0001 C CNN
	1    5650 6950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4850 3300 4400 3300
Text Label 4400 3300 0    50   ~ 0
~SDCS
Wire Wire Line
	4850 3400 4400 3400
Wire Wire Line
	4850 3500 4400 3500
Wire Wire Line
	4850 3800 4400 3800
Wire Wire Line
	4850 3900 4400 3900
Wire Wire Line
	4850 4100 4400 4100
Wire Wire Line
	4850 4200 4400 4200
Wire Wire Line
	4850 4300 4400 4300
Text Label 4400 3400 0    50   ~ 0
~XPTREQ
Text Label 4400 3500 0    50   ~ 0
~SDDETECT
Text Label 4400 4200 0    50   ~ 0
XPTOUT
Text Label 4400 4100 0    50   ~ 0
XPTIN
Text Label 4400 4300 0    50   ~ 0
~XPTCS
Wire Wire Line
	5350 4800 5350 5250
Wire Wire Line
	5450 4800 5450 5250
Wire Wire Line
	5550 4800 5550 5250
Wire Wire Line
	5650 4800 5650 5250
Wire Wire Line
	5750 4800 5750 5250
Wire Wire Line
	5850 4800 5850 5250
Wire Wire Line
	5950 4800 5950 5250
Wire Wire Line
	6050 4800 6050 5250
Wire Wire Line
	6150 4800 6150 5250
Wire Wire Line
	6250 4800 6250 5250
Wire Wire Line
	6350 4800 6350 5250
Wire Wire Line
	6450 4800 6450 5250
Text Label 5350 5250 1    50   ~ 0
XPTCLK
Text Label 5450 5250 1    50   ~ 0
~W25QCS
Text Label 5550 5250 1    50   ~ 0
SPI_SCK
Text Label 5650 5250 1    50   ~ 0
SPI_MISO
Text Label 5750 5250 1    50   ~ 0
SPI_MOSI
Text Label 5850 5250 1    50   ~ 0
LCD_DB0
Text Label 5950 5250 1    50   ~ 0
LCD_DB1
Text Label 6050 5250 1    50   ~ 0
LCD_DB2
Text Label 6150 5250 1    50   ~ 0
LCD_DB10
Text Label 6250 5250 1    50   ~ 0
LCD_DB11
Wire Wire Line
	6950 4300 7550 4300
Wire Wire Line
	6950 4200 7550 4200
Wire Wire Line
	6950 4100 7550 4100
Wire Wire Line
	6950 4000 7550 4000
Wire Wire Line
	6950 3900 7550 3900
Wire Wire Line
	6950 3800 7550 3800
Wire Wire Line
	6950 3600 7550 3600
Wire Wire Line
	6950 3500 7550 3500
Wire Wire Line
	6950 3400 7550 3400
Wire Wire Line
	6950 3300 7550 3300
Wire Wire Line
	6950 3200 7550 3200
Text Label 7550 4300 2    50   ~ 0
LCD_DB12
Text Label 7550 4200 2    50   ~ 0
LCD_DB13
Text Label 7550 4100 2    50   ~ 0
LCD_DB14
Text Label 7550 4000 2    50   ~ 0
LCD_DB15
Text Label 7550 3900 2    50   ~ 0
DISPLAY_LED
Text Label 7550 3800 2    50   ~ 0
DATA_TX
Text Label 7550 3700 2    50   ~ 0
DATA_RX
Text Label 7550 3600 2    50   ~ 0
LCD_RD
Text Label 7550 3500 2    50   ~ 0
LCD_WR
Text Label 7550 3400 2    50   ~ 0
SWDIO
Text Label 7550 3300 2    50   ~ 0
LCD_CS
Text Label 7550 3200 2    50   ~ 0
LCD_RST
Wire Wire Line
	6450 2700 6450 2250
Wire Wire Line
	6350 2700 6350 2250
Wire Wire Line
	6250 2700 6250 2250
Wire Wire Line
	6150 2700 6150 2250
Wire Wire Line
	6050 2700 6050 2250
Wire Wire Line
	5950 2700 5950 2250
Wire Wire Line
	5850 2700 5850 2250
Wire Wire Line
	5650 2700 5650 2250
Wire Wire Line
	5550 2700 5550 2250
Wire Wire Line
	5450 2700 5450 2250
Wire Wire Line
	5350 2700 5350 2600
Text Label 6450 2250 3    50   ~ 0
SWCLK
Text Label 6350 2250 3    50   ~ 0
LCD_RS
Text Label 6250 2250 3    50   ~ 0
LCD_DB3
Text Label 6150 2250 3    50   ~ 0
LCD_DB4
Text Label 6050 2250 3    50   ~ 0
LCD_DB5
Text Label 5950 2250 3    50   ~ 0
LCD_DB6
Text Label 5850 2250 3    50   ~ 0
LCD_DB7
Text Label 5650 2250 3    50   ~ 0
LCD_DB8
Text Label 5550 2250 3    50   ~ 0
LCD_DB9
Text Label 5450 2250 3    50   ~ 0
GND
Text Label 4400 3900 0    50   ~ 0
GND
Text Label 6350 5250 1    50   ~ 0
GND
Text Label 4400 3800 0    50   ~ 0
~NRST
Text Label 4400 4000 0    50   ~ 0
VDD
Text Label 5350 2250 3    50   ~ 0
VDD
Text Label 6450 5250 1    50   ~ 0
VDD
Wire Wire Line
	5750 6450 5750 6250
Wire Wire Line
	5750 6250 5650 6250
Wire Wire Line
	5650 6250 5650 6450
Wire Wire Line
	5650 7450 5650 7650
Text Label 5650 7650 1    50   ~ 0
GND
Text Label 6000 6250 2    50   ~ 0
VDD
Wire Wire Line
	5750 6250 6000 6250
Connection ~ 5750 6250
Wire Wire Line
	6150 6650 6500 6650
Wire Wire Line
	6150 6750 6500 6750
Wire Wire Line
	6150 6850 6500 6850
Wire Wire Line
	6150 6950 6500 6950
Wire Wire Line
	5150 7050 4800 7050
Wire Wire Line
	5150 6850 4800 6850
Wire Wire Line
	5150 6750 4800 6750
Wire Wire Line
	5150 6650 4800 6650
Text Label 4800 6750 0    50   ~ 0
XPTIN
Text Label 4800 6650 0    50   ~ 0
XPTOUT
Text Label 4800 6850 0    50   ~ 0
XPTCLK
Text Label 3950 7150 0    50   ~ 0
~XPTREQ
Text Label 4800 7050 0    50   ~ 0
~XPTCS
Text Label 6500 6650 2    50   ~ 0
XP
Text Label 6500 6750 2    50   ~ 0
YP
Text Label 6500 6850 2    50   ~ 0
XN
Text Label 6500 6950 2    50   ~ 0
YN
$Comp
L Device:R R12
U 1 1 5C091A9F
P 4400 6900
F 0 "R12" H 4470 6946 50  0000 L CNN
F 1 "10k" H 4470 6855 50  0000 L CNN
F 2 "" V 4330 6900 50  0001 C CNN
F 3 "~" H 4400 6900 50  0001 C CNN
	1    4400 6900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1600 4850 1100 4850
Wire Wire Line
	1600 4950 1100 4950
Wire Wire Line
	1600 5050 1100 5050
Wire Wire Line
	1600 5150 1100 5150
Wire Wire Line
	2800 4950 3250 4950
Wire Wire Line
	2800 5050 3250 5050
Wire Wire Line
	2800 5150 3250 5150
Text Label 1100 4850 0    50   ~ 0
~W25QCS
Text Label 3250 4850 2    50   ~ 0
VDD
Text Label 1100 5150 0    50   ~ 0
GND
Text Label 1100 4950 0    50   ~ 0
SPI_MISO
Text Label 3250 5150 2    50   ~ 0
SPI_MOSI
Text Label 3250 5050 2    50   ~ 0
SPI_SCK
Text Label 1100 5050 0    50   ~ 0
VDD
Wire Wire Line
	2800 4850 2900 4850
Text Label 3250 4950 2    50   ~ 0
5VDC
$Comp
L Device:C C6
U 1 1 5C091AB6
P 2650 4500
F 0 "C6" V 2490 4500 50  0000 C CNN
F 1 "C" V 2489 4500 50  0001 C CNN
F 2 "" H 2688 4350 50  0001 C CNN
F 3 "~" H 2650 4500 50  0001 C CNN
	1    2650 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 4500 2250 4500
Wire Wire Line
	2800 4500 2900 4500
Wire Wire Line
	2900 4500 2900 4850
Connection ~ 2900 4850
Wire Wire Line
	2900 4850 3250 4850
Text Label 2250 4500 0    50   ~ 0
GND
Text Label 1500 1700 0    50   ~ 0
GND
$Comp
L Device:C C7
U 1 1 5C091AC4
P 5400 6250
F 0 "C7" V 5240 6250 50  0000 C CNN
F 1 "C" V 5239 6250 50  0001 C CNN
F 2 "" H 5438 6100 50  0001 C CNN
F 3 "~" H 5400 6250 50  0001 C CNN
	1    5400 6250
	0    -1   1    0   
$EndComp
Wire Wire Line
	5650 6250 5550 6250
Connection ~ 5650 6250
Wire Wire Line
	5250 6250 5050 6250
Text Label 5050 6250 0    50   ~ 0
GND
Wire Wire Line
	4400 7050 4400 7150
Wire Wire Line
	4400 6750 4400 6550
Text Label 4400 6550 3    50   ~ 0
VDD
Connection ~ 4400 7150
Wire Wire Line
	4400 7150 3950 7150
$Comp
L Device:C C4
U 1 1 5C091AD4
P 5100 2600
F 0 "C4" V 4940 2600 50  0000 C CNN
F 1 "C" V 4939 2600 50  0001 C CNN
F 2 "" H 5138 2450 50  0001 C CNN
F 3 "~" H 5100 2600 50  0001 C CNN
	1    5100 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 2600 5350 2600
Connection ~ 5350 2600
Wire Wire Line
	5350 2600 5350 2250
Wire Wire Line
	4950 2600 4700 2600
Text Label 4700 2600 0    50   ~ 0
GND
Wire Wire Line
	9050 1500 8700 1500
Text Label 8700 1500 0    50   ~ 0
VDD
Wire Wire Line
	9050 1300 8750 1300
Wire Wire Line
	9050 1400 8550 1400
$Comp
L Device:R R2
U 1 1 5C091AE4
P 8750 1050
F 0 "R2" V 8650 1000 50  0000 C CNN
F 1 "4k7" V 8650 1150 50  0000 C CNN
F 2 "" V 8680 1050 50  0001 C CNN
F 3 "~" H 8750 1050 50  0001 C CNN
	1    8750 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8750 1200 8750 1300
Connection ~ 8750 1300
Wire Wire Line
	8750 1300 7950 1300
$Comp
L Device:R R3
U 1 1 5C091AEE
P 8550 1050
F 0 "R3" V 8450 1000 50  0000 C CNN
F 1 "4k7" V 8450 1150 50  0000 C CNN
F 2 "" V 8480 1050 50  0001 C CNN
F 3 "~" H 8550 1050 50  0001 C CNN
	1    8550 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8550 1200 8550 1400
Connection ~ 8550 1400
Wire Wire Line
	8550 1400 7950 1400
Wire Wire Line
	8550 900  8550 800 
Wire Wire Line
	8550 800  8750 800 
Wire Wire Line
	8750 800  8750 900 
Wire Wire Line
	8750 800  9100 800 
Connection ~ 8750 800 
Text Label 9100 800  2    50   ~ 0
VDD
$Comp
L Device:R R4
U 1 1 5C091AFE
P 8350 1050
F 0 "R4" V 8250 1000 50  0000 C CNN
F 1 "4k7" V 8250 1150 50  0000 C CNN
F 2 "" V 8280 1050 50  0001 C CNN
F 3 "~" H 8350 1050 50  0001 C CNN
	1    8350 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8350 1200 8350 1600
Wire Wire Line
	8350 1600 9050 1600
Wire Wire Line
	8350 1600 7950 1600
Connection ~ 8350 1600
Wire Wire Line
	8350 900  8350 800 
Wire Wire Line
	8350 800  8550 800 
Connection ~ 8550 800 
Text Label 8700 1700 0    50   ~ 0
GND
Wire Wire Line
	9050 1800 8750 1800
$Comp
L Device:R R5
U 1 1 5C091B0E
P 8750 2250
F 0 "R5" V 8650 2200 50  0000 C CNN
F 1 "4k7" V 8650 2350 50  0000 C CNN
F 2 "" V 8680 2250 50  0001 C CNN
F 3 "~" H 8750 2250 50  0001 C CNN
	1    8750 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	8750 2100 8750 1800
Connection ~ 8750 1800
Wire Wire Line
	8750 1800 7950 1800
Wire Wire Line
	8750 2400 8750 2500
Wire Wire Line
	9050 2000 8350 2000
$Comp
L Device:R R1
U 1 1 5C091B1A
P 8350 2250
F 0 "R1" V 8250 2200 50  0000 C CNN
F 1 "10k" V 8250 2350 50  0000 C CNN
F 2 "" V 8280 2250 50  0001 C CNN
F 3 "~" H 8350 2250 50  0001 C CNN
	1    8350 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	8350 2400 8350 2500
Wire Wire Line
	8350 2500 8750 2500
Connection ~ 8750 2500
Wire Wire Line
	8750 2500 9150 2500
Text Label 9150 2500 2    50   ~ 0
VDD
Wire Wire Line
	8350 2100 8350 2000
Connection ~ 8350 2000
Wire Wire Line
	8350 2000 7950 2000
$Comp
L mech:X_Micro_SD_Card_Det K1
U 1 1 5C091B35
P 9950 1600
F 0 "K1" H 10350 2300 50  0000 R CNN
F 1 "X_Micro_SD_Card_Det" V 9850 1070 50  0001 R CNN
F 2 "" H 12000 2300 50  0001 C CNN
F 3 "https://www.tme.eu/lt/Document/83ba12ba0c08b3a2f6df6fc72128cfd8/MCC-SDMICRO3.pdf" H 9850 1000 50  0001 C CNN
F 4 "ZAJ343" H 9400 2400 60  0001 C CNN "ventcode"
F 5 "-" H 9500 2500 60  0001 C CNN "Nominalas"
F 6 "0.84" H 9600 2600 60  0001 C CNN "Kaina"
F 7 "-" H 9700 2700 60  0001 C CNN "Korpusas"
F 8 "2" H 9800 2800 60  0001 C CNN "Aukstis"
F 9 "MMC-SDMICRO/3" H 9900 2900 60  0001 C CNN "Marke"
F 10 "Jungtis" H 10000 3000 60  0001 C CNN "Pavadinimas"
F 11 "112J-TDAR-R01" H 10100 3100 60  0001 C CNN "Gamintojo Kodas"
F 12 "https://www.tme.eu/lt/details/mcc-sdmicro_3/jungtys-kortelems/attend/112j-tdar-r01/" H 10200 3200 60  0001 C CNN "Nuoroda"
F 13 "SMT" H 10300 3300 60  0001 C CNN "Korpuso tipas"
F 14 "-" H 10400 3400 60  0001 C CNN "Parametras"
F 15 "-" H 10500 3500 60  0001 C CNN "Komentaras"
	1    9950 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 1700 8700 1700
Text Label 7950 1600 0    50   ~ 0
SPI_SCK
Text Label 7950 2000 0    50   ~ 0
~SDDETECT
Text Label 7950 1300 0    50   ~ 0
~SDCS
Wire Wire Line
	5150 7150 4400 7150
Wire Wire Line
	1400 1550 1950 1550
Wire Wire Line
	1400 1450 2400 1450
Text Label 2400 1450 2    50   ~ 0
DAT_TX
Text Label 2400 1550 2    50   ~ 0
DAT_RX
$Comp
L SparkFun-Connectors:CONN_05SMD J2
U 1 1 5C091B4F
P 2900 3100
F 0 "J2" H 2800 3600 45  0000 C CNN
F 1 "SWD" V 2650 3300 45  0000 C CNN
F 2 "1X01" H 2900 3300 20  0001 C CNN
F 3 "" H 2900 3100 50  0001 C CNN
F 4 "XXX-00000" H 2857 2969 60  0001 C CNN "Field4"
	1    2900 3100
	-1   0    0    -1  
$EndComp
Text Label 1650 3400 0    50   ~ 0
GND
Text Label 1650 2600 0    50   ~ 0
VDD
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 5C091B74
P 3300 1300
F 0 "U1" H 3300 1450 50  0000 C CNN
F 1 "AMS1117-3.3" H 3300 1451 50  0001 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3300 1500 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 3400 1050 50  0001 C CNN
	1    3300 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C091B7B
P 2850 1500
F 0 "C1" H 2600 1550 50  0000 L CNN
F 1 "C" V 2689 1500 50  0001 C CNN
F 2 "" H 2888 1350 50  0001 C CNN
F 3 "~" H 2850 1500 50  0001 C CNN
	1    2850 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1300 2850 1300
Wire Wire Line
	2850 1300 2850 1350
Wire Wire Line
	2850 1650 2850 1700
Wire Wire Line
	2850 1700 3300 1700
Wire Wire Line
	3300 1700 3300 1600
$Comp
L Device:C C2
U 1 1 5C091B87
P 3750 1500
F 0 "C2" H 3900 1550 50  0000 L CNN
F 1 "C" V 3589 1500 50  0001 C CNN
F 2 "" H 3788 1350 50  0001 C CNN
F 3 "~" H 3750 1500 50  0001 C CNN
	1    3750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1300 3750 1300
Wire Wire Line
	3750 1300 3750 1350
Wire Wire Line
	3300 1700 3750 1700
Wire Wire Line
	3750 1700 3750 1650
Connection ~ 3300 1700
Wire Wire Line
	4400 4000 4850 4000
Wire Wire Line
	3750 1300 4150 1300
Connection ~ 3750 1300
Connection ~ 2850 1300
Text Label 1500 1300 0    50   ~ 0
5VDC
Text Label 4000 1300 2    50   ~ 0
VDD
Connection ~ 2850 1700
Text Label 2000 2800 0    50   ~ 0
SWDIO
Text Label 1650 3000 0    50   ~ 0
~NRST
Text Label 2000 2900 0    50   ~ 0
SWCLK
Text Label 7950 1400 0    50   ~ 0
SPI_MOSI
Text Label 7950 1800 0    50   ~ 0
SPI_MISO
$Comp
L Device:C C5
U 1 1 5C091BA2
P 1400 3200
F 0 "C5" H 1450 3300 50  0000 L CNN
F 1 "C" V 1239 3200 50  0001 C CNN
F 2 "" H 1438 3050 50  0001 C CNN
F 3 "~" H 1400 3200 50  0001 C CNN
	1    1400 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5C091BA9
P 1400 2800
F 0 "R9" H 1470 2846 50  0000 L CNN
F 1 "10k" H 1470 2755 50  0000 L CNN
F 2 "" V 1330 2800 50  0001 C CNN
F 3 "~" H 1400 2800 50  0001 C CNN
	1    1400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 3050 1400 3000
Connection ~ 1400 3000
Wire Wire Line
	1400 3000 1400 2950
$Comp
L Transistor_BJT:BC817 Q2
U 1 1 5C091BB3
P 2400 7050
F 0 "Q2" H 2591 7096 50  0000 L CNN
F 1 "BC817" H 2591 7005 50  0000 L CNN
F 2 "" H 2600 6975 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 2400 7050 50  0001 L CNN
	1    2400 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 7250 2500 7450
Text Label 2900 7450 2    50   ~ 0
GND
$Comp
L Device:R R8
U 1 1 5C091BBC
P 2500 6600
F 0 "R8" H 2570 6646 50  0000 L CNN
F 1 "2R7" H 2570 6555 50  0000 L CNN
F 2 "" V 2430 6600 50  0001 C CNN
F 3 "~" H 2500 6600 50  0001 C CNN
	1    2500 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6750 2500 6850
Wire Wire Line
	2500 6450 2500 6350
Wire Wire Line
	2500 6350 2900 6350
$Comp
L Device:R R7
U 1 1 5C091BC6
P 2050 7250
F 0 "R7" H 2120 7296 50  0000 L CNN
F 1 "10k" H 2120 7205 50  0000 L CNN
F 2 "" V 1980 7250 50  0001 C CNN
F 3 "~" H 2050 7250 50  0001 C CNN
	1    2050 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 7050 2050 7050
Wire Wire Line
	2050 7050 2050 7100
Wire Wire Line
	2050 7400 2050 7450
Wire Wire Line
	2050 7450 2500 7450
Connection ~ 2500 7450
Wire Wire Line
	2500 7450 2900 7450
$Comp
L Device:R R6
U 1 1 5C091BD3
P 1750 7050
F 0 "R6" V 1850 7100 50  0000 L CNN
F 1 "3R9" V 1850 6900 50  0000 L CNN
F 2 "" V 1680 7050 50  0001 C CNN
F 3 "~" H 1750 7050 50  0001 C CNN
	1    1750 7050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1900 7050 2050 7050
Connection ~ 2050 7050
Wire Wire Line
	1600 7050 1000 7050
Text Label 1000 7050 0    50   ~ 0
DISPLAY_LED
Wire Wire Line
	4850 3200 4400 3200
Text Label 4400 3200 0    50   ~ 0
VDD
$Comp
L Device:R R10
U 1 1 5C091BE0
P 2350 3200
F 0 "R10" H 2100 3150 50  0000 L CNN
F 1 "10k" H 2100 3250 50  0000 L CNN
F 2 "" V 2280 3200 50  0001 C CNN
F 3 "~" H 2350 3200 50  0001 C CNN
	1    2350 3200
	1    0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 5C091BE7
P 2550 2700
F 0 "R11" V 2400 2750 50  0000 L CNN
F 1 "10k" V 2400 2550 50  0000 L CNN
F 2 "" V 2480 2700 50  0001 C CNN
F 3 "~" H 2550 2700 50  0001 C CNN
	1    2550 2700
	0    -1   1    0   
$EndComp
Wire Wire Line
	1400 3350 1400 3400
Wire Wire Line
	1400 2600 1400 2650
Wire Wire Line
	2350 3050 2350 2900
Connection ~ 2350 2900
Wire Wire Line
	2350 2900 2000 2900
Wire Wire Line
	2350 3400 2350 3350
Wire Wire Line
	1400 3400 2350 3400
Wire Wire Line
	2750 3400 2350 3400
Connection ~ 2350 3400
Wire Wire Line
	6950 3700 7550 3700
Text HLabel 1400 1300 0    50   Input ~ 0
5VDC
Text HLabel 1400 1450 0    50   Output ~ 0
DATA_TX
Text HLabel 1400 1550 0    50   Input ~ 0
DATA_RX
Text HLabel 1400 1700 0    50   UnSpc ~ 0
GND
Wire Wire Line
	1400 1700 2850 1700
$Comp
L Device:R R13
U 1 1 5C0E0A75
P 1950 1050
F 0 "R13" H 1700 1000 50  0000 L CNN
F 1 "10k" H 1700 1100 50  0000 L CNN
F 2 "" V 1880 1050 50  0001 C CNN
F 3 "~" H 1950 1050 50  0001 C CNN
	1    1950 1050
	1    0    0    1   
$EndComp
Wire Wire Line
	1950 1200 1950 1550
Connection ~ 1950 1550
Wire Wire Line
	1950 1550 2400 1550
Wire Wire Line
	1950 900  1950 700 
Wire Wire Line
	2750 2600 2750 2700
Wire Wire Line
	2750 2700 2800 2700
Wire Wire Line
	2350 2900 2800 2900
Wire Wire Line
	2750 3100 2800 3100
Wire Wire Line
	2750 3100 2750 3400
Wire Wire Line
	1400 3000 2800 3000
Wire Wire Line
	1400 2600 2750 2600
Wire Wire Line
	2000 2800 2350 2800
Wire Wire Line
	2400 2700 2350 2700
Wire Wire Line
	2350 2700 2350 2800
Connection ~ 2350 2800
Wire Wire Line
	2350 2800 2800 2800
Wire Wire Line
	2700 2700 2750 2700
Connection ~ 2750 2700
Wire Wire Line
	1400 1300 2850 1300
Text Label 1950 700  3    50   ~ 0
VDD
Text Label 2900 6350 2    50   ~ 0
LED
$Comp
L Connector_Generic:Conn_01x37 LCD1
U 1 1 5C2D85D0
P 10700 4450
F 0 "LCD1" H 10650 6400 50  0001 L CNN
F 1 "LCD Interface" V 10800 4150 50  0000 L CNN
F 2 "" H 10700 4450 50  0001 C CNN
F 3 "~" H 10700 4450 50  0001 C CNN
	1    10700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 2650 10050 2650
Wire Wire Line
	10500 2750 10400 2750
Wire Wire Line
	10500 2850 10400 2850
Wire Wire Line
	10400 2850 10400 2750
Connection ~ 10400 2750
Wire Wire Line
	10400 2750 10050 2750
Wire Wire Line
	10500 2950 10050 2950
Wire Wire Line
	10500 3050 10050 3050
Wire Wire Line
	10500 3150 10050 3150
Wire Wire Line
	10500 3250 10050 3250
Wire Wire Line
	10500 3350 10050 3350
Wire Wire Line
	10500 3450 10050 3450
Wire Wire Line
	10500 3550 10050 3550
Wire Wire Line
	10500 3650 10050 3650
Wire Wire Line
	10500 3750 10050 3750
Wire Wire Line
	10500 3850 10050 3850
Wire Wire Line
	10500 3950 10050 3950
Wire Wire Line
	10500 4050 10050 4050
Wire Wire Line
	10500 4150 10050 4150
Wire Wire Line
	10500 4250 10050 4250
Wire Wire Line
	10500 4350 10050 4350
Wire Wire Line
	10500 4450 10050 4450
Wire Wire Line
	10500 4550 10050 4550
Wire Wire Line
	10500 4650 10050 4650
Wire Wire Line
	10500 4750 10050 4750
Wire Wire Line
	10500 4850 10050 4850
Wire Wire Line
	10500 4950 10050 4950
Wire Wire Line
	10500 5050 10050 5050
Wire Wire Line
	10500 5150 10050 5150
Wire Wire Line
	10500 5250 10050 5250
Wire Wire Line
	10500 5350 10050 5350
Text Label 10050 2650 0    50   ~ 0
GND
Text Label 10050 2750 0    50   ~ 0
VDD
Text Label 10050 2950 0    50   ~ 0
LCD_CS
Text Label 10050 3050 0    50   ~ 0
LCD_RS
Text Label 10050 3150 0    50   ~ 0
LCD_WR
Text Label 10050 3250 0    50   ~ 0
LCD_RD
Text Label 10050 3350 0    50   ~ 0
LCD_RST
Text Label 10050 3450 0    50   ~ 0
LCD_DB0
Text Label 10050 3550 0    50   ~ 0
LCD_DB1
Text Label 10050 3650 0    50   ~ 0
LCD_DB2
Text Label 10050 3750 0    50   ~ 0
LCD_DB3
Text Label 10050 3850 0    50   ~ 0
LCD_DB4
Text Label 10050 3950 0    50   ~ 0
LCD_DB5
Text Label 10050 4050 0    50   ~ 0
LCD_DB6
Text Label 10050 4150 0    50   ~ 0
LCD_DB7
Text Label 10050 4250 0    50   ~ 0
LCD_DB8
Text Label 10050 4350 0    50   ~ 0
LCD_DB9
Text Label 10050 4450 0    50   ~ 0
LCD_DB10
Text Label 10050 4550 0    50   ~ 0
LCD_DB11
Text Label 10050 4650 0    50   ~ 0
LCD_DB12
Text Label 10050 4750 0    50   ~ 0
LCD_DB13
Text Label 10050 4850 0    50   ~ 0
LCD_DB14
Text Label 10050 4950 0    50   ~ 0
LCD_DB15
Text Label 10050 5050 0    50   ~ 0
GND
Text Label 10050 5150 0    50   ~ 0
YN
Text Label 10050 5250 0    50   ~ 0
XN
Text Label 10050 5350 0    50   ~ 0
YP
Wire Wire Line
	10500 5450 10050 5450
Wire Wire Line
	10500 5550 10400 5550
Wire Wire Line
	10500 6150 10050 6150
Wire Wire Line
	10500 6250 10050 6250
Text Label 10050 5450 0    50   ~ 0
XP
Wire Wire Line
	10500 6050 10400 6050
Wire Wire Line
	10400 6050 10400 5950
Connection ~ 10400 5550
Wire Wire Line
	10400 5550 10050 5550
Wire Wire Line
	10500 5650 10400 5650
Connection ~ 10400 5650
Wire Wire Line
	10400 5650 10400 5550
Wire Wire Line
	10500 5750 10400 5750
Connection ~ 10400 5750
Wire Wire Line
	10400 5750 10400 5650
Wire Wire Line
	10500 5850 10400 5850
Connection ~ 10400 5850
Wire Wire Line
	10400 5850 10400 5750
Wire Wire Line
	10500 5950 10400 5950
Connection ~ 10400 5950
Wire Wire Line
	10400 5950 10400 5850
Text Label 10050 5550 0    50   ~ 0
LED
Text Label 10050 6150 0    50   ~ 0
VDD
Text Label 10050 6250 0    50   ~ 0
GND
Wire Wire Line
	4850 3600 4150 3600
Wire Wire Line
	4850 3700 4150 3700
Text HLabel 4150 3600 0    50   Output ~ 0
PF0
Text HLabel 4150 3700 0    50   Input ~ 0
PF1
Text HLabel 4150 1300 2    50   Output ~ 0
VDD
$EndSCHEMATC