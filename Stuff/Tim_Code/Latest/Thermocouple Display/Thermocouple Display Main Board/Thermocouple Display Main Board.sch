EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Tim_schematic_lib
LIBS:keypad doorlock-cache
LIBS:Keypad Capacitive V5.03-cache
LIBS:Keypad Capacitive V4.0-cache
LIBS:Thermocouple Display Main Board-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date "24 jan 2018"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 16F726 U2
U 1 1 589DDEE8
P 5050 2900
F 0 "U2" H 5050 2900 60  0000 C CNN
F 1 "16F726" H 5050 2900 60  0000 C CNN
F 2 "~" H 5050 2900 60  0000 C CNN
F 3 "~" H 5050 2900 60  0000 C CNN
	1    5050 2900
	1    0    0    -1  
$EndComp
Text GLabel 10300 800  0    60   Input ~ 0
BRA5
Text GLabel 10000 900  0    60   Input ~ 0
BRA4
Text GLabel 10300 1000 0    60   Input ~ 0
BRA2
Text GLabel 10000 1100 0    60   Input ~ 0
MISO
Text GLabel 10300 1200 0    60   Input ~ 0
SCK
Text GLabel 10000 1300 0    60   Input ~ 0
ARA5
Text GLabel 10300 1400 0    60   Input ~ 0
ARA4
Text GLabel 10000 1500 0    60   Input ~ 0
ARA2
$Comp
L +3.3V #PWR31
U 1 1 589DDFBA
P 9650 1600
F 0 "#PWR31" H 9650 1560 30  0001 C CNN
F 1 "+3.3V" H 9650 1710 30  0000 C CNN
F 2 "" H 9650 1600 60  0000 C CNN
F 3 "" H 9650 1600 60  0000 C CNN
	1    9650 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR36
U 1 1 589DDFC9
P 10350 1700
F 0 "#PWR36" H 10350 1700 30  0001 C CNN
F 1 "GND" H 10350 1630 30  0001 C CNN
F 2 "" H 10350 1700 60  0000 C CNN
F 3 "" H 10350 1700 60  0000 C CNN
	1    10350 1700
	1    0    0    -1  
$EndComp
Text GLabel 10300 1800 0    60   Input ~ 0
SOLAR_POWER
Wire Wire Line
	10400 800  10300 800 
Wire Wire Line
	10400 900  10000 900 
Wire Wire Line
	10400 1000 10300 1000
Wire Wire Line
	10400 1100 10000 1100
Wire Wire Line
	10400 1200 10300 1200
Wire Wire Line
	10400 1300 10000 1300
Wire Wire Line
	10400 1400 10300 1400
Wire Wire Line
	10400 1500 10000 1500
Wire Wire Line
	10400 1700 10350 1700
Wire Wire Line
	10400 1800 10300 1800
Wire Wire Line
	9650 1600 10400 1600
$Comp
L CONN_6 P3
U 1 1 589DE161
P 10750 2800
F 0 "P3" V 10700 2800 60  0000 C CNN
F 1 "CONN_6" V 10800 2800 60  0000 C CNN
F 2 "" H 10750 2800 60  0000 C CNN
F 3 "" H 10750 2800 60  0000 C CNN
	1    10750 2800
	1    0    0    -1  
$EndComp
Text GLabel 10250 2550 0    60   Input ~ 0
MCLR/VPP
$Comp
L +3.3V #PWR30
U 1 1 589DE16E
P 9550 2650
F 0 "#PWR30" H 9550 2610 30  0001 C CNN
F 1 "+3.3V" H 9550 2760 30  0000 C CNN
F 2 "" H 9550 2650 60  0000 C CNN
F 3 "" H 9550 2650 60  0000 C CNN
	1    9550 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR32
U 1 1 589DE174
P 10300 2750
F 0 "#PWR32" H 10300 2750 30  0001 C CNN
F 1 "GND" H 10300 2680 30  0001 C CNN
F 2 "" H 10300 2750 60  0000 C CNN
F 3 "" H 10300 2750 60  0000 C CNN
	1    10300 2750
	1    0    0    -1  
$EndComp
Text GLabel 10200 2850 0    60   Input ~ 0
ICSPDAT
Text GLabel 9750 2950 0    60   Input ~ 0
ICSPSCLK
Wire Wire Line
	10400 2550 10250 2550
Wire Wire Line
	9550 2650 10400 2650
Wire Wire Line
	10400 2750 10300 2750
Wire Wire Line
	10400 2850 10200 2850
Wire Wire Line
	10400 2950 9750 2950
Text GLabel 5900 2100 2    60   Input ~ 0
ICSPSCLK
Text GLabel 6400 2000 2    60   Input ~ 0
ICSPDAT
Text GLabel 4000 2000 0    60   Input ~ 0
MCLR/VPP
$Comp
L R R7
U 1 1 589DE28C
P 4050 1700
F 0 "R7" V 4130 1700 40  0000 C CNN
F 1 "R" V 4057 1701 40  0000 C CNN
F 2 "~" V 3980 1700 30  0000 C CNN
F 3 "~" H 4050 1700 30  0000 C CNN
	1    4050 1700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR17
