EESchema Schematic File Version 4
LIBS:nextion_hmi-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L nextion_hmi-rescue:1N4148- D1
U 1 1 5BF96A09
P 5450 3500
F 0 "D1" H 5450 3300 50  0000 C CNN
F 1 "BAS85" H 5450 3400 50  0000 C CNN
F 2 "Diodes_SMD:D_MiniMELF_Handsoldering" H 5450 3325 50  0001 C CNN
F 3 "" H 5450 3500 50  0001 C CNN
	1    5450 3500
	1    0    0    1   
$EndComp
Text HLabel 3800 3800 0    60   BiDi ~ 0
DATA
Connection ~ 4600 4400
Connection ~ 6200 3500
Wire Wire Line
	6200 3650 6200 3500
Wire Wire Line
	6300 4100 6000 4100
Connection ~ 5700 4400
Wire Wire Line
	6200 4400 6200 3950
Wire Wire Line
	6100 3500 6200 3500
Wire Wire Line
	6350 3200 6700 3200
Connection ~ 4600 3200
Wire Wire Line
	4100 3200 4100 3950
Wire Wire Line
	4100 3200 4600 3200
Wire Wire Line
	4600 3200 4600 3300
Wire Wire Line
	4100 4400 4100 4250
Wire Wire Line
	5100 3800 3800 3800
Wire Wire Line
	4950 3500 4900 3500
Wire Wire Line
	5300 3500 5250 3500
Connection ~ 5700 3800
Wire Wire Line
	5400 3800 5700 3800
Wire Wire Line
	6600 4100 6700 4100
Wire Wire Line
	4600 4400 4600 3700
Connection ~ 5700 3500
Wire Wire Line
	5700 4400 5700 4300
Wire Wire Line
	4100 4400 4600 4400
Wire Wire Line
	5700 3500 5700 3800
Wire Wire Line
	5600 3500 5700 3500
Text Label 5200 4400 2    60   ~ 0
COM
Wire Wire Line
	4600 4400 5700 4400
Wire Wire Line
	6200 3500 6700 3500
Wire Wire Line
	5700 4400 6200 4400
Wire Wire Line
	5700 3800 5700 3900
Wire Wire Line
	5700 3500 5800 3500
$Comp
L Device:R R18
U 1 1 5BF96A3A
P 5250 3800
F 0 "R18" V 5350 3850 50  0000 L CNN
F 1 "100" V 5350 3650 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5180 3800 50  0001 C CNN
F 3 "~" H 5250 3800 50  0001 C CNN
	1    5250 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R16
U 1 1 5BF96A41
P 5100 3500
F 0 "R16" V 5200 3550 50  0000 L CNN
F 1 "1k0" V 5200 3350 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5030 3500 50  0001 C CNN
F 3 "~" H 5100 3500 50  0001 C CNN
	1    5100 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R17
U 1 1 5BF96A48
P 5950 3500
F 0 "R17" V 6050 3550 50  0000 L CNN
F 1 "10k" V 6050 3350 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5880 3500 50  0001 C CNN
F 3 "~" H 5950 3500 50  0001 C CNN
	1    5950 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R15
U 1 1 5BF96A4F
P 6200 3200
F 0 "R15" V 6300 3250 50  0000 L CNN
F 1 "1k0" V 6300 3050 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6130 3200 50  0001 C CNN
F 3 "~" H 6200 3200 50  0001 C CNN
	1    6200 3200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 5BF96A56
P 6200 2900
F 0 "R14" V 6300 2950 50  0000 L CNN
F 1 "10k" V 6300 2750 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6130 2900 50  0001 C CNN
F 3 "~" H 6200 2900 50  0001 C CNN
	1    6200 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R19
U 1 1 5BF96A5D
P 6450 4100
F 0 "R19" V 6550 4150 50  0000 L CNN
F 1 "5k1" V 6550 3950 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6380 4100 50  0001 C CNN
F 3 "~" H 6450 4100 50  0001 C CNN
	1    6450 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C12
U 1 1 5BF96A64
P 4100 4100
F 0 "C12" H 3900 4150 50  0000 C CNN
F 1 "1nF" H 3900 4050 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4138 3950 50  0001 C CNN
F 3 "~" H 4100 4100 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5BF96A6B
P 6200 3800
F 0 "C11" H 6400 3850 50  0000 C CNN
F 1 "100nF" H 6450 3750 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6238 3650 50  0001 C CNN
F 3 "~" H 6200 3800 50  0001 C CNN
	1    6200 3800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 5BF96A72
P 4700 3500
F 0 "Q1" H 4890 3546 50  0000 L CNN
F 1 "BC817" H 4890 3455 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4900 3425 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 4700 3500 50  0001 L CNN
	1    4700 3500
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q3
U 1 1 5BF96A79
P 5800 4100
F 0 "Q3" H 5990 4146 50  0000 L CNN
F 1 "BC817" H 5990 4055 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6000 4025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 5800 4100 50  0001 L CNN
	1    5800 4100
	-1   0    0    -1  
$EndComp
Text HLabel 6700 3200 2    50   Input ~ 0
MCURX
Text HLabel 6700 4100 2    50   Input ~ 0
MCUTX
Text Label 6700 3500 2    50   ~ 0
12VDC
Wire Wire Line
	4600 3200 5950 3200
Wire Wire Line
	6050 2900 5950 2900
Wire Wire Line
	6350 2900 6700 2900
Text HLabel 6700 2900 2    50   Input ~ 0
VDD
Wire Wire Line
	5950 2900 5950 3200
Connection ~ 5950 3200
Wire Wire Line
	5950 3200 6050 3200
Text HLabel 6700 5200 2    50   Input ~ 0
PF0
Text HLabel 6700 5400 2    50   Output ~ 0
PF1
$EndSCHEMATC
