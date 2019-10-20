EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:ESP32-footprints-Shem-Lib
LIBS:SparkFun_SchematicComponents
LIBS:Symbols_DCDC-ACDC-Converter_RevC_20Jul2012
LIBS:ac-dc
LIBS:Altera
LIBS:analog_devices
LIBS:Battery_Management
LIBS:bbd
LIBS:Bosch
LIBS:brooktre
LIBS:Connector
LIBS:dc-dc
LIBS:Decawave
LIBS:Diode
LIBS:Display
LIBS:driver_gate
LIBS:DSP_Microchip_DSPIC33
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:Espressif
LIBS:FPGA_Actel
LIBS:ftdi
LIBS:gennum
LIBS:Graphic
LIBS:hc11
LIBS:infineon
LIBS:intersil
LIBS:ir
LIBS:Lattice
LIBS:LED
LIBS:LEM
LIBS:Logic_74xgxx
LIBS:Logic_74xx
LIBS:Logic_CMOS_4000
LIBS:Logic_CMOS_IEEE
LIBS:logic_programmable
LIBS:Logic_TTL_IEEE
LIBS:maxim
LIBS:MCU_Microchip_PIC10
LIBS:MCU_Microchip_PIC12
LIBS:MCU_Microchip_PIC16
LIBS:MCU_Microchip_PIC18
LIBS:MCU_Microchip_PIC24
LIBS:MCU_Microchip_PIC32
LIBS:MCU_NXP_Kinetis
LIBS:MCU_NXP_LPC
LIBS:MCU_NXP_S08
LIBS:MCU_Parallax
LIBS:MCU_ST_STM8
LIBS:MCU_ST_STM32
LIBS:MCU_Texas_MSP430
LIBS:Mechanical
LIBS:modules
LIBS:Motor
LIBS:motor_drivers
LIBS:nordicsemi
LIBS:nxp
LIBS:onsemi
LIBS:Oscillators
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:Relay
LIBS:RF_Bluetooth
LIBS:rfcom
LIBS:RFSolutions
LIBS:Sensor_Current
LIBS:Sensor_Humidity
LIBS:sensors
LIBS:silabs
LIBS:supertex
LIBS:Switch
LIBS:Transformer
LIBS:Transistor
LIBS:triac_thyristor
LIBS:Valve
LIBS:video
LIBS:wiznet
LIBS:Worldsemi
LIBS:Xicor
LIBS:zetex
LIBS:Zilog
LIBS:doorbell-cache
EELAYER 25 0
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
L D_Bridge_+-AA D1
U 1 1 5A4BA67B
P 1450 1900
F 0 "D1" H 1500 2175 50  0000 L CNN
F 1 "Bridge Rectifier 1N4001" H 1500 2100 50  0000 L CNN
F 2 "" H 1450 1900 50  0001 C CNN
F 3 "" H 1450 1900 50  0001 C CNN
	1    1450 1900
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 5A4BA79F
P 2000 2250
F 0 "C1" H 2025 2350 50  0000 L CNN
F 1 "470uF" H 2025 2150 50  0000 L CNN
F 2 "" H 2000 2250 50  0001 C CNN
F 3 "" H 2000 2250 50  0001 C CNN
	1    2000 2250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR01
U 1 1 5A4BA8E5
P 5600 1550
F 0 "#PWR01" H 5600 1400 50  0001 C CNN
F 1 "+5V" H 5600 1690 50  0000 C CNN
F 2 "" H 5600 1550 50  0001 C CNN
F 3 "" H 5600 1550 50  0001 C CNN
	1    5600 1550
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A4BAA60
P 2500 2250
F 0 "R1" V 2580 2250 50  0000 C CNN
F 1 "1k" V 2500 2250 50  0000 C CNN
F 2 "" V 2430 2250 50  0001 C CNN
F 3 "" H 2500 2250 50  0001 C CNN
	1    2500 2250
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 5A4BAA9B
P 2500 2650
F 0 "D2" H 2500 2750 50  0000 C CNN
F 1 "LED" H 2500 2550 50  0000 C CNN
F 2 "" H 2500 2650 50  0001 C CNN
F 3 "" H 2500 2650 50  0001 C CNN
	1    2500 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2500 2400 2500 2500
Wire Wire Line
	2000 1900 2000 2100
Connection ~ 2000 1900
Wire Wire Line
	2500 1900 2500 2100
Connection ~ 2500 1900
Wire Wire Line
	2500 2950 2500 2800