U 1 1 589DE299
P 4050 1350
F 0 "#PWR17" H 4050 1310 30  0001 C CNN
F 1 "+3.3V" H 4050 1460 30  0000 C CNN
F 2 "" H 4050 1350 60  0000 C CNN
F 3 "" H 4050 1350 60  0000 C CNN
	1    4050 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2000 4150 2000
Wire Wire Line
	4050 1950 4050 2000
Connection ~ 4050 2000
Wire Wire Line
	4050 1350 4050 1450
Wire Wire Line
	5800 2100 5900 2100
Wire Wire Line
	6400 2000 5800 2000
Text GLabel 3700 3300 0    60   Input ~ 0
SCK
Text GLabel 5950 3300 2    60   Input ~ 0
MISO
Text GLabel 6250 3200 2    60   Input ~ 0
MOSI
Wire Wire Line
	4150 3300 3700 3300
Wire Wire Line
	5800 3300 5950 3300
Wire Wire Line
	6250 3200 5800 3200
$Sheet
S 650  7400 500  300 
U 58A2259D
F0 "DISPLAY" 50
F1 "file58A2259C.sch" 50
$EndSheet
Text GLabel 5950 3100 2    60   Input ~ 0
DSS
Wire Wire Line
	5800 3100 5950 3100
Text GLabel 3450 2100 0    60   Input ~ 0
DINTERRUPT
Wire Wire Line
	4150 2100 3450 2100
Text GLabel 4000 2200 0    60   Input ~ 0
ARA2
Text GLabel 3700 2300 0    60   Input ~ 0
ARA4
Text GLabel 4000 2400 0    60   Input ~ 0
ARA5
Text GLabel 3700 2500 0    60   Input ~ 0
BRA2
Text GLabel 4000 2600 0    60   Input ~ 0
BRA4
Text GLabel 4000 2800 0    60   Input ~ 0
BRA5
Wire Wire Line
	4150 2200 4000 2200
Wire Wire Line
	4150 2300 3700 2300
Wire Wire Line
	4150 2400 4000 2400
Wire Wire Line
	4150 2500 3700 2500
Wire Wire Line
	4150 2600 4000 2600
$Comp
L INDUCTOR L1
U 1 1 58A4A7EF
P 9900 4700
F 0 "L1" V 9850 4700 40  0000 C CNN
F 1 "INDUCTOR" V 10000 4700 40  0000 C CNN
F 2 "~" H 9900 4700 60  0000 C CNN
F 3 "~" H 9900 4700 60  0000 C CNN
	1    9900 4700
	0    -1   -1   0   
$EndComp
$Comp
L C C9
U 1 1 58A4A7FE
P 10300 4950
F 0 "C9" H 10300 5050 40  0000 L CNN
F 1 "C" H 10306 4865 40  0000 L CNN
F 2 "~" H 10338 4800 30  0000 C CNN
F 3 "~" H 10300 4950 60  0000 C CNN
	1    10300 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR34
U 1 1 58A4A863
P 10300 5200
F 0 "#PWR34" H 10300 5200 30  0001 C CNN
F 1 "GND" H 10300 5130 30  0001 C CNN
F 2 "" H 10300 5200 60  0000 C CNN
F 3 "" H 10300 5200 60  0000 C CNN
	1    10300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4700 9600 4700
Wire Wire Line
	10200 4700 10600 4700
Wire Wire Line
	10300 4700 10300 4750
Wire Wire Line
	10300 5150 10300 5200
Wire Wire Line
	9500 5400 10450 5400
Wire Wire Line
	10450 5400 10450 4700
Connection ~ 10300 4700
$Comp
L +3.3V #PWR37
U 1 1 58A4A900
P 10600 4700
F 0 "#PWR37" H 10600 4660 30  0001 C CNN
F 1 "+3.3V" H 10600 4810 30  0000 C CNN
F 2 "" H 10600 4700 60  0000 C CNN
F 3 "" H 10600 4700 60  0000 C CNN
	1    10600 4700
	1    0    0    -1  
$EndComp
Connection ~ 10450 4700
$Comp
L GND #PWR27
U 1 1 58A4A930
P 7850 5100
F 0 "#PWR27" H 7850 5100 30  0001 C CNN
F 1 "GND" H 7850 5030 30  0001 C CNN
F 2 "" H 7850 5100 60  0000 C CNN
F 3 "" H 7850 5100 60  0000 C CNN
	1    7850 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 5050 7850 5050
Wire Wire Line
	7850 5050 7850 5100
