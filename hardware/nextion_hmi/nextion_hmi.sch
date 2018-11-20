EESchema Schematic File Version 4
LIBS:nextion_hmi-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
L ics:STM32F051C8Tx U1
U 1 1 5BF26DB2
P 5650 4150
F 0 "U1" H 5600 3900 50  0000 L CNN
F 1 "STM32F051C8Tx" H 5350 3800 50  0000 L CNN
F 2 "" H 9100 4600 50  0001 R TNN
F 3 "www.st.com/resource/en/datasheet/stm32f051t8.pdf" H 8400 4300 50  0001 C CNN
F 4 "ZELM144" H 5650 3850 60  0001 C CNN "ventcode"
F 5 "-" H 7450 4500 60  0001 C CNN "Nominalas"
F 6 "0" H 8450 4400 60  0001 C CNN "Kaina"
F 7 "LQFP-48" H 8850 4400 60  0001 C CNN "Korpusas"
F 8 "1" H 9250 4400 60  0001 C CNN "Aukstis"
F 9 "-" H 7600 4500 60  0001 C CNN "Marke"
F 10 "Mikroschema" H 7700 4650 60  0001 C CNN "Pavadinimas"
F 11 "STM32F051C8Tx" H 8450 4650 60  0001 C CNN "Gamintojo Kodas"
F 12 "-" H 7800 4500 60  0001 C CNN "Nuoroda"
F 13 "SMD" H 8150 4400 60  0001 C CNN "Korpuso tipas"
F 14 "FLASH 64kB, RAM 16kB" H 8600 4500 60  0001 C CNN "Parametras"
F 15 "-" H 7950 4500 60  0001 C CNN "Komentaras"
	1    5650 4150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-IC-Memory:W25Q32FVSS U2
U 1 1 5BF26EDF
P 2050 4700
F 0 "U2" H 1650 5000 45  0000 C CNN
F 1 "W25Q32FVSS" H 2050 5000 45  0000 C CNN
F 2 "" H 2050 5050 20  0001 C CNN
F 3 "" H 2050 4700 50  0001 C CNN
F 4 "IC-13229" H 2050 5031 60  0001 C CNN "Field4"
	1    2050 4700
	1    0    0    -1  
$EndComp
$Comp
L Driver_Display:XPT2046TS U3
U 1 1 5BF27110
P 2050 6100
F 0 "U3" H 1750 6550 50  0000 C CNN
F 1 "XPT2046TS" H 2350 6550 50  0000 C CNN
F 2 "" H 2050 5500 50  0001 C CIN
F 3 "http://www.xptek.com.cn/uploadfile/download/201707171401161883.pdf" H 2250 5550 50  0001 C CNN
	1    2050 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3700 4150 3700
Text Label 4150 3700 0    50   ~ 0
~SDCS
Wire Wire Line
	4600 3800 4150 3800
Wire Wire Line
	4600 3900 4150 3900
Wire Wire Line
	4600 4200 4150 4200
Wire Wire Line
	4600 4300 4150 4300
Wire Wire Line
	4600 4500 4150 4500
Wire Wire Line
	4600 4600 4150 4600
Wire Wire Line
	4600 4700 4150 4700
Text Label 4150 3800 0    50   ~ 0
~XPTREQ
Text Label 4150 3900 0    50   ~ 0
~SDDETECT
Text Label 4150 4600 0    50   ~ 0
XPTOUT
Text Label 4150 4500 0    50   ~ 0
XPTIN
Text Label 4150 4700 0    50   ~ 0
~XPTCS
Wire Wire Line
	5100 5200 5100 5650
Wire Wire Line
	5200 5200 5200 5650
Wire Wire Line
	5300 5200 5300 5650
Wire Wire Line
	5400 5200 5400 5650
Wire Wire Line
	5500 5200 5500 5650
Wire Wire Line
	5600 5200 5600 5650
Wire Wire Line
	5700 5200 5700 5650
Wire Wire Line
	5800 5200 5800 5650
Wire Wire Line
	5900 5200 5900 5650
Wire Wire Line
	6000 5200 6000 5650
Wire Wire Line
	6100 5200 6100 5650
Wire Wire Line
	6200 5200 6200 5650
