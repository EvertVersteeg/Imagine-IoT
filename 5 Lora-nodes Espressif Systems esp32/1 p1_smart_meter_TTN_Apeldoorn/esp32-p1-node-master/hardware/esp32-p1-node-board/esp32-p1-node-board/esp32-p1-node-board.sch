EESchema Schematic File Version 4
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
L esp32-p1-node-board-rescue:RJ11-6-SparkFun-Connectors J1
U 1 1 5F00D179
P 1200 1550
F 0 "J1" H 1156 2360 45  0000 C CNN
F 1 "RJ11-6" H 1156 2276 45  0000 C CNN
F 2 "Connector_RJ:RJ12_Amphenol_54601" H 1200 2250 20  0001 C CNN
F 3 "" H 1200 1550 50  0001 C CNN
F 4 "P1-Interface" H 1156 2181 60  0000 C CNN "Field4"
	1    1200 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1150 2000 1150
Wire Wire Line
	1300 1350 2000 1350
Wire Wire Line
	1300 1450 2000 1450
Text Label 1600 1150 0    50   ~ 0
DATA
Text Label 1600 1350 0    50   ~ 0
DATA_GND
Text Label 1600 1450 0    50   ~ 0
DATA_REQ
Text Notes 2250 1400 0    50   ~ 0
See: P1 Specification: https://www.netbeheernederland.nl/_upload/Files/Slimme_meter_15_a727fce1f1.pdf\nPWR: 5V, Max current: 250 mA\nDATA: Open collector\nP1 port lines must be galvanically isolated from the mains,Including+5V power supply lines
Wire Wire Line
	1300 1250 2000 1250
Wire Wire Line
	1300 1050 2000 1050
Text Label 1600 1050 0    50   ~ 0
GND
Text Label 1600 1250 0    50   ~ 0
NC
$Comp
L Device:R R3
U 1 1 5F010DE5
P 3050 2400
F 0 "R3" H 3120 2446 50  0000 L CNN
F 1 "12K" H 3120 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2980 2400 50  0001 C CNN
F 3 "~" H 3050 2400 50  0001 C CNN
	1    3050 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F010DEC
P 1700 2900
F 0 "R2" V 1493 2900 50  0000 C CNN
F 1 "1K" V 1584 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1630 2900 50  0001 C CNN
F 3 "~" H 1700 2900 50  0001 C CNN
	1    1700 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F010DF3
P 1450 2400
F 0 "R1" H 1520 2446 50  0000 L CNN
F 1 "10K" H 1520 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1380 2400 50  0001 C CNN
F 3 "~" H 1450 2400 50  0001 C CNN
	1    1450 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2550 3050 2650
Wire Wire Line
	1550 2900 1450 2900
Wire Wire Line
	1450 2550 1450 2900
Wire Wire Line
	3050 2250 3050 2050
Wire Wire Line
	1450 2250 1450 2050
Text Label 3050 2150 0    50   ~ 0
3V3
Text Label 1450 2150 0    50   ~ 0
5V
Wire Wire Line
	3050 2650 3700 2650
Connection ~ 3050 2650
Wire Wire Line
	3050 2650 3050 2700
Text Label 3300 2650 0    50   ~ 0
DATA_3V3_N
Text Label 1050 3450 0    50   ~ 0
DATA_GND
$Comp
L Device:C C1
U 1 1 5F0114B4
P 2000 3150
F 0 "C1" H 2115 3196 50  0000 L CNN
F 1 "10n" H 2115 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2038 3000 50  0001 C CNN
F 3 "~" H 2000 3150 50  0001 C CNN
	1    2000 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2250 2600 2050
Wire Wire Line
	1850 2900 2000 2900
Wire Wire Line
	2000 3000 2000 2900
Connection ~ 2000 2900
Wire Wire Line
	2000 3450 2000 3300
Wire Wire Line
	3050 3100 3050 3450
Wire Wire Line
	2000 3450 1000 3450
Connection ~ 2000 3450
Wire Wire Line
	1450 2900 1000 2900