$Comp
L INDUCTOR L2
U 1 1 58A4A96D
P 9900 6050
F 0 "L2" V 9850 6050 40  0000 C CNN
F 1 "INDUCTOR" V 10000 6050 40  0000 C CNN
F 2 "~" H 9900 6050 60  0000 C CNN
F 3 "~" H 9900 6050 60  0000 C CNN
	1    9900 6050
	0    -1   -1   0   
$EndComp
$Comp
L C C10
U 1 1 58A4A973
P 10300 6300
F 0 "C10" H 10300 6400 40  0000 L CNN
F 1 "C" H 10306 6215 40  0000 L CNN
F 2 "~" H 10338 6150 30  0000 C CNN
F 3 "~" H 10300 6300 60  0000 C CNN
	1    10300 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR35
U 1 1 58A4A979
P 10300 6550
F 0 "#PWR35" H 10300 6550 30  0001 C CNN
F 1 "GND" H 10300 6480 30  0001 C CNN
F 2 "" H 10300 6550 60  0000 C CNN
F 3 "" H 10300 6550 60  0000 C CNN
	1    10300 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 6050 9600 6050
Wire Wire Line
	10200 6050 10600 6050
Wire Wire Line
	10300 6050 10300 6100
Wire Wire Line
	10300 6500 10300 6550
Wire Wire Line
	9500 6750 10450 6750
Wire Wire Line
	10450 6750 10450 6050
Connection ~ 10300 6050
Connection ~ 10450 6050
$Comp
L GND #PWR28
U 1 1 58A4A98D
P 7850 6450
F 0 "#PWR28" H 7850 6450 30  0001 C CNN
F 1 "GND" H 7850 6380 30  0001 C CNN
F 2 "" H 7850 6450 60  0000 C CNN
F 3 "" H 7850 6450 60  0000 C CNN
	1    7850 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 6400 7850 6400
Wire Wire Line
	7850 6400 7850 6450
Text GLabel 10600 5750 0    60   Input ~ 0
MAINPICPOWER
Wire Wire Line
	10600 6050 10600 5750
Text GLabel 6050 2800 2    60   Input ~ 0
MAINPICPOWER
Wire Wire Line
	4000 2800 4150 2800
$Comp
L GND #PWR18
U 1 1 58A4AA70
P 4050 2700
F 0 "#PWR18" H 4050 2700 30  0001 C CNN
F 1 "GND" H 4050 2630 30  0001 C CNN
F 2 "" H 4050 2700 60  0000 C CNN
F 3 "" H 4050 2700 60  0000 C CNN
	1    4050 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2700 4050 2700
Wire Wire Line
	6050 2800 5800 2800
Text GLabel 3650 2900 0    60   Input ~ 0
RA6
Wire Wire Line
	3650 2900 4150 2900
Text GLabel 7650 5400 0    60   Input ~ 0
RA6
Wire Wire Line
	7900 5400 7650 5400
Wire Wire Line
	7900 6750 7700 6750
Wire Wire Line
	7700 6750 7700 6050
Wire Wire Line
	7600 6050 7900 6050
Text GLabel 7750 4700 0    60   Input ~ 0
SOLAR_POWER
Text GLabel 7600 6050 0    60   Input ~ 0
SOLAR_POWER
Connection ~ 7700 6050
Wire Wire Line
	7750 4700 7900 4700
$Comp
L CONN_2 P4
U 1 1 58A4AC17
P 10750 3550
F 0 "P4" V 10700 3550 40  0000 C CNN
F 1 "CONN_2" V 10800 3550 40  0000 C CNN
F 2 "" H 10750 3550 60  0000 C CNN
F 3 "" H 10750 3550 60  0000 C CNN
	1    10750 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR33
U 1 1 58A4AC26
P 10300 3650
F 0 "#PWR33" H 10300 3650 30  0001 C CNN
F 1 "GND" H 10300 3580 30  0001 C CNN
F 2 "" H 10300 3650 60  0000 C CNN
F 3 "" H 10300 3650 60  0000 C CNN
	1    10300 3650
	1    0    0    -1  
$EndComp
Text GLabel 10250 3450 0    60   Input ~ 0
SOLAR_POWER
Wire Wire Line
	10400 3450 10250 3450
Wire Wire Line
	10400 3650 10300 3650
$Comp
L NHD-C12832A1Z-FSB-FBW-3V3 U1
U 1 1 58A4B40E
P 3750 5250
F 0 "U1" H 3750 5250 60  0000 C CNN
F 1 "NHD-C12832A1Z-FSB-FBW-3V3" H 3750 5250 60  0000 C CNN
F 2 "" H 3750 5250 60  0000 C CNN
F 3 "" H 3750 5250 60  0000 C CNN
	1    3750 5250
	1    0    0    -1  
