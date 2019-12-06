#ifndef PLATFORM_H
#define PLATFORM_H


typedef enum {
	P00 = (0 << 16) | 0,
	P01 = (0 << 16) | 1,
	P02 = (0 << 16) | 2,
	P03 = (0 << 16) | 3,
	P04 = (0 << 16) | 4,
	P05 = (0 << 16) | 5,
	P06 = (0 << 16) | 6,
	P07 = (0 << 16) | 7,
	P08 = (0 << 16) | 8,
	P09 = (0 << 16) | 9,
	P0A = (0 << 16) | 10,
	P0B = (0 << 16) | 11,
	P0C = (0 << 16) | 12,
	P0D = (0 << 16) | 13,
	P0E = (0 << 16) | 14,
	P0F = (0 << 16) | 15,

	P10 = (1 << 16) | 0,
	P11 = (1 << 16) | 1,
	P12 = (1 << 16) | 2,
	P13 = (1 << 16) | 3,
	P14 = (1 << 16) | 4,
	P15 = (1 << 16) | 5,
	P16 = (1 << 16) | 6,
	P17 = (1 << 16) | 7,
	P18 = (1 << 16) | 8,
	P19 = (1 << 16) | 9,
	P1A = (1 << 16) | 10,
	P1B = (1 << 16) | 11,
	P1C = (1 << 16) | 12,
	P1D = (1 << 16) | 13,
	P1E = (1 << 16) | 14,
	P1F = (1 << 16) | 15,
	
	P20 = (2 << 16) | 0,
	P21 = (2 << 16) | 1,
	P22 = (2 << 16) | 2,
	P23 = (2 << 16) | 3,
	P24 = (2 << 16) | 4,
	P25 = (2 << 16) | 5,
	P26 = (2 << 16) | 6,
	P27 = (2 << 16) | 7,
	P28 = (2 << 16) | 8,
	P29 = (2 << 16) | 9,
	P2A = (2 << 16) | 10,
	P2B = (2 << 16) | 11,
	P2C = (2 << 16) | 12,
	P2D = (2 << 16) | 13,
	P2E = (2 << 16) | 14,
	P2F = (2 << 16) | 15,

	P30 = (3 << 16) | 0,
	P31 = (3 << 16) | 1,
	P32 = (3 << 16) | 2,
	P33 = (3 << 16) | 3,
	P34 = (3 << 16) | 4,
	P35 = (3 << 16) | 5,
	P36 = (3 << 16) | 6,
	P37 = (3 << 16) | 7,
	P38 = (3 << 16) | 8,
	P39 = (3 << 16) | 9,
	P3A = (3 << 16) | 10,
	P3B = (3 << 16) | 11,
	P3C = (3 << 16) | 12,
	P3D = (3 << 16) | 13,
	P3E = (3 << 16) | 14,
	P3F = (3 << 16) | 15,

	P40 = (4 << 16) | 0,
	P41 = (4 << 16) | 1,
	P42 = (4 << 16) | 2,
	P43 = (4 << 16) | 3,
	P44 = (4 << 16) | 4,
	P45 = (4 << 16) | 5,
	P46 = (4 << 16) | 6,
	P47 = (4 << 16) | 7,
	P48 = (4 << 16) | 8,
	P49 = (4 << 16) | 9,
	P4A = (4 << 16) | 10,
	P4B = (4 << 16) | 11,
	P4C = (4 << 16) | 12,
	P4D = (4 << 16) | 13,
	P4E = (4 << 16) | 14,
	P4F = (4 << 16) | 15,	

	P50 = (5 << 16) | 0,
	P51 = (5 << 16) | 1,
	P52 = (5 << 16) | 2,
	P53 = (5 << 16) | 3,
	P54 = (5 << 16) | 4,
	P55 = (5 << 16) | 5,
	P56 = (5 << 16) | 6,
	P57 = (5 << 16) | 7,
	P58 = (5 << 16) | 8,
	P59 = (5 << 16) | 9,
	P5A = (5 << 16) | 10,
	P5B = (5 << 16) | 11,
	P5C = (5 << 16) | 12,
	P5D = (5 << 16) | 13,
	P5E = (5 << 16) | 14,
	P5F = (5 << 16) | 15,	
	
	P60 = (6 << 16) | 0,
	P61 = (6 << 16) | 1,
	P62 = (6 << 16) | 2,
	P63 = (6 << 16) | 3,
	P64 = (6 << 16) | 4,
	P65 = (6 << 16) | 5,
	P66 = (6 << 16) | 6,
	P67 = (6 << 16) | 7,
	P68 = (6 << 16) | 8,
	P69 = (6 << 16) | 9,
	P6A = (6 << 16) | 10,
	P6B = (6 << 16) | 11,
	P6C = (6 << 16) | 12,
	P6D = (6 << 16) | 13,
	P6E = (6 << 16) | 14,
	P6F = (6 << 16) | 15,	
	
	P70 = (7 << 16) | 0,
	P71 = (7 << 16) | 1,
	P72 = (7 << 16) | 2,
	P73 = (7 << 16) | 3,
	P74 = (7 << 16) | 4,
	P75 = (7 << 16) | 5,
	P76 = (7 << 16) | 6,
	P77 = (7 << 16) | 7,
	P78 = (7 << 16) | 8,
	P79 = (7 << 16) | 9,
	P7A = (7 << 16) | 10,
	P7B = (7 << 16) | 11,
	P7C = (7 << 16) | 12,
	P7D = (7 << 16) | 13,
	P7E = (7 << 16) | 14,
	P7F = (7 << 16) | 15,	

	P80 = (8 << 16) | 0,
	P81 = (8 << 16) | 1,
	P82 = (8 << 16) | 2,
	P83 = (8 << 16) | 3,
	P84 = (8 << 16) | 4,
	P85 = (8 << 16) | 5,
	P86 = (8 << 16) | 6,
	P87 = (8 << 16) | 7,
	P88 = (8 << 16) | 8,
	P89 = (8 << 16) | 9,
	P8A = (8 << 16) | 10,
	P8B = (8 << 16) | 11,
	P8C = (8 << 16) | 12,
	P8D = (8 << 16) | 13,
	P8E = (8 << 16) | 14,
	P8F = (8 << 16) | 15,	
	
	P90 = (9 << 16) | 0,
	P91 = (9 << 16) | 1,
	P92 = (9 << 16) | 2,
	P93 = (9 << 16) | 3,
	P94 = (9 << 16) | 4,
	P95 = (9 << 16) | 5,
	P96 = (9 << 16) | 6,
	P97 = (9 << 16) | 7,
	P98 = (9 << 16) | 8,
	P99 = (9 << 16) | 9,
	P9A = (9 << 16) | 10,
	P9B = (9 << 16) | 11,
	P9C = (9 << 16) | 12,
	P9D = (9 << 16) | 13,
	P9E = (9 << 16) | 14,
	P9F = (9 << 16) | 15,	
	
	PA0 = (10 << 16) | 0,
	PA1 = (10 << 16) | 1,
	PA2 = (10 << 16) | 2,
	PA3 = (10 << 16) | 3,
	PA4 = (10 << 16) | 4,
	PA5 = (10 << 16) | 5,
	PA6 = (10 << 16) | 6,
	PA7 = (10 << 16) | 7,
	PA8 = (10 << 16) | 8,
	PA9 = (10 << 16) | 9,
	PAA = (10 << 16) | 10,
	PAB = (10 << 16) | 11,
	PAC = (10 << 16) | 12,
	PAD = (10 << 16) | 13,
	PAE = (10 << 16) | 14,
	PAF = (10 << 16) | 15,	
	
	PB0 = (11 << 16) | 0,
	PB1 = (11 << 16) | 1,
	PB2 = (11 << 16) | 2,
	PB3 = (11 << 16) | 3,
	PB4 = (11 << 16) | 4,
	PB5 = (11 << 16) | 5,
	PB6 = (11 << 16) | 6,
	PB7 = (11 << 16) | 7,
	PB8 = (11 << 16) | 8,
	PB9 = (11 << 16) | 9,
	PBA = (11 << 16) | 10,
	PBB = (11 << 16) | 11,
	PBC = (11 << 16) | 12,
	PBD = (11 << 16) | 13,
	PBE = (11 << 16) | 14,
	PBF = (11 << 16) | 15,	
	
	PC0 = (12 << 16) | 0,
	PC1 = (12 << 16) | 1,
	PC2 = (12 << 16) | 2,
	PC3 = (12 << 16) | 3,
	PC4 = (12 << 16) | 4,
	PC5 = (12 << 16) | 5,
	PC6 = (12 << 16) | 6,
	PC7 = (12 << 16) | 7,
	PC8 = (12 << 16) | 8,
	PC9 = (12 << 16) | 9,
	PCA = (12 << 16) | 10,
	PCB = (12 << 16) | 11,
	PCC = (12 << 16) | 12,
	PCD = (12 << 16) | 13,
	PCE = (12 << 16) | 14,
	PCF = (12 << 16) | 15,	

	PD0 = (13 << 16) | 0,
	PD1 = (13 << 16) | 1,
	PD2 = (13 << 16) | 2,
	PD3 = (13 << 16) | 3,
	PD4 = (13 << 16) | 4,
	PD5 = (13 << 16) | 5,
	PD6 = (13 << 16) | 6,
	PD7 = (13 << 16) | 7,
	PD8 = (13 << 16) | 8,
	PD9 = (13 << 16) | 9,
	PDA = (13 << 16) | 10,
	PDB = (13 << 16) | 11,
	PDC = (13 << 16) | 12,
	PDD = (13 << 16) | 13,
	PDE = (13 << 16) | 14,
	PDF = (13 << 16) | 15,
	
	PE0 = (14 << 16) | 0,
	PE1 = (14 << 16) | 1,
	PE2 = (14 << 16) | 2,
	PE3 = (14 << 16) | 3,
	PE4 = (14 << 16) | 4,
	PE5 = (14 << 16) | 5,
	PE6 = (14 << 16) | 6,
	PE7 = (14 << 16) | 7,
	PE8 = (14 << 16) | 8,
	PE9 = (14 << 16) | 9,
	PEA = (14 << 16) | 10,
	PEB = (14 << 16) | 11,
	PEC = (14 << 16) | 12,
	PED = (14 << 16) | 13,
	PEE = (14 << 16) | 14,
	PEF = (14 << 16) | 15,
	
	PF0 = (15 << 16) | 0,
	PF1 = (15 << 16) | 1,
	PF2 = (15 << 16) | 2,
	PF3 = (15 << 16) | 3,
	PF4 = (15 << 16) | 4,
	PF5 = (15 << 16) | 5,
	PF6 = (15 << 16) | 6,
	PF7 = (15 << 16) | 7,
	PF8 = (15 << 16) | 8,
	PF9 = (15 << 16) | 9,
	PFA = (15 << 16) | 10,
	PFB = (15 << 16) | 11,
	PFC = (15 << 16) | 12,
	PFD = (15 << 16) | 13,
	PFE = (15 << 16) | 14,
	PFF = (15 << 16) | 15,
	
	
	// QSB baseboard Arduino shield pins
	D0  = P16,
	D1  = P19,
	D2  = PF7,
	D3  = P43,
	D4  = PF5,
	D5  = P44,
	D6  = P45,
	D7  = PF3,
	D8  = P38,
	D9  = PF4,
	D10 = PF0,
	D11 = P40,
	D12 = P41,
	D13 = P42,
	D14 = P16,
	D15 = P17,
	
	A0  = PB0,
	A1  = P14,
	A2  = P13,
	A3  = P12,
	A4  = P11,
	A5  = P10,
	
	// Other Pin Names
	
	LED_R = P1A,
	LED_G = PB2,
	LED_B = P18,
	
	BUTTON = P20,
	
	SCL = P3B, 			//I2C clock
	SDA = P3A,		  //I2C data
	
  I2SMCLK = P5D,  // I2S master clock
	I2SBCLK = P31,  // I2S bit clock
	I2SDO   = P5E,  // I2S data line from MCU to CODEC (output data)
	I2SDI   = P30,  // I2S data line from CODEC to MCU (input data)
  I2SW    = P5F,  // I2S word (Left/righ channel selector) 
	I2SWS   = P3C,  // Word switch;  Low-> I2S Word conected to DACLRC. High -> I2S Word conected to ADCLRC
  
	TEST_PIN= P10,
	// Not connected
	NC = (int)0xFFFFFFFF


} Pin;

#define CLK_FREQ 200000000UL

#define HIGH 1
#define LOW 0

#define GET_PORT_INDEX(pin) ((pin) >> 16)
#define GET_PIN_INDEX(pin) ((pin) & 0xFF)


#endif

// *******************************ARM University Program Copyright � ARM Ltd 2015*************************************