Text Label 5100 5650 1    50   ~ 0
XPTCLK
Text Label 5200 5650 1    50   ~ 0
~W25QCS
Text Label 5300 5650 1    50   ~ 0
SPI_SCK
Text Label 5400 5650 1    50   ~ 0
SPI_MISO
Text Label 5500 5650 1    50   ~ 0
SPI_MOSI
Text Label 5600 5650 1    50   ~ 0
LCD_DB0
Text Label 5700 5650 1    50   ~ 0
LCD_DB1
Text Label 5800 5650 1    50   ~ 0
LCD_DB2
Text Label 5900 5650 1    50   ~ 0
LCD_DB10
Text Label 6000 5650 1    50   ~ 0
LCD_DB11
Wire Wire Line
	6700 4700 7300 4700
Wire Wire Line
	6700 4600 7300 4600
Wire Wire Line
	6700 4500 7300 4500
Wire Wire Line
	6700 4400 7300 4400
Wire Wire Line
	6700 4300 7300 4300
Wire Wire Line
	6700 4200 7300 4200
Wire Wire Line
	6700 4000 7300 4000
Wire Wire Line
	6700 3900 7300 3900
Wire Wire Line
	6700 3800 7300 3800
Wire Wire Line
	6700 3700 7300 3700
Wire Wire Line
	6700 3600 7300 3600
Text Label 7300 4700 2    50   ~ 0
LCD_DB12
Text Label 7300 4600 2    50   ~ 0
LCD_DB13
Text Label 7300 4500 2    50   ~ 0
LCD_DB14
Text Label 7300 4400 2    50   ~ 0
LCD_DB15
Text Label 7300 4300 2    50   ~ 0
DISPLAY_LED
Text Label 7300 4200 2    50   ~ 0
DATA_TX
Text Label 7300 4100 2    50   ~ 0
DATA_RX
Text Label 7300 4000 2    50   ~ 0
LCD_RD
Text Label 7300 3900 2    50   ~ 0
LCD_WR
Text Label 7300 3800 2    50   ~ 0
SWDIO
Text Label 7300 3700 2    50   ~ 0
LCD_CS
Text Label 7300 3600 2    50   ~ 0
LCD_RST
Wire Wire Line
	6200 3100 6200 2650
Wire Wire Line
	6100 3100 6100 2650
Wire Wire Line
	6000 3100 6000 2650
Wire Wire Line
	5900 3100 5900 2650
Wire Wire Line
	5800 3100 5800 2650
Wire Wire Line
	5700 3100 5700 2650
Wire Wire Line
	5600 3100 5600 2650
Wire Wire Line
	5400 3100 5400 2650
Wire Wire Line
	5300 3100 5300 2650
Wire Wire Line
	5200 3100 5200 2650
Wire Wire Line
	5100 3100 5100 3000
Text Label 6200 2650 3    50   ~ 0
SWCLK
Text Label 6100 2650 3    50   ~ 0
LCD_RS
Text Label 6000 2650 3    50   ~ 0
LCD_DB3
Text Label 5900 2650 3    50   ~ 0
LCD_DB4
Text Label 5800 2650 3    50   ~ 0
LCD_DB5
Text Label 5700 2650 3    50   ~ 0
LCD_DB6
Text Label 5600 2650 3    50   ~ 0
LCD_DB7
Text Label 5400 2650 3    50   ~ 0
LCD_DB8
Text Label 5300 2650 3    50   ~ 0
LCD_DB9
Text Label 5200 2650 3    50   ~ 0
GND
Text Label 4150 4300 0    50   ~ 0
GND
Text Label 6100 5650 1    50   ~ 0
GND
Text Label 4150 4200 0    50   ~ 0
~NRST
Text Label 4150 4400 0    50   ~ 0
VDD
Text Label 5100 2650 3    50   ~ 0
VDD
Text Label 6200 5650 1    50   ~ 0
VDD
Wire Wire Line
	1950 5600 1950 5400
Wire Wire Line
	1950 5400 2050 5400
Wire Wire Line
	2050 5400 2050 5600
Wire Wire Line
	2050 6600 2050 6800
Text Label 2050 6800 1    50   ~ 0
GND
Text Label 1700 5400 0    50   ~ 0
VDD
Wire Wire Line
	1950 5400 1700 5400
Connection ~ 1950 5400
Wire Wire Line
	1550 5800 1200 5800
Wire Wire Line
	1550 5900 1200 5900
Wire Wire Line
	1550 6000 1200 6000
Wire Wire Line
	1550 6100 1200 6100
Wire Wire Line
	2550 6200 2900 6200
Wire Wire Line
	2550 6000 2900 6000
Wire Wire Line
	2550 5900 2900 5900
Wire Wire Line
	2550 5800 2900 5800
Text Label 2900 5900 2    50   ~ 0
XPTIN
Text Label 2900 5800 2    50   ~ 0
XPTOUT
Text Label 2900 6000 2    50   ~ 0
XPTCLK
Text Label 3750 6300 2    50   ~ 0
~XPTREQ
Text Label 2900 6200 2    50   ~ 0
~XPTCS
Text Label 1200 5800 0    50   ~ 0
XP
Text Label 1200 5900 0    50   ~ 0
YP
Text Label 1200 6000 0    50   ~ 0
XN
Text Label 1200 6100 0    50   ~ 0
YN
$Comp
L Device:R R12
U 1 1 5BF4363B
P 3300 6050
F 0 "R12" H 3370 6096 50  0000 L CNN
F 1 "10k" H 3370 6005 50  0000 L CNN
F 2 "" V 3230 6050 50  0001 C CNN
F 3 "~" H 3300 6050 50  0001 C CNN
	1    3300 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4550 950  4550
Wire Wire Line
	1450 4650 950  4650
Wire Wire Line
	1450 4750 950  4750
Wire Wire Line
	1450 4850 950  4850
Wire Wire Line
	2650 4650 3100 4650
Wire Wire Line
	2650 4750 3100 4750
Wire Wire Line
	2650 4850 3100 4850
Text Label 950  4550 0    50   ~ 0
~W25QCS
Text Label 3100 4550 2    50   ~ 0
VDD
Text Label 950  4850 0    50   ~ 0
GND
Text Label 950  4650 0    50   ~ 0
SPI_MISO
Text Label 3100 4850 2    50   ~ 0
SPI_MOSI
Text Label 3100 4750 2    50   ~ 0
SPI_SCK
Text Label 950  4750 0    50   ~ 0
VDD
Wire Wire Line
	2650 4550 2750 4550
Text Label 3100 4650 2    50   ~ 0
5VDC
$Comp
L Device:C C3
U 1 1 5BF60430
P 2500 4200
F 0 "C3" V 2340 4200 50  0000 C CNN
F 1 "C" V 2339 4200 50  0001 C CNN
F 2 "" H 2538 4050 50  0001 C CNN
F 3 "~" H 2500 4200 50  0001 C CNN
	1    2500 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	2350 4200 2100 4200
Wire Wire Line
	2650 4200 2750 4200
Wire Wire Line
	2750 4200 2750 4550
Connection ~ 2750 4550
Wire Wire Line
	2750 4550 3100 4550
Text Label 2100 4200 0    50   ~ 0
GND
Text Label 2650 3500 0    50   ~ 0
GND
$Comp
L Device:C C7
U 1 1 5BF6E0E3
P 2300 5400
F 0 "C7" V 2140 5400 50  0000 C CNN
F 1 "C" V 2139 5400 50  0001 C CNN
F 2 "" H 2338 5250 50  0001 C CNN
F 3 "~" H 2300 5400 50  0001 C CNN
	1    2300 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 5400 2150 5400
Connection ~ 2050 5400
Wire Wire Line
	2450 5400 2650 5400
Text Label 2650 5400 2    50   ~ 0
GND
Wire Wire Line
	3300 6200 3300 6300
Wire Wire Line
	3300 5900 3300 5700
Text Label 3300 5700 3    50   ~ 0
VDD
Connection ~ 3300 6300
Wire Wire Line
	3300 6300 3750 6300
$Comp
L Device:C C4
U 1 1 5BF8C142
P 4850 3000
F 0 "C4" V 4690 3000 50  0000 C CNN
F 1 "C" V 4689 3000 50  0001 C CNN
F 2 "" H 4888 2850 50  0001 C CNN
F 3 "~" H 4850 3000 50  0001 C CNN
	1    4850 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 3000 5100 3000
Connection ~ 5100 3000
Wire Wire Line
	5100 3000 5100 2650
Wire Wire Line
	4700 3000 4450 3000
Text Label 4450 3000 0    50   ~ 0
GND
Wire Wire Line
	9500 2450 9500 2800
Text Label 9500 2800 1    50   ~ 0
VDD
Wire Wire Line
	9300 2450 9300 2750
Wire Wire Line
	9400 2450 9400 2950
$Comp
L Device:R R2
U 1 1 5BF9B02B
P 9050 2750
F 0 "R2" V 8950 2700 50  0000 C CNN
F 1 "4k7" V 8950 2850 50  0000 C CNN
F 2 "" V 8980 2750 50  0001 C CNN
F 3 "~" H 9050 2750 50  0001 C CNN
	1    9050 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 2750 9300 2750
Connection ~ 9300 2750
Wire Wire Line
	9300 2750 9300 3550
$Comp
L Device:R R4
U 1 1 5BF9D1F6
P 9050 2950
F 0 "R4" V 8950 2900 50  0000 C CNN
F 1 "4k7" V 8950 3050 50  0000 C CNN
F 2 "" V 8980 2950 50  0001 C CNN
F 3 "~" H 9050 2950 50  0001 C CNN
	1    9050 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 2950 9400 2950
Connection ~ 9400 2950
Wire Wire Line
	9400 2950 9400 3550
Wire Wire Line
	8900 2950 8800 2950
Wire Wire Line
	8800 2950 8800 2750
Wire Wire Line
	8800 2750 8900 2750
Wire Wire Line
	8800 2750 8600 2750
Connection ~ 8800 2750
Text Label 8600 2750 0    50   ~ 0
VDD
$Comp
L Device:R R5
U 1 1 5BFAA312
P 9050 3150
F 0 "R5" V 8950 3100 50  0000 C CNN
F 1 "4k7" V 8950 3250 50  0000 C CNN
F 2 "" V 8980 3150 50  0001 C CNN
F 3 "~" H 9050 3150 50  0001 C CNN
	1    9050 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 3150 9600 3150
Wire Wire Line
	9600 3150 9600 2450
Wire Wire Line
	9600 3150 9600 3550
Connection ~ 9600 3150
Wire Wire Line
	8900 3150 8800 3150
Wire Wire Line
	8800 3150 8800 2950
Connection ~ 8800 2950
Text Label 9700 2800 1    50   ~ 0
GND
Wire Wire Line
	9800 2450 9800 2750
$Comp
L Device:R R3
U 1 1 5BFC2944
P 10250 2750
F 0 "R3" V 10150 2700 50  0000 C CNN
F 1 "4k7" V 10150 2850 50  0000 C CNN
F 2 "" V 10180 2750 50  0001 C CNN
F 3 "~" H 10250 2750 50  0001 C CNN
	1    10250 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	10100 2750 9800 2750
Connection ~ 9800 2750
Wire Wire Line
	9800 2750 9800 3550
Wire Wire Line
	10400 2750 10500 2750
Wire Wire Line
	10000 2450 10000 3150
$Comp
L Device:R R1
U 1 1 5BFCA9F4
P 10250 3150
F 0 "R1" V 10150 3100 50  0000 C CNN
F 1 "10k" V 10150 3250 50  0000 C CNN
F 2 "" V 10180 3150 50  0001 C CNN
F 3 "~" H 10250 3150 50  0001 C CNN
	1    10250 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	10400 3150 10500 3150
Wire Wire Line
	10500 3150 10500 2750
Connection ~ 10500 2750
Wire Wire Line
	10500 2750 10750 2750
Text Label 10750 2750 2    50   ~ 0
VDD
Wire Wire Line
	10100 3150 10000 3150
Connection ~ 10000 3150
Wire Wire Line
	10000 3150 10000 3550