$EndComp
Text GLabel 3350 6150 3    60   Input ~ 0
MOSI
Text GLabel 3200 6150 3    60   Input ~ 0
SCK
$Comp
L +3.3V #PWR14
U 1 1 58A4D294
P 3550 6300
F 0 "#PWR14" H 3550 6260 30  0001 C CNN
F 1 "+3.3V" H 3550 6410 30  0000 C CNN
F 2 "" H 3550 6300 60  0000 C CNN
F 3 "" H 3550 6300 60  0000 C CNN
	1    3550 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 58A4D2A8
P 3650 6050
F 0 "#PWR15" H 3650 6050 30  0001 C CNN
F 1 "GND" H 3650 5980 30  0001 C CNN
F 2 "" H 3650 6050 60  0000 C CNN
F 3 "" H 3650 6050 60  0000 C CNN
	1    3650 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6000 3500 6400
Wire Wire Line
	3500 6400 3550 6400
Wire Wire Line
	3550 6400 3550 6300
Wire Wire Line
	3650 6000 3650 6050
$Comp
L C C1
U 1 1 58A4D402
P 3800 6300
F 0 "C1" H 3800 6400 40  0000 L CNN
F 1 "C" H 3806 6215 40  0000 L CNN
F 2 "~" H 3838 6150 30  0000 C CNN
F 3 "~" H 3800 6300 60  0000 C CNN
	1    3800 6300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58A4D40F
P 4000 6300
F 0 "C2" H 4000 6400 40  0000 L CNN
F 1 "C" H 4006 6215 40  0000 L CNN
F 2 "~" H 4038 6150 30  0000 C CNN
F 3 "~" H 4000 6300 60  0000 C CNN
	1    4000 6300
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 58A4D415
P 4350 6300
F 0 "C3" H 4350 6400 40  0000 L CNN
F 1 "C" H 4356 6215 40  0000 L CNN
F 2 "~" H 4388 6150 30  0000 C CNN
F 3 "~" H 4350 6300 60  0000 C CNN
	1    4350 6300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 58A4D41B
P 5100 5800
F 0 "C4" H 5100 5900 40  0000 L CNN
F 1 "C" H 5106 5715 40  0000 L CNN
F 2 "~" H 5138 5650 30  0000 C CNN
F 3 "~" H 5100 5800 60  0000 C CNN
	1    5100 5800
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 58A4D421
P 5350 5600
F 0 "C5" H 5350 5700 40  0000 L CNN
F 1 "C" H 5356 5515 40  0000 L CNN
F 2 "~" H 5388 5450 30  0000 C CNN
F 3 "~" H 5350 5600 60  0000 C CNN
	1    5350 5600
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 58A4D427
P 5600 5500
F 0 "C6" H 5600 5600 40  0000 L CNN
F 1 "C" H 5606 5415 40  0000 L CNN
F 2 "~" H 5638 5350 30  0000 C CNN
F 3 "~" H 5600 5500 60  0000 C CNN
	1    5600 5500
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 58A4D42D
P 5850 5400
F 0 "C7" H 5850 5500 40  0000 L CNN
F 1 "C" H 5856 5315 40  0000 L CNN
F 2 "~" H 5888 5250 30  0000 C CNN
F 3 "~" H 5850 5400 60  0000 C CNN
	1    5850 5400
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 58A4D433
P 6050 5300
F 0 "C8" H 6050 5400 40  0000 L CNN
F 1 "C" H 6056 5215 40  0000 L CNN
F 2 "~" H 6088 5150 30  0000 C CNN
F 3 "~" H 6050 5300 60  0000 C CNN
	1    6050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 5200 5850 5200
Wire Wire Line
	5100 5100 6050 5100
Wire Wire Line
	5100 5300 5600 5300
Wire Wire Line
	5100 5400 5350 5400
Wire Wire Line
	5100 5500 5100 5600
$Comp
L GND #PWR19
U 1 1 58A5B02B
P 5100 6050
F 0 "#PWR19" H 5100 6050 30  0001 C CNN
F 1 "GND" H 5100 5980 30  0001 C CNN
F 2 "" H 5100 6050 60  0000 C CNN
F 3 "" H 5100 6050 60  0000 C CNN
	1    5100 6050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR20
U 1 1 58A5B038
P 5350 5900
F 0 "#PWR20" H 5350 5900 30  0001 C CNN
F 1 "GND" H 5350 5830 30  0001 C CNN
F 2 "" H 5350 5900 60  0000 C CNN
F 3 "" H 5350 5900 60  0000 C CNN
	1    5350 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 58A5B03E
P 5600 5750
F 0 "#PWR21" H 5600 5750 30  0001 C CNN
F 1 "GND" H 5600 5680 30  0001 C CNN
F 2 "" H 5600 5750 60  0000 C CNN
F 3 "" H 5600 5750 60  0000 C CNN
	1    5600 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR22