Wire Wire Line
	2000 2950 2000 2400
Wire Wire Line
	800  1900 800  2950
Connection ~ 2000 2950
Wire Wire Line
	800  1900 1150 1900
$Comp
L LTV-814 U1
U 1 1 5A4BB1CC
P 5100 2100
F 0 "U1" H 4900 2300 50  0000 L CNN
F 1 "LTV-814" H 5100 2300 50  0000 L CNN
F 2 "Housings_DIP:DIP-4_W7.62mm" H 4900 1900 50  0001 L CIN
F 3 "" H 5125 2100 50  0001 L CNN
	1    5100 2100
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A4BB221
P 4600 2200
F 0 "R2" V 4680 2200 50  0000 C CNN
F 1 "330R" V 4600 2200 50  0000 C CNN
F 2 "" V 4530 2200 50  0001 C CNN
F 3 "" H 4600 2200 50  0001 C CNN
	1    4600 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 2200 4800 2200
$Comp
L CP1_Small C2
U 1 1 5A4BB303
P 5600 2100
F 0 "C2" H 5610 2170 50  0000 L CNN
F 1 "10uF" H 5610 2020 50  0000 L CNN
F 2 "" H 5600 2100 50  0001 C CNN
F 3 "" H 5600 2100 50  0001 C CNN
	1    5600 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2000 5950 2000
Wire Wire Line
	5400 2200 5600 2200
$Comp
L R R3
U 1 1 5A4BB39E
P 5600 1700
F 0 "R3" V 5680 1700 50  0000 C CNN
F 1 "10k" V 5600 1700 50  0000 C CNN
F 2 "" V 5530 1700 50  0001 C CNN
F 3 "" H 5600 1700 50  0001 C CNN
	1    5600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2000 5600 1850
Wire Wire Line
	5600 2200 5600 2950
Connection ~ 2500 2950
$Comp
L GND #PWR02
U 1 1 5A4BB463
P 5600 2950
F 0 "#PWR02" H 5600 2700 50  0001 C CNN
F 1 "GND" H 5600 2800 50  0000 C CNN
F 2 "" H 5600 2950 50  0001 C CNN
F 3 "" H 5600 2950 50  0001 C CNN
	1    5600 2950
	1    0    0    -1  
$EndComp
Text GLabel 1450 1450 1    60   Input ~ 0
AC
Text GLabel 1450 2400 3    60   Input ~ 0
AC
Text GLabel 4350 2000 0    60   Input Italic 0
BELL
Text GLabel 4350 2200 0    60   Input Italic 0
BELL
Wire Wire Line
	4800 2000 4350 2000
Wire Wire Line
	4450 2200 4350 2200
Text GLabel 5950 2000 2    60   Output ~ 0
pin
Connection ~ 5600 2000
Text Notes 1150 1200 0    60   ~ 0
14.7V AC from beltrado
Text Notes 2700 1650 0    60   ~ 0
17.3V DC in
Connection ~ 5600 2200
Connection ~ 5600 2950
$Comp
L TSR_1-2450 U2
U 1 1 5A4BFCEF
P 3150 2000
F 0 "U2" H 2850 2250 50  0000 L CNN
F 1 "5V buck converter" H 3100 2250 50  0000 L CNN
F 2 "Converters_DCDC_ACDC:DCDC-Conv_TRACO_TSR-1" H 3150 1850 50  0001 L CIN
F 3 "" H 3150 2000 50  0001 C CNN
	1    3150 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2200 3150 2950
Connection ~ 3150 2950
$Comp
L +5V #PWR03
U 1 1 5A4C14A9
P 3650 1900
F 0 "#PWR03" H 3650 1750 50  0001 C CNN
F 1 "+5V" H 3650 2040 50  0000 C CNN
F 2 "" H 3650 1900 50  0001 C CNN
F 3 "" H 3650 1900 50  0001 C CNN
	1    3650 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 1900 3550 1900
Wire Wire Line
	1750 1900 2850 1900
Connection ~ 800  2950
Wire Wire Line
	5600 2950 800  2950
Wire Wire Line
	1450 1600 1450 1450
Connection ~ 1450 1700
Connection ~ 1250 1900
Wire Wire Line
	1450 2200 1450 2400
Connection ~ 1450 2100
Connection ~ 1650 1900
Text Notes 4050 1900 0    60   ~ 0
14V AC
$EndSCHEMATC