$Comp
L mech:X_Micro_SD_Card_Det K1
U 1 1 5BFEA722
P 9600 1550
F 0 "K1" V 10450 2100 50  0000 R CNN
F 1 "X_Micro_SD_Card_Det" V 9500 1020 50  0001 R CNN
F 2 "" H 11650 2250 50  0001 C CNN
F 3 "https://www.tme.eu/lt/Document/83ba12ba0c08b3a2f6df6fc72128cfd8/MCC-SDMICRO3.pdf" H 9500 950 50  0001 C CNN
F 4 "ZAJ343" H 9050 2350 60  0001 C CNN "ventcode"
F 5 "-" H 9150 2450 60  0001 C CNN "Nominalas"
F 6 "0.84" H 9250 2550 60  0001 C CNN "Kaina"
F 7 "-" H 9350 2650 60  0001 C CNN "Korpusas"
F 8 "2" H 9450 2750 60  0001 C CNN "Aukstis"
F 9 "MMC-SDMICRO/3" H 9550 2850 60  0001 C CNN "Marke"
F 10 "Jungtis" H 9650 2950 60  0001 C CNN "Pavadinimas"
F 11 "112J-TDAR-R01" H 9750 3050 60  0001 C CNN "Gamintojo Kodas"
F 12 "https://www.tme.eu/lt/details/mcc-sdmicro_3/jungtys-kortelems/attend/112j-tdar-r01/" H 9850 3150 60  0001 C CNN "Nuoroda"
F 13 "SMT" H 9950 3250 60  0001 C CNN "Korpuso tipas"
F 14 "-" H 10050 3350 60  0001 C CNN "Parametras"
F 15 "-" H 10150 3450 60  0001 C CNN "Komentaras"
	1    9600 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 2450 9700 2800
Text Label 9600 3550 1    50   ~ 0
SPI_SCK
Text Label 10000 3550 1    50   ~ 0
~SDDETECT
Text Label 9300 3550 1    50   ~ 0
~SDCS
$Comp
L Device:R R13
U 1 1 5C0356BB
P 3700 1200
F 0 "R13" H 3770 1246 50  0000 L CNN
F 1 "10k" H 3770 1155 50  0000 L CNN
F 2 "" V 3630 1200 50  0001 C CNN
F 3 "~" H 3700 1200 50  0001 C CNN
	1    3700 1200
	1    0    0    -1  
$EndComp
Text Label 3700 850  3    50   ~ 0
VDD
Wire Wire Line
	2550 6300 3300 6300
$Comp
L SparkFun-Connectors:CONN_04LOCK J6
U 1 1 5C0A3E06
P 1250 3400
F 0 "J6" H 1150 3800 45  0000 C CNN
F 1 "UART" V 1000 3550 45  0000 C CNN
F 2 "" H 1250 3900 20  0001 C CNN
F 3 "" H 1250 3400 50  0001 C CNN
F 4 "CONN-09696" H 1206 3831 60  0001 C CNN "Field4"
	1    1250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3400 1450 3400
Wire Wire Line
	1350 3300 1700 3300
Wire Wire Line
	1350 3200 1700 3200
Text Label 1700 3200 2    50   ~ 0
DAT_TX
Text Label 1700 3300 2    50   ~ 0
DAT_RX
$Sheet
S 2250 1250 1000 600 
U 5BF96868
F0 "UART konverteris" 50
F1 "uart_conv.sch" 50
F2 "DATA" B L 2250 1550 50 
F3 "MCURX" O R 3250 1650 50 
F4 "12VDC" I L 2250 1450 50 
F5 "MCUTX" I R 3250 1550 50 
F6 "5VDC" I R 3250 1450 50 
F7 "COM" U L 2250 1650 50 
$EndSheet
Wire Wire Line
	3850 1450 3250 1450
Wire Wire Line
	4150 1550 3250 1550
Wire Wire Line
	3850 1650 3700 1650
Text Label 3750 1900 0    50   ~ 0
GND
Wire Wire Line
	2250 1450 1850 1450
Wire Wire Line
	2250 1650 1850 1650