U 1 1 58A5B044
P 5850 5650
F 0 "#PWR22" H 5850 5650 30  0001 C CNN
F 1 "GND" H 5850 5580 30  0001 C CNN
F 2 "" H 5850 5650 60  0000 C CNN
F 3 "" H 5850 5650 60  0000 C CNN
	1    5850 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR24
U 1 1 58A5B04A
P 6050 5550
F 0 "#PWR24" H 6050 5550 30  0001 C CNN
F 1 "GND" H 6050 5480 30  0001 C CNN
F 2 "" H 6050 5550 60  0000 C CNN
F 3 "" H 6050 5550 60  0000 C CNN
	1    6050 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5500 6050 5550
Wire Wire Line
	5850 5600 5850 5650
Wire Wire Line
	5600 5700 5600 5750
Wire Wire Line
	5350 5800 5350 5900
Wire Wire Line
	5100 6000 5100 6050
$Comp
L GND #PWR16
U 1 1 58A5B1CC
P 3800 6550
F 0 "#PWR16" H 3800 6550 30  0001 C CNN
F 1 "GND" H 3800 6480 30  0001 C CNN
F 2 "" H 3800 6550 60  0000 C CNN
F 3 "" H 3800 6550 60  0000 C CNN
	1    3800 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6000 3800 6100
Wire Wire Line
	3800 6500 3800 6550
Wire Wire Line
	4000 6000 4000 6100
Wire Wire Line
	4000 6500 4000 6600
Wire Wire Line
	4000 6600 4150 6600
Wire Wire Line
	4150 6600 4150 6000
Wire Wire Line
	4350 6000 4350 6100
Wire Wire Line
	4350 6500 4350 6600
Wire Wire Line
	4350 6600 4500 6600
Wire Wire Line
	4500 6600 4500 6000
Wire Wire Line
	3350 6150 3350 6000
Wire Wire Line
	3200 6150 3200 6000
$Comp
L NPN Q1
U 1 1 58A5B478
P 1900 4950
F 0 "Q1" H 1900 4800 50  0000 R CNN
F 1 "NPN" H 1900 5100 50  0000 R CNN
F 2 "~" H 1900 4950 60  0000 C CNN
F 3 "~" H 1900 4950 60  0000 C CNN
	1    1900 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5150 2200 5150
$Comp
L +3.3V #PWR12
U 1 1 58A5B4E2
P 2000 4600
F 0 "#PWR12" H 2000 4560 30  0001 C CNN
F 1 "+3.3V" H 2000 4710 30  0000 C CNN
F 2 "" H 2000 4600 60  0000 C CNN
F 3 "" H 2000 4600 60  0000 C CNN
	1    2000 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4600 2000 4750
$Comp
L R R6
U 1 1 58A5B54D
P 2050 5600
F 0 "R6" V 2130 5600 40  0000 C CNN
F 1 "R" V 2057 5601 40  0000 C CNN
F 2 "~" V 1980 5600 30  0000 C CNN
F 3 "~" H 2050 5600 30  0000 C CNN
	1    2050 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 58A5B55C
P 2050 5900
F 0 "#PWR13" H 2050 5900 30  0001 C CNN
F 1 "GND" H 2050 5830 30  0001 C CNN
F 2 "" H 2050 5900 60  0000 C CNN
F 3 "" H 2050 5900 60  0000 C CNN
	1    2050 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5350 2050 5350
Wire Wire Line
	2050 5850 2050 5900
Text GLabel 6800 2700 2    60   Input ~ 0
MAIN_INTERRUPT
Wire Wire Line
	5800 2700 6800 2700
Text GLabel 1900 700  2    60   Input ~ 0
MAIN_INTERRUPT
$Comp
L CONN_2 P1
U 1 1 58A5C5FA
P 650 800
F 0 "P1" V 600 800 40  0000 C CNN
F 1 "CONN_2" V 700 800 40  0000 C CNN
F 2 "" H 650 800 60  0000 C CNN
F 3 "" H 650 800 60  0000 C CNN
	1    650  800 
	-1   0    0    1   
$EndComp
$Comp
L SW_PUSH_SMALL SW1
U 1 1 58A5C784
P 1550 800
F 0 "SW1" H 1700 910 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 1550 721 30  0000 C CNN
F 2 "~" H 1550 800 60  0000 C CNN
F 3 "~" H 1550 800 60  0000 C CNN
	1    1550 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 700  1900 700 
Connection ~ 1450 700 
$Comp
L GND #PWR1
U 1 1 58A5C855
P 1000 950
F 0 "#PWR1" H 1000 950 30  0001 C CNN
F 1 "GND" H 1000 880 30  0001 C CNN
F 2 "" H 1000 950 60  0000 C CNN
F 3 "" H 1000 950 60  0000 C CNN
	1    1000 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 58A5C864
P 1650 950
F 0 "#PWR7" H 1650 950 30  0001 C CNN
F 1 "GND" H 1650 880 30  0001 C CNN
F 2 "" H 1650 950 60  0000 C CNN
F 3 "" H 1650 950 60  0000 C CNN
	1    1650 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 900  1650 950 