Connection ~ 1450 2900
Text Label 1050 2900 0    50   ~ 0
DATA
Text Label 2600 2150 0    50   ~ 0
5V
$Comp
L esp32-p1-node-board-rescue:TTGO_LoRa32_V11-esp32_node U1
U 1 1 5F01626F
P 5500 2650
F 0 "U1" H 5475 3465 50  0000 C CNN
F 1 "TTGO_LoRa32_V11" H 5475 3374 50  0000 C CNN
F 2 "esp32-p1-node-board:TTGO_LoRa32_V11" H 5500 2650 50  0001 C CNN
F 3 "" H 5500 2650 50  0001 C CNN
	1    5500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2100 4300 2100
Wire Wire Line
	4900 2400 4300 2400
Wire Wire Line
	6050 2100 6650 2100
Wire Wire Line
	4900 2200 4300 2200
Wire Wire Line
	6050 2200 6650 2200
Wire Wire Line
	6050 2300 6650 2300
Text Label 4400 2100 0    50   ~ 0
GND
Text Label 4400 2400 0    50   ~ 0
GND
Text Label 6350 2100 0    50   ~ 0
GND
Text Label 4400 2200 0    50   ~ 0
5V
Text Label 6350 2200 0    50   ~ 0
5V
Text Label 6350 2300 0    50   ~ 0
3V3
Wire Wire Line
	3050 3450 3700 3450
Connection ~ 3050 3450
Text Label 3300 3450 0    50   ~ 0
GND
Wire Wire Line
	6050 3200 6600 3200
Wire Wire Line
	4900 2700 4300 2700
Wire Wire Line
	4900 2800 4300 2800
Wire Wire Line
	4900 2900 4300 2900
Wire Wire Line
	6050 3800 6600 3800
Text Label 6350 3800 0    50   ~ 0
SDA
Text Label 4400 2700 0    50   ~ 0
RESET
Text Label 4400 2800 0    50   ~ 0
BUTTON
Text Label 4400 2900 0    50   ~ 0
SCL
Text Label 6500 3200 2    50   ~ 0
SOFT_REQ
Text Label 6500 2800 2    50   ~ 0
SOFT_TXD
Wire Wire Line
	6050 2800 6600 2800
Text Notes 4400 3000 0    50   ~ 0
LoRa_MISO
Text Notes 4400 3200 0    50   ~ 0
LoRa_CS
Text Notes 4400 3300 0    50   ~ 0
LoRa_SCK
Text Notes 4400 3400 0    50   ~ 0
OLED_SCL\n
Text Notes 4400 3500 0    50   ~ 0
LED
Text Notes 4400 3600 0    50   ~ 0
OLED_SDA
Text Notes 4400 3800 0    50   ~ 0
OLED_RST
Text Notes 6500 3300 2    50   ~ 0
LoRa_IRQ
Text Notes 6500 3400 2    50   ~ 0
LoRa_MOSI
Text Notes 6500 3500 2    50   ~ 0
LoRa_RST
$Comp
L Diode:BAT54S D1
U 1 1 5F032A48
P 2600 2550
F 0 "D1" V 2646 2637 50  0000 L CNN
F 1 "BAT54S" V 2555 2637 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2675 2675 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds11005.pdf" H 2480 2550 50  0001 C CNN
	1    2600 2550
	0    1    -1   0   
$EndComp
Wire Wire Line
	2000 2900 2350 2900
Wire Wire Line
	2000 3450 2600 3450
Wire Wire Line
	2600 2850 2600 3450
Connection ~ 2600 3450
Wire Wire Line
	2600 3450 3050 3450
Wire Wire Line
	2400 2550 2350 2550
Wire Wire Line
	2350 2550 2350 2900
Connection ~ 2350 2900
Wire Wire Line
	2350 2900 2750 2900
Wire Wire Line
	4900 2300 4300 2300