Text Label 1950 1550 0    50   ~ 0
DATA
Text Label 1950 1450 0    50   ~ 0
12VDC
Text Label 1950 1650 0    50   ~ 0
GND
$Comp
L SparkFun-Connectors:CONN_01 J1
U 1 1 5C019D8D
P 3950 1450
F 0 "J1" H 3850 1250 45  0001 C CNN
F 1 "5VDC" H 3850 1450 45  0000 C CNN
F 2 "1X01" H 3950 1650 20  0001 C CNN
F 3 "" H 3950 1450 50  0001 C CNN
F 4 "XXX-00000" H 3907 1319 60  0001 C CNN "Field4"
	1    3950 1450
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J4
U 1 1 5C019FF7
P 4250 1550
F 0 "J4" H 4150 1350 45  0001 C CNN
F 1 "TX" H 4150 1550 45  0000 C CNN
F 2 "1X01" H 4250 1750 20  0001 C CNN
F 3 "" H 4250 1550 50  0001 C CNN
F 4 "XXX-00000" H 4207 1419 60  0001 C CNN "Field4"
	1    4250 1550
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J5
U 1 1 5C01A512
P 3950 1650
F 0 "J5" H 3850 1450 45  0001 C CNN
F 1 "RX" H 3850 1650 45  0000 C CNN
F 2 "1X01" H 3950 1850 20  0001 C CNN
F 3 "" H 3950 1650 50  0001 C CNN
F 4 "XXX-00000" H 3907 1519 60  0001 C CNN "Field4"
	1    3950 1650
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J7
U 1 1 5C01A565
P 4250 1750
F 0 "J7" H 4150 1550 45  0001 C CNN
F 1 "GND" H 4150 1750 45  0000 C CNN
F 2 "1X01" H 4250 1950 20  0001 C CNN
F 3 "" H 4250 1750 50  0001 C CNN
F 4 "XXX-00000" H 4207 1619 60  0001 C CNN "Field4"
	1    4250 1750
	-1   0    0    1   
$EndComp
$Comp
L Connector:RJ45_Shielded J3
U 1 1 5C048F23
P 1250 1600
F 0 "J3" H 1305 2176 50  0000 C CNN
F 1 "RJ45_Shielded" H 1305 2176 50  0001 C CNN
F 2 "Connectors:RJ45_8" V 1250 1625 50  0001 C CNN
F 3 "~" V 1250 1625 50  0001 C CNN
	1    1250 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1200 1850 1200
Wire Wire Line
	1850 1200 1850 1300
Wire Wire Line
	1850 1300 1650 1300
Wire Wire Line
	1650 1900 1850 1900
Wire Wire Line
	1850 1900 1850 1800
Wire Wire Line
	1850 1800 1650 1800
Wire Wire Line
	1250 2100 1250 2200
Wire Wire Line
	1250 2200 1850 2200
Wire Wire Line
	1850 2200 1850 1900
Connection ~ 1850 1900
Wire Wire Line
	1850 1800 1850 1650
Connection ~ 1850 1800
Wire Wire Line
	1850 1300 1850 1450
Connection ~ 1850 1300
Wire Wire Line
	1650 1500 1750 1500
Wire Wire Line
	1750 1500 1750 1550
Wire Wire Line
	1750 1550 2250 1550
Wire Wire Line
	4150 1750 4050 1750
Wire Wire Line
	4050 1750 4050 1900
Wire Wire Line
	4050 1900 3750 1900
$Comp
L SparkFun-Connectors:CONN_01 J11
U 1 1 5BF4009B
P 6600 1050
F 0 "J11" H 6500 850 45  0001 C CNN
F 1 "VDD" H 6500 1050 45  0000 C CNN
F 2 "1X01" H 6600 1250 20  0001 C CNN
F 3 "" H 6600 1050 50  0001 C CNN
F 4 "XXX-00000" H 6557 919 60  0001 C CNN "Field4"
	1    6600 1050
	-1   0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J10
U 1 1 5BF4012B
P 6600 1200
F 0 "J10" H 6500 1000 45  0001 C CNN
F 1 "DIO" H 6500 1200 45  0000 C CNN
F 2 "1X01" H 6600 1400 20  0001 C CNN
F 3 "" H 6600 1200 50  0001 C CNN
F 4 "XXX-00000" H 6557 1069 60  0001 C CNN "Field4"
	1    6600 1200
	-1   0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J9
U 1 1 5BF4015A
P 6600 1350
F 0 "J9" H 6500 1150 45  0001 C CNN
F 1 "CLK" H 6500 1350 45  0000 C CNN
F 2 "1X01" H 6600 1550 20  0001 C CNN
F 3 "" H 6600 1350 50  0001 C CNN
F 4 "XXX-00000" H 6557 1219 60  0001 C CNN "Field4"
	1    6600 1350
	-1   0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J8