Wire Wire Line
	1000 900  1000 950 
Text GLabel 4000 3000 0    60   Input ~ 0
RC0
Text GLabel 3050 6150 3    60   Input ~ 0
RC0
Text GLabel 3700 3100 0    60   Input ~ 0
RC1
Text GLabel 2900 6150 3    60   Input ~ 0
RC1
Text GLabel 4000 3200 0    60   Input ~ 0
RC2
Text GLabel 2750 6150 3    60   Input ~ 0
RC2
Wire Wire Line
	3050 6000 3050 6150
Wire Wire Line
	2900 6000 2900 6150
Wire Wire Line
	2750 6000 2750 6150
Wire Wire Line
	4000 3000 4150 3000
Wire Wire Line
	3700 3100 4150 3100
Wire Wire Line
	4000 3200 4150 3200
Text GLabel 6250 3000 2    60   Input ~ 0
RC7
Text GLabel 1500 4950 0    60   Input ~ 0
RC7
Wire Wire Line
	1500 4950 1700 4950
Wire Wire Line
	5800 3000 6250 3000
$Comp
L GND #PWR23
U 1 1 58A5CDA7
P 5900 2900
F 0 "#PWR23" H 5900 2900 30  0001 C CNN
F 1 "GND" H 5900 2830 30  0001 C CNN
F 2 "" H 5900 2900 60  0000 C CNN
F 3 "" H 5900 2900 60  0000 C CNN
	1    5900 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2900 5900 2900
$Comp
L R R1
U 1 1 58A5CE7C
P 1300 1000
F 0 "R1" V 1380 1000 40  0000 C CNN
F 1 "R" V 1307 1001 40  0000 C CNN
F 2 "~" V 1230 1000 30  0000 C CNN
F 3 "~" H 1300 1000 30  0000 C CNN
	1    1300 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 58A5CE89
P 1300 1300
F 0 "#PWR2" H 1300 1300 30  0001 C CNN
F 1 "GND" H 1300 1230 30  0001 C CNN
F 2 "" H 1300 1300 60  0000 C CNN
F 3 "" H 1300 1300 60  0000 C CNN
	1    1300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1300 1300 1250
Wire Wire Line
	1300 750  1300 700 
Connection ~ 1300 700 
Text GLabel 1900 1450 2    60   Input ~ 0
RB1
$Comp
L SW_PUSH_SMALL SW2
U 1 1 58A5CF6B
P 1550 1550
F 0 "SW2" H 1700 1660 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 1550 1471 30  0000 C CNN
F 2 "~" H 1550 1550 60  0000 C CNN
F 3 "~" H 1550 1550 60  0000 C CNN
	1    1550 1550
	1    0    0    -1  
$EndComp
Connection ~ 1450 1450
$Comp
L GND #PWR8
U 1 1 58A5CF73
P 1650 1700
F 0 "#PWR8" H 1650 1700 30  0001 C CNN
F 1 "GND" H 1650 1630 30  0001 C CNN
F 2 "" H 1650 1700 60  0000 C CNN
F 3 "" H 1650 1700 60  0000 C CNN
	1    1650 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1650 1650 1700
$Comp
L R R2
U 1 1 58A5CF7A
P 1300 1750
F 0 "R2" V 1380 1750 40  0000 C CNN
F 1 "R" V 1307 1751 40  0000 C CNN
F 2 "~" V 1230 1750 30  0000 C CNN
F 3 "~" H 1300 1750 30  0000 C CNN
	1    1300 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 58A5CF80
P 1300 2050
F 0 "#PWR3" H 1300 2050 30  0001 C CNN
F 1 "GND" H 1300 1980 30  0001 C CNN
F 2 "" H 1300 2050 60  0000 C CNN
F 3 "" H 1300 2050 60  0000 C CNN
	1    1300 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2050 1300 2000
Wire Wire Line
	1300 1500 1300 1450
Connection ~ 1300 1450
Wire Wire Line
	1300 1450 1900 1450
Text GLabel 6050 2600 2    60   Input ~ 0
RB1
Text GLabel 1900 2250 2    60   Input ~ 0
RB2
$Comp
L SW_PUSH_SMALL SW3
U 1 1 58A5D092
P 1550 2350
F 0 "SW3" H 1700 2460 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 1550 2271 30  0000 C CNN
F 2 "~" H 1550 2350 60  0000 C CNN
F 3 "~" H 1550 2350 60  0000 C CNN
	1    1550 2350
	1    0    0    -1  
$EndComp
Connection ~ 1450 2250
$Comp
L GND #PWR9
U 1 1 58A5D099
P 1650 2500
F 0 "#PWR9" H 1650 2500 30  0001 C CNN
F 1 "GND" H 1650 2430 30  0001 C CNN
F 2 "" H 1650 2500 60  0000 C CNN
F 3 "" H 1650 2500 60  0000 C CNN
	1    1650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2450 1650 2500
