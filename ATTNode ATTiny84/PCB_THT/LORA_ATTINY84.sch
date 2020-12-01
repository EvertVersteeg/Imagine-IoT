EESchema Schematic File Version 4
LIBS:LORA_ATTINY84-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L power:GND #PWR0101
U 1 1 5D662E21
P 2550 4750
F 0 "#PWR0101" H 2550 4500 50  0001 C CNN
F 1 "GND" H 2555 4577 50  0000 C CNN
F 2 "" H 2550 4750 50  0001 C CNN
F 3 "" H 2550 4750 50  0001 C CNN
	1    2550 4750
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny84A-SSU U1
U 1 1 5D66342E
P 2550 3850
F 0 "U1" H 2020 3896 50  0000 R CNN
F 1 "ATtiny84A-SSU" H 2800 3850 50  0000 R CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket" H 2550 3850 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8183.pdf" H 2550 3850 50  0001 C CNN
	1    2550 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1850 2900 1750
$Comp
L power:GND #PWR0103
U 1 1 5D68B8DB
P 3200 1750
F 0 "#PWR0103" H 3200 1500 50  0001 C CNN
F 1 "GND" H 3205 1577 50  0000 C CNN
F 2 "" H 3200 1750 50  0001 C CNN
F 3 "" H 3200 1750 50  0001 C CNN
	1    3200 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1650 3200 1750
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 5D68DC89
P 4450 3500
F 0 "J1" H 4422 3382 50  0000 R CNN
F 1 "Sensor" V 4422 3473 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 4450 3500 50  0001 C CNN
F 3 "~" H 4450 3500 50  0001 C CNN
	1    4450 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 2900 2550 2950
$Comp
L Device:Antenna AE1
U 1 1 5D699DFD
P 2150 950
F 0 "AE1" H 2230 939 50  0000 L CNN
F 1 "Antenna" H 2230 848 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2150 950 50  0001 C CNN
F 3 "~" H 2150 950 50  0001 C CNN
	1    2150 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 7250 7350 7200
Text GLabel 3150 3650 2    50   Input ~ 0
SCK
Text GLabel 3150 3750 2    50   Input ~ 0
MISO
Text GLabel 3150 3850 2    50   Input ~ 0
MOSI
Text GLabel 3150 4150 2    50   Input ~ 0
DIO0
Text GLabel 3150 4250 2    50   Input ~ 0
NSS
Text GLabel 3150 4450 2    50   Input ~ 0
RST
Text GLabel 2150 2150 3    50   Input ~ 0
SCK
Text GLabel 2350 2150 3    50   Input ~ 0
MOSI
Text GLabel 2250 2150 3    50   Input ~ 0
MISO
Text GLabel 2450 2150 3    50   Input ~ 0
NSS
Text GLabel 2850 1150 1    50   Input ~ 0
DIO0
Wire Wire Line
	3050 1650 3100 1650
Text GLabel 3150 3250 2    50   Input ~ 0
PA0
Text GLabel 3150 3350 2    50   Input ~ 0
PA1
Text GLabel 3150 3450 2    50   Input ~ 0
PA2
Text GLabel 3150 3550 2    50   Input ~ 0
PA3
Text GLabel 3150 3950 2    50   Input ~ 0
PA7
Text GLabel 3150 4350 2    50   Input ~ 0
PB2
Text GLabel 4250 3300 0    50   Input ~ 0
PA0
Text GLabel 4250 3400 0    50   Input ~ 0
PA1
Text GLabel 4250 3500 0    50   Input ~ 0
PA2
Text GLabel 4250 3600 0    50   Input ~ 0
PA3
Text GLabel 4250 3700 0    50   Input ~ 0
PA7
Text GLabel 4250 3800 0    50   Input ~ 0
PB2
$Comp
L power:GND #PWR0102
U 1 1 5D6F5F48
P 3900 1600
F 0 "#PWR0102" H 3900 1350 50  0001 C CNN
F 1 "GND" H 3905 1427 50  0000 C CNN
F 2 "" H 3900 1600 50  0001 C CNN
F 3 "" H 3900 1600 50  0001 C CNN
	1    3900 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5D6F40EE
P 3900 1500
F 0 "BT1" H 4018 1596 50  0000 L CNN
F 1 "Battery_Cell" H 4018 1505 50  0000 L CNN
F 2 "battery_holder:BatteryHolder_Keystone_1060_1x2032_Long_Pad" V 3900 1560 50  0001 C CNN
F 3 "~" V 3900 1560 50  0001 C CNN
	1    3900 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 5D6F66AA
P 3900 1300
F 0 "#PWR0105" H 3900 1150 50  0001 C CNN
F 1 "+3V3" H 3915 1473 50  0000 C CNN
F 2 "" H 3900 1300 50  0001 C CNN
F 3 "" H 3900 1300 50  0001 C CNN
	1    3900 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 5D6F6B97
P 1750 1500
F 0 "#PWR0106" H 1750 1350 50  0001 C CNN
F 1 "+3V3" H 1765 1673 50  0000 C CNN
F 2 "" H 1750 1500 50  0001 C CNN
F 3 "" H 1750 1500 50  0001 C CNN
	1    1750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1500 1750 1650
$Comp
L power:+3V3 #PWR0107
U 1 1 5D6F753F
P 2550 2900
F 0 "#PWR0107" H 2550 2750 50  0001 C CNN
F 1 "+3V3" H 2565 3073 50  0000 C CNN
F 2 "" H 2550 2900 50  0001 C CNN
F 3 "" H 2550 2900 50  0001 C CNN
	1    2550 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 5D6FB5F9
P 3900 3050
F 0 "#PWR0109" H 3900 2900 50  0001 C CNN
F 1 "+3V3" H 3915 3223 50  0000 C CNN
F 2 "" H 3900 3050 50  0001 C CNN
F 3 "" H 3900 3050 50  0001 C CNN
	1    3900 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5D6FC140
P 3900 3300
F 0 "#PWR0110" H 3900 3050 50  0001 C CNN
F 1 "GND" H 3905 3127 50  0000 C CNN
F 2 "" H 3900 3300 50  0001 C CNN
F 3 "" H 3900 3300 50  0001 C CNN
	1    3900 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3050 3900 3100
Wire Wire Line
	3900 3100 4250 3100
Wire Wire Line
	3900 3300 3900 3200
Wire Wire Line
	3900 3200 4250 3200
Wire Wire Line
	3100 1650 3100 1550
Connection ~ 3100 1650
Wire Wire Line
	3100 1650 3200 1650
NoConn ~ 2750 1150
NoConn ~ 2650 1150
NoConn ~ 2550 1150
NoConn ~ 2450 1150
NoConn ~ 2350 1150
NoConn ~ 2650 2150
Wire Wire Line
	2900 1750 3050 1750
$Comp
L RF_Module:RFM95W-868S2 U2
U 1 1 5D664943
P 2450 1650
F 0 "U2" V 2350 2100 50  0000 L CNN
F 1 "RFM95W-868S2" V 2250 2100 50  0000 L CNN
F 2 "RFM:RFM95" H -850 3300 50  0001 C CNN
F 3 "https://www.hoperf.com/data/upload/portal/20181127/5bfcbea20e9ef.pdf" H -850 3300 50  0001 C CNN
	1    2450 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 1550 3100 1550
Wire Wire Line
	3050 1750 3100 1750
Wire Wire Line
	3100 1750 3100 1650
Connection ~ 3050 1750
Wire Wire Line
	1750 1650 1950 1650
$EndSCHEMATC