U 1 1 5BF40189
P 6600 1500
F 0 "J8" H 6500 1300 45  0001 C CNN
F 1 "~RST" H 6500 1500 45  0000 C CNN
F 2 "1X01" H 6600 1700 20  0001 C CNN
F 3 "" H 6600 1500 50  0001 C CNN
F 4 "XXX-00000" H 6557 1369 60  0001 C CNN "Field4"
	1    6600 1500
	-1   0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_01 J2
U 1 1 5BF401B8
P 6600 1650
F 0 "J2" H 6500 1550 45  0000 C CNN
F 1 "GND" H 6500 1650 45  0000 C CNN
F 2 "1X01" H 6600 1850 20  0001 C CNN
F 3 "" H 6600 1650 50  0001 C CNN
F 4 "XXX-00000" H 6557 1519 60  0001 C CNN "Field4"
	1    6600 1650
	-1   0    0    -1  
$EndComp
Text Label 5700 1900 0    50   ~ 0
GND
Text Label 5700 1050 0    50   ~ 0
VDD
$Comp
L Regulator_Linear:AMS1117-3.3 U5
U 1 1 5BF63F53
P 2450 3100
F 0 "U5" H 2450 3250 50  0000 C CNN
F 1 "AMS1117-3.3" H 2450 3251 50  0001 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 2450 3300 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 2550 2850 50  0001 C CNN
	1    2450 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5BF63FC3
P 2000 3300
F 0 "C1" H 1800 3400 50  0000 L CNN
F 1 "C" V 1839 3300 50  0001 C CNN
F 2 "" H 2038 3150 50  0001 C CNN
F 3 "~" H 2000 3300 50  0001 C CNN
	1    2000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3100 2000 3100
Wire Wire Line
	2000 3100 2000 3150
Wire Wire Line
	2000 3450 2000 3500
Wire Wire Line
	2000 3500 2450 3500
Wire Wire Line
	2450 3500 2450 3400
$Comp
L Device:C C2
U 1 1 5BF70806
P 2950 3300
F 0 "C2" H 3000 3400 50  0000 L CNN
F 1 "C" V 2789 3300 50  0001 C CNN
F 2 "" H 2988 3150 50  0001 C CNN
F 3 "~" H 2950 3300 50  0001 C CNN
	1    2950 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3100 2950 3100
Wire Wire Line
	2950 3100 2950 3150
Wire Wire Line
	2450 3500 2950 3500
Wire Wire Line
	2950 3500 2950 3450
Connection ~ 2450 3500
Wire Wire Line
	4150 4400 4600 4400
Wire Wire Line
	2950 3100 3300 3100
Connection ~ 2950 3100
Wire Wire Line
	2000 3100 1350 3100
Connection ~ 2000 3100
Text Label 1450 3100 0    50   ~ 0
5VDC
Text Label 3300 3100 2    50   ~ 0
VDD
Text Label 3350 1450 0    50   ~ 0
5VDC
Wire Wire Line
	2000 3500 1450 3500
Wire Wire Line
	1450 3500 1450 3400
Connection ~ 2000 3500
Text Label 5700 1200 0    50   ~ 0
SWDIO
Text Label 5700 1500 0    50   ~ 0
~NRST
Text Label 5700 1350 0    50   ~ 0
SWCLK
Text Label 9400 3550 1    50   ~ 0
SPI_MOSI
Text Label 9800 3550 1    50   ~ 0
SPI_MISO
$Comp
L Device:C C5
U 1 1 5C030F20
P 5250 1700
F 0 "C5" H 5300 1800 50  0000 L CNN
F 1 "C" V 5089 1700 50  0001 C CNN
F 2 "" H 5288 1550 50  0001 C CNN
F 3 "~" H 5250 1700 50  0001 C CNN
	1    5250 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5C030FA8
P 5250 1300
F 0 "R9" H 5320 1346 50  0000 L CNN
F 1 "10k" H 5320 1255 50  0000 L CNN
F 2 "" V 5180 1300 50  0001 C CNN
F 3 "~" H 5250 1300 50  0001 C CNN
	1    5250 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1550 5250 1500