$Comp
L R R3
U 1 1 58A5D0A0
P 1300 2550
F 0 "R3" V 1380 2550 40  0000 C CNN
F 1 "R" V 1307 2551 40  0000 C CNN
F 2 "~" V 1230 2550 30  0000 C CNN
F 3 "~" H 1300 2550 30  0000 C CNN
	1    1300 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 58A5D0A6
P 1300 2850
F 0 "#PWR4" H 1300 2850 30  0001 C CNN
F 1 "GND" H 1300 2780 30  0001 C CNN
F 2 "" H 1300 2850 60  0000 C CNN
F 3 "" H 1300 2850 60  0000 C CNN
	1    1300 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2850 1300 2800
Wire Wire Line
	1300 2300 1300 2250
Connection ~ 1300 2250
Wire Wire Line
	1300 2250 1900 2250
Text GLabel 1900 3050 2    60   Input ~ 0
RB3
$Comp
L SW_PUSH_SMALL SW4
U 1 1 58A5D0B1
P 1550 3150
F 0 "SW4" H 1700 3260 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 1550 3071 30  0000 C CNN
F 2 "~" H 1550 3150 60  0000 C CNN
F 3 "~" H 1550 3150 60  0000 C CNN
	1    1550 3150
	1    0    0    -1  
$EndComp
Connection ~ 1450 3050
$Comp
L GND #PWR10
U 1 1 58A5D0B8
P 1650 3300
F 0 "#PWR10" H 1650 3300 30  0001 C CNN
F 1 "GND" H 1650 3230 30  0001 C CNN
F 2 "" H 1650 3300 60  0000 C CNN
F 3 "" H 1650 3300 60  0000 C CNN
	1    1650 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3250 1650 3300
$Comp
L R R4
U 1 1 58A5D0BF
P 1300 3350
F 0 "R4" V 1380 3350 40  0000 C CNN
F 1 "R" V 1307 3351 40  0000 C CNN
F 2 "~" V 1230 3350 30  0000 C CNN
F 3 "~" H 1300 3350 30  0000 C CNN
	1    1300 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 58A5D0C5
P 1300 3650
F 0 "#PWR5" H 1300 3650 30  0001 C CNN
F 1 "GND" H 1300 3580 30  0001 C CNN
F 2 "" H 1300 3650 60  0000 C CNN
F 3 "" H 1300 3650 60  0000 C CNN
	1    1300 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3650 1300 3600
Wire Wire Line
	1300 3100 1300 3050
Connection ~ 1300 3050
Wire Wire Line
	1300 3050 1900 3050
Text GLabel 1900 3800 2    60   Input ~ 0
RB4
$Comp
L SW_PUSH_SMALL SW5
U 1 1 58A5D0EB
P 1550 3900
F 0 "SW5" H 1700 4010 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 1550 3821 30  0000 C CNN
F 2 "~" H 1550 3900 60  0000 C CNN
F 3 "~" H 1550 3900 60  0000 C CNN
	1    1550 3900
	1    0    0    -1  
$EndComp
Connection ~ 1450 3800
$Comp
L GND #PWR11
U 1 1 58A5D0F2
P 1650 4050
F 0 "#PWR11" H 1650 4050 30  0001 C CNN
F 1 "GND" H 1650 3980 30  0001 C CNN
F 2 "" H 1650 4050 60  0000 C CNN
F 3 "" H 1650 4050 60  0000 C CNN
	1    1650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 4000 1650 4050
$Comp
L R R5
U 1 1 58A5D0F9
P 1300 4100
F 0 "R5" V 1380 4100 40  0000 C CNN
F 1 "R" V 1307 4101 40  0000 C CNN
F 2 "~" V 1230 4100 30  0000 C CNN
F 3 "~" H 1300 4100 30  0000 C CNN
	1    1300 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 58A5D0FF
P 1300 4400
F 0 "#PWR6" H 1300 4400 30  0001 C CNN
F 1 "GND" H 1300 4330 30  0001 C CNN
F 2 "" H 1300 4400 60  0000 C CNN
F 3 "" H 1300 4400 60  0000 C CNN
	1    1300 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4400 1300 4350
Wire Wire Line
	1300 3850 1300 3800
Connection ~ 1300 3800
Wire Wire Line
	1300 3800 1900 3800
Text GLabel 6350 2500 2    60   Input ~ 0
RB2
Text GLabel 6050 2400 2    60   Input ~ 0
RB3
Text GLabel 6350 2300 2    60   Input ~ 0
RB4
$Comp
L R R8
U 1 1 58A5D198
P 7250 2200
F 0 "R8" V 7330 2200 40  0000 C CNN
F 1 "R" V 7257 2201 40  0000 C CNN
F 2 "~" V 7180 2200 30  0000 C CNN
F 3 "~" H 7250 2200 30  0000 C CNN
	1    7250 2200
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 58A5D1A7
P 7900 2200
F 0 "D1" H 7900 2300 50  0000 C CNN
F 1 "LED" H 7900 2100 50  0000 C CNN
F 2 "~" H 7900 2200 60  0000 C CNN
F 3 "~" H 7900 2200 60  0000 C CNN
	1    7900 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR25