Text Label 4400 2300 0    50   ~ 0
3V3
Text Notes 4400 2600 0    50   ~ 0
TXD
$Comp
L esp32-p1-node-board-rescue:JUMPER-SMT_3_1-NC-SparkFun-Jumpers JP1
U 1 1 5F1DD89F
P 3550 4450
F 0 "JP1" V 3886 4450 45  0000 C CNN
F 1 "Serial-type-select" V 3802 4450 45  0000 C CNN
F 2 "Jumpers:SMT-JUMPER_3_1-NC_TRACE_SILK" H 3550 4700 20  0001 C CNN
F 3 "" V 3550 4395 60  0001 C CNN
F 4 "Serial selector" V 3707 4450 60  0000 C CNN "PROD_ID"
	1    3550 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 4600 3550 4750
Wire Wire Line
	3550 4750 4250 4750
Wire Wire Line
	3350 4450 2800 4450
Wire Wire Line
	3750 4450 4250 4450
Wire Wire Line
	4900 2500 4300 2500
Text Label 4400 2500 0    50   ~ 0
HARD_RXD
Text Label 4150 4750 2    50   ~ 0
DATA_3V3
Text Label 4150 4450 2    50   ~ 0
SOFT_RXD
Text Label 2900 4450 0    50   ~ 0
HARD_RXD
Wire Wire Line
	6050 2900 6600 2900
Text Label 6150 2900 0    50   ~ 0
SOFT_RXD
$Comp
L esp32-p1-node-board-rescue:JUMPER-SMT_3_1-NC-SparkFun-Jumpers JP2
U 1 1 5F1EB1BA
P 3550 5400
F 0 "JP2" V 3886 5400 45  0000 C CNN
F 1 "Data-request-select" V 3802 5400 45  0000 C CNN
F 2 "Jumpers:SMT-JUMPER_3_1-NC_TRACE_SILK" H 3550 5650 20  0001 C CNN
F 3 "" V 3550 5345 60  0001 C CNN
F 4 "Request selector" V 3707 5400 60  0000 C CNN "PROD_ID"
	1    3550 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 5550 3550 5700
Wire Wire Line
	3550 5700 4250 5700
Wire Wire Line
	3350 5400 2800 5400
Wire Wire Line
	3750 5400 4250 5400
Text Label 4150 5700 2    50   ~ 0
DATA_REQ
Text Label 4150 5400 2    50   ~ 0
3V3
Text Label 2900 5400 0    50   ~ 0
SOFT_REQ
Wire Wire Line
	5700 4450 6600 4450
Text Label 6500 4450 2    50   ~ 0
GND
Text Label 6500 5050 2    50   ~ 0
5V
$Comp
L Device:C C2
U 1 1 5F1EFAFA
P 5900 5250
F 0 "C2" H 6015 5296 50  0000 L CNN
F 1 "10n" H 6015 5205 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5938 5100 50  0001 C CNN
F 3 "~" H 5900 5250 50  0001 C CNN
	1    5900 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5050 5900 5050
Wire Wire Line
	5900 5100 5900 5050
Connection ~ 5900 5050
Wire Wire Line
	5900 5050 6600 5050
$Comp
L esp32-p1-node-board-rescue:THT_USB-B-Mini-esp32_node Conn1
U 1 1 5F1FC4B8
P 5300 5300
F 0 "Conn1" H 5244 5815 50  0000 C CNN
F 1 "THT_USB-B-Mini" H 5244 5724 50  0000 C CNN
F 2 "esp32-p1-node-board:THT_USB-B-Mini" H 5300 5300 50  0001 C CNN
F 3 "" H 5300 5300 50  0001 C CNN
	1    5300 5300
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F1FD530
P 6050 5700
F 0 "C3" H 6165 5746 50  0000 L CNN
F 1 "10n" H 6165 5655 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6088 5550 50  0001 C CNN
F 3 "~" H 6050 5700 50  0001 C CNN
	1    6050 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5550 5750 5550
Wire Wire Line
	5750 5550 5750 5650
Wire Wire Line
	5750 5950 6050 5950
Wire Wire Line
	6050 5950 6050 5850
Wire Wire Line
	5650 5650 5750 5650
Connection ~ 5750 5650
Wire Wire Line
	5750 5650 5750 5950
Wire Wire Line
	5650 5450 5900 5450
Wire Wire Line
	5900 5450 5900 5400