Connection ~ 5250 1500
Wire Wire Line
	5250 1500 5250 1450
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 5C053280
P 9850 5400
F 0 "Q1" H 10041 5446 50  0000 L CNN
F 1 "BC817" H 10041 5355 50  0000 L CNN
F 2 "" H 10050 5325 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 9850 5400 50  0001 L CNN
	1    9850 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 5600 9950 5800
Text Label 10350 5800 2    50   ~ 0
GND
$Comp
L Device:R R8
U 1 1 5C0616EF
P 9950 4950
F 0 "R8" H 10020 4996 50  0000 L CNN
F 1 "2R7" H 10020 4905 50  0000 L CNN
F 2 "" V 9880 4950 50  0001 C CNN
F 3 "~" H 9950 4950 50  0001 C CNN
	1    9950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 5100 9950 5200
Wire Wire Line
	9950 4800 9950 4700
Wire Wire Line
	9950 4700 10350 4700
$Comp
L Device:R R7
U 1 1 5C06FA6B
P 9500 5600
F 0 "R7" H 9570 5646 50  0000 L CNN
F 1 "10k" H 9570 5555 50  0000 L CNN
F 2 "" V 9430 5600 50  0001 C CNN
F 3 "~" H 9500 5600 50  0001 C CNN
	1    9500 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5400 9500 5400
Wire Wire Line
	9500 5400 9500 5450
Wire Wire Line
	9500 5750 9500 5800
Wire Wire Line
	9500 5800 9950 5800
Connection ~ 9950 5800
Wire Wire Line
	9950 5800 10350 5800
$Comp
L Device:R R6
U 1 1 5C0B2815
P 9200 5400
F 0 "R6" V 9300 5450 50  0000 L CNN
F 1 "3R9" V 9300 5250 50  0000 L CNN
F 2 "" V 9130 5400 50  0001 C CNN
F 3 "~" H 9200 5400 50  0001 C CNN
	1    9200 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 5400 9500 5400
Connection ~ 9500 5400
Wire Wire Line
	9050 5400 8450 5400
Text Label 8450 5400 0    50   ~ 0
DISPLAY_LED
Wire Wire Line
	4600 3600 4150 3600
Text Label 4150 3600 0    50   ~ 0
VDD
$Comp
L Device:R R10
U 1 1 5C0D2115
P 6200 1700
F 0 "R10" H 5950 1650 50  0000 L CNN
F 1 "10k" H 5950 1750 50  0000 L CNN
F 2 "" V 6130 1700 50  0001 C CNN
F 3 "~" H 6200 1700 50  0001 C CNN
	1    6200 1700
	1    0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 5C0DA119
P 6200 950
F 0 "R11" V 6100 1000 50  0000 L CNN
F 1 "10k" V 6100 800 50  0000 L CNN
F 2 "" V 6130 950 50  0001 C CNN
F 3 "~" H 6200 950 50  0001 C CNN
	1    6200 950 
	0    -1   1    0   
$EndComp
Wire Wire Line
	5700 1200 6400 1200
Wire Wire Line
	6350 950  6400 950 
Wire Wire Line
	6400 950  6400 1200
Connection ~ 6400 1200
Wire Wire Line
	6400 1200 6500 1200
Wire Wire Line
	6050 950  6000 950 
Wire Wire Line
	6000 950  6000 1050
Connection ~ 6000 1050
Wire Wire Line
	6000 1050 6500 1050
Wire Wire Line
	5250 1500 6500 1500
Wire Wire Line
	5250 1850 5250 1900
Wire Wire Line
	5250 1050 5250 1150
Wire Wire Line
	5250 1050 6000 1050
Wire Wire Line
	6200 1550 6200 1350
Connection ~ 6200 1350
Wire Wire Line
	6200 1350 5700 1350
Wire Wire Line
	6200 1900 6200 1850
Wire Wire Line
	5250 1900 6200 1900
Wire Wire Line
	6200 1350 6500 1350
Wire Wire Line
	6500 1650 6400 1650
Wire Wire Line
	6400 1650 6400 1900
Wire Wire Line
	6400 1900 6200 1900
Connection ~ 6200 1900
Wire Wire Line
	3700 1350 3700 1650
Connection ~ 3700 1650
Wire Wire Line
	3700 1650 3250 1650
Wire Wire Line
	6700 4100 7300 4100
Wire Wire Line
	3700 1050 3700 850 
$EndSCHEMATC