U 1 1 58A5D1B6
P 7300 1150
F 0 "#PWR25" H 7300 1110 30  0001 C CNN
F 1 "+3.3V" H 7300 1260 30  0000 C CNN
F 2 "" H 7300 1150 60  0000 C CNN
F 3 "" H 7300 1150 60  0000 C CNN
	1    7300 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2200 7000 2200
Wire Wire Line
	7500 2200 7700 2200
Wire Wire Line
	8100 2200 8350 2200
Wire Wire Line
	5800 2300 6350 2300
Wire Wire Line
	5800 2400 6050 2400
Wire Wire Line
	5800 2500 6350 2500
Wire Wire Line
	5800 2600 6050 2600
Text Notes 1650 850  0    60   ~ 0
CKN9112CT-ND
$Comp
L SC189_3.3 U3
U 1 1 58B0512C
P 8700 5100
F 0 "U3" H 8650 5250 60  0000 C CNN
F 1 "SC189_3.3" H 8700 5100 60  0000 C CNN
F 2 "~" H 8700 5100 60  0000 C CNN
F 3 "~" H 8700 5100 60  0000 C CNN
	1    8700 5100
	1    0    0    -1  
$EndComp
$Comp
L SC189_3.3 U4
U 1 1 58B05143
P 8700 6450
F 0 "U4" H 8650 6600 60  0000 C CNN
F 1 "SC189_3.3" H 8700 6450 60  0000 C CNN
F 2 "~" H 8700 6450 60  0000 C CNN
F 3 "~" H 8700 6450 60  0000 C CNN
	1    8700 6450
	1    0    0    -1  
$EndComp
$Comp
L CONN_12 P2
U 1 1 58B0AA81
P 10750 1350
F 0 "P2" V 10700 1350 60  0000 C CNN
F 1 "CONN_12" V 10800 1350 60  0000 C CNN
F 2 "" H 10750 1350 60  0000 C CNN
F 3 "" H 10750 1350 60  0000 C CNN
	1    10750 1350
	1    0    0    -1  
$EndComp
Text GLabel 9600 1900 0    60   Input ~ 0
MOSI
Wire Wire Line
	9600 1900 10400 1900
$Comp
L NPN Q7
U 1 1 58B6E547
P 7200 1400
F 0 "Q7" H 7200 1250 50  0000 R CNN
F 1 "NPN" H 7200 1550 50  0000 R CNN
F 2 "~" H 7200 1400 60  0000 C CNN
F 3 "~" H 7200 1400 60  0000 C CNN
	1    7200 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR29
U 1 1 58B6E5CC
P 8350 2200
F 0 "#PWR29" H 8350 2200 30  0001 C CNN
F 1 "GND" H 8350 2130 30  0001 C CNN
F 2 "" H 8350 2200 60  0000 C CNN
F 3 "" H 8350 2200 60  0000 C CNN
	1    8350 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2200 7000 1400
Wire Wire Line
	7300 1150 7300 1200
$Comp
L C6L-1F_DC3 K1
U 1 1 58B71A93
P 8300 1450
F 0 "K1" H 8250 1650 60  0000 C CNN
F 1 "C6L-1F_DC3" H 8300 1450 60  0000 C CNN
F 2 "" H 8300 1450 60  0000 C CNN
F 3 "" H 8300 1450 60  0000 C CNN
	1    8300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1600 7300 1750
Wire Wire Line
	7300 1750 7450 1750
$Comp
L GND #PWR26
U 1 1 58B71B35
P 7450 750
F 0 "#PWR26" H 7450 750 30  0001 C CNN
F 1 "GND" H 7450 680 30  0001 C CNN
F 2 "" H 7450 750 60  0000 C CNN
F 3 "" H 7450 750 60  0000 C CNN
	1    7450 750 
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P17
U 1 1 58B71B44
P 8900 1200
F 0 "P17" V 8850 1200 40  0000 C CNN
F 1 "CONN_2" V 8950 1200 40  0000 C CNN
F 2 "" H 8900 1200 60  0000 C CNN
F 3 "" H 8900 1200 60  0000 C CNN
	1    8900 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	9000 1750 9250 1750
Wire Wire Line
	9250 1750 9250 1300
Wire Wire Line
	9250 1100 9250 750 
Wire Wire Line
	9250 750  9000 750 
Text Notes 3800 1200 0    60   ~ 0
This 3.3V should be MAINPICPOWER
$EndSCHEMATC