Wire Wire Line
	5900 5450 6050 5450
Wire Wire Line
	6050 5450 6050 5550
Connection ~ 5900 5450
Wire Wire Line
	6050 5450 6600 5450
Connection ~ 6050 5450
Text Label 6500 5450 2    50   ~ 0
GND
$Comp
L esp32-p1-node-board-rescue:SMA-ANT-CONN-esp32_node COAX1
U 1 1 5F1FA2D2
P 5400 4450
F 0 "COAX1" H 5456 4815 50  0000 C CNN
F 1 "SMA-ANT-CONN" H 5456 4724 50  0000 C CNN
F 2 "esp32-p1-node-board:SMA-ANT-CONN" H 5400 4450 50  0001 C CNN
F 3 "" H 5400 4450 50  0001 C CNN
	1    5400 4450
	1    0    0    -1  
$EndComp
$Comp
L esp32-p1-node-board-rescue:JUMPER-SMT_3_1-NC-SparkFun-Jumpers JP3
U 1 1 5F231B69
P 3550 6350
F 0 "JP3" V 3886 6350 45  0000 C CNN
F 1 "Serial-type-select" V 3802 6350 45  0000 C CNN
F 2 "Jumpers:SMT-JUMPER_3_1-NC_TRACE_SILK" H 3550 6600 20  0001 C CNN
F 3 "" V 3550 6295 60  0001 C CNN
F 4 "Polarity selector" V 3707 6350 60  0000 C CNN "PROD_ID"
	1    3550 6350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 6500 3550 6650
Wire Wire Line
	3550 6650 4250 6650
Wire Wire Line
	3750 6350 4250 6350
Text Label 4150 6650 2    50   ~ 0
DATA_3V3
Text Label 4150 6350 2    50   ~ 0
DATA_3V3_N
Wire Wire Line
	2000 2900 2000 1850
Wire Wire Line
	2000 1850 2700 1850
Text Label 2100 1850 0    50   ~ 0
DATA_5V_R
$Comp
L Device:R R4
U 1 1 5F27E427
P 1650 6050
F 0 "R4" H 1720 6096 50  0000 L CNN
F 1 "10K" H 1720 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1580 6050 50  0001 C CNN
F 3 "~" H 1650 6050 50  0001 C CNN
	1    1650 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5F27E534
P 2350 6050
F 0 "R5" H 2420 6096 50  0000 L CNN
F 1 "10K" H 2420 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2280 6050 50  0001 C CNN
F 3 "~" H 2350 6050 50  0001 C CNN
	1    2350 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6350 1650 6350
Wire Wire Line
	2350 5900 2350 5800
Wire Wire Line
	1650 6200 1650 6350
Connection ~ 1650 6350
Wire Wire Line
	1650 6350 1000 6350
Wire Wire Line
	2200 6350 2350 6350
Wire Wire Line
	2350 6200 2350 6350
Connection ~ 2350 6350
Wire Wire Line
	2350 6350 3350 6350
Text Label 1500 6350 2    50   ~ 0
DATA_5V_R
Wire Wire Line
	1650 5400 1650 5900
$Comp
L Transistor_FET:BSS138 Q2
U 1 1 5F291B2F
P 2000 6250
F 0 "Q2" V 2250 6250 50  0000 C CNN
F 1 "BSS138" V 2341 6250 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2200 6175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 2000 6250 50  0001 L CNN
	1    2000 6250
	0    -1   1    0   
$EndComp
Wire Wire Line
	2000 6050 2000 5800
Wire Wire Line
	2000 5800 2350 5800
Connection ~ 2350 5800
Wire Wire Line
	2350 5800 2350 5400
Text Label 2350 5550 2    50   ~ 0
3V3
Text Label 1650 5550 2    50   ~ 0
5V
$Comp
L Transistor_BJT:BC847 Q1
U 1 1 5F2B34AD
P 2950 2900
F 0 "Q1" H 3141 2946 50  0000 L CNN
F 1 "BC847" H 3141 2855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3150 2825 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 2950 2900 50  0001 L CNN
	1    2950 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
