// fm4_Slider-GUI.c

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "FM4_slider_interface.h"
#include "audio.h"


uint16_t buffer = 32000;
uint16_t freq1 = 110;		//darf aufgrund von Shannon nur ganzzahlige Werte von 1<freq<16000 annehmen
uint16_t freq2 = 220;

static int16_t i1 = 0;
static int16_t i2 = 0;

float b0 = 0;
float b1 = 0;
float b2 = 0;
float a1 = 0;
float a2 = 0;
float k = 0;
int fc = 1000;

//int16_t period;

//int16_t i = 0;

// functions:
int sawtooth(int freq, int oct, bool oszi);
int square(int freq, int oct, bool oszi);
int triangle(int freq, int oct, bool oszi);
int sine(int freq, int oct, bool oszi);
int mix(int in1, int in2, int lvl1, int lvl2);

int pval2int(int pval);
	
//float filt(int in, float b0, float b1, float b2, float a0, float a2);

float filt(int in);

// Funktion Pointer 
int (*funk_point_array[])(int, int ,bool) = {sine, square, triangle, sawtooth};

// create GUI slider instance data structure
struct FM4_slider_struct FM4_GUI;

/** I2C Interrupt handler **/
void I2S_HANDLER(void) {

	

	// audio in
	/*
	Square workig, one side (needs to be doubled, audio_OUT expected 32Bit)
	*
//	if (i == period / 2){
//		t = 1;
//	}
//	if (i == period){
//		t = -1;
//		i = 0;
//	}
//	i++;
//	
//	Main:period = 8000 / var;
//	

*
sawtooth working, needs to be doubled for both sides
*
//	period = 8000 / var;
//	t = i;
//	t = t / period;
//	if (i++ > period / 2) i = -(period / 2);

*
working triangle, needs to be doubled...
*
//period = 8000 / var;
//t = i;
//t = 2 * (t / period);
//if (up){
//	i++;
//}
//else if (!up){
//	i--;
//}
//if (i == (period / 4)){
//	up = false;
//}
//if (i == -(period / 4)){
//	up = true;
//}
	// audio out
	
//TEST:
	***********************************************************************************************************************************************
	(1)
	float right_float = 0;
	float left_float = 0;
	right_float = sin(2*PI*FM4_GUI.P_vals[0]*t);
	left_float = sin(2*PI*FM4_GUI.P_vals[0]*t);
	
	right_float = right_float * 10000;
	left_float = left_float * 10000;
	
	right = (int16_t)right_float;
	left = (int16_t)left_float;

	
	(2)
	right = sin(2*PI*110*t) * 1000;		//Signal in rechts und links geteilt, sin Funktion alterniert zw. 0...1. Multiplikation mit 10000: Alterniert zw. 0...10000
	left = sin(2*PI*55*t) * 1000;		//beide Signalanteile erhalten den selben Wert aus dem GUI_Slider. -> Selbe Frequez für links und rechts

	GUI slider:
		FM4_GUI.P_vals[0]
		
************************************************************************************************************************************************
	

working
*

//int16_t oszi1 = 0;
//int16_t oszi2 = 0;

//int32_t oszi1_OUT;
//int32_t oszi2_OUT;
//	t = i;
//	t = t / 8000;
//	
//	oszi1 = .5 * sin(2*PI*55*t) * 16000;			//2 Frequenzen werden generiert und faktorisiert mit werten 0<x<0,5 (GUI_slider!! mixer)
//	oszi2 = .5 * sin(2*PI*110*t) * 16000;			//16 BIT!!!
//	
//	oszi1_OUT = ((oszi1 << 16) & 0xffff0000) + (oszi1 & 0x0000ffff);			//Frequenzen werden 2x hintereinander in ein 32BIT array geschrieben für Ausgabe links und rechts
//	oszi2_OUT = ((oszi2 << 16) & 0xffff0000) + (oszi2 & 0x0000ffff);			//in audio_OUT werden beide arrays zusammen addiert -> Ausgabe zweier überlagerter Frequenzen 
//	
//	audio_OUT = (oszi1_OUT + oszi2_OUT);		//audio_OUT erwartet 32bit!!
//	if (i++ == 8000)i=0;

*/	
	
	int16_t oszi1;
	int16_t oszi2;
	
	if (FM4_GUI.P_vals[0] == 0){
		audio_OUT = 0x00000000;
	} else if (FM4_GUI.P_vals[0] == 1){
		oszi1 = (*funk_point_array[pval2int(FM4_GUI.P_vals[1])])(FM4_GUI.P_vals[3], FM4_GUI.P_vals[7], 0);
		oszi2 = 0x0000;
		audio_OUT = mix(oszi1, oszi2, FM4_GUI.P_vals[4], FM4_GUI.P_vals[6]);
	} else if (FM4_GUI.P_vals[0] == 2){
		oszi1 = 0x0000;
		oszi2 = (*funk_point_array[pval2int(FM4_GUI.P_vals[2])])(FM4_GUI.P_vals[5], FM4_GUI.P_vals[8], 1);
		audio_OUT = mix(oszi1, oszi2, FM4_GUI.P_vals[4], FM4_GUI.P_vals[6]);
	} else if (FM4_GUI.P_vals[0] == 3){
		oszi1 = (*funk_point_array[pval2int(FM4_GUI.P_vals[1])])(FM4_GUI.P_vals[3], FM4_GUI.P_vals[7], 0);
		oszi2 = (*funk_point_array[pval2int(FM4_GUI.P_vals[2])])(FM4_GUI.P_vals[5], FM4_GUI.P_vals[8], 1);
		audio_OUT = mix(oszi1, oszi2, FM4_GUI.P_vals[4], FM4_GUI.P_vals[6]);
	}
	
	

	/*
	oszi1 = (*funk_point_array[pval2int(FM4_GUI.P_vals[1])])(FM4_GUI.P_vals[3], 2, 1, 0);
	//oszi1 = 0x00000000;
	oszi2 = (*funk_point_array[pval2int(FM4_GUI.P_vals[2])])(FM4_GUI.P_vals[5], 2, 1, 1);
 	oszi1 = filt(oszi1);
	oszi2 = filt(oszi2);
	
	audio_OUT = mix(oszi1, oszi2, FM4_GUI.P_vals[4], FM4_GUI.P_vals[6]);			//¡audio_OUT expecting 32BIT!
	//audio_OUT = oszi2 & 0x0000ffff;
	*/
	/*
	oszi1 = sine(FM4_GUI.P_vals[3], 0 ,0);
	audio_OUT = ((oszi1 << 16) & 0xffff0000) + (oszi1 & 0x0000ffff);
	*/
	
	i2s_tx(audio_OUT);

}

int main(void)
{
  // initialize the slider interface by setting the baud rate (460800 or 921600)
  // and initial float values for each of the 6 slider parameter
  init_slider_interface(&FM4_GUI, 921600, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  
	/*
	k = tan(PI*fc/8000);
	b0 = (k * k) / (1 + sqrt(2) * k + (k * k));
	b1 = (2 * (k * k)) / (1 + sqrt(2) * k + (k * k));
	b2 = (k * k) / (1 + sqrt(2) * k + (k * k));
	a1 = (2 * ((k * k) - 
	1)) / (1 + sqrt(2) * k + (k* k));
	a2 = (1 - sqrt(2) * k + (k * k)) / (1 + sqrt(2) * k + (k * k));
	*/
	
	audio_init(hz32000, line_in, intr, I2S_HANDLER);
  
	
	

  while(1){
    update_slider_parameters(&FM4_GUI);
  }
}

// prototypes
int sawtooth(int freq, int oct, bool oszi){
	if (freq == 0){
		return 0;
	}
	static int16_t i;	//needs to be static, to be counted each time function is called
	if (!oszi){
		i = i1;
	}
	else if (oszi){
		i = i2;
	}
	int16_t period = 8000 / freq;			//period is the itervalltime
	int16_t out;	//out is the funktions feedback
	int16_t test;
	float t;
	float x = 0;
	if (oct == 0){
		x = 1;
	}
	if (oct > 0){
		x = (1<<oct);
	}
	else if (oct < 0){
		oct = abs(oct);
		x = (1<<oct);
		x = 1 / x;
	}
	test = period / (2 * x);
	
	t = x * 2 * i;
	t = t / period;				//t = i normalized to 1
	if (i > test) i = -(test);		//i rises to (period/2) and will be resetet to -(period/2)
	i++;
	out = t * 8000;
	
	if (!oszi){
		i1 = i;
	}
	else if (oszi){
		i2 = i;
	}
	return out;
}

int square(int freq, int oct, bool oszi){
	if (freq == 0){
	return 0;
	}
	static int16_t i;
	if (!oszi){
		i = i1;
	}
	else if (oszi){
		i = i2;
	}
	int16_t period = 8000 / freq;
	int16_t out;
	int16_t test;
	int16_t test1;
	float t;
	float x = 0;
	if (oct == 0){
		x = 1;
	}
	if (oct > 0){
		x = (1<<oct);
	}
	else if (oct < 0){
		oct = abs(oct);
		x = (1<<oct);
		x = 1 / x;
	}
	test = (period / (2 * x));
	test1 = (period / x);
	
	if (i == test){		//t = 1 for period/2<i<period
		t = 1;
	}
	if (i == test1){				//t = -1 for 0<i<period/2 ; i reset to 0
		t = -1;
		i = 0;
	}
	i++;
	out = t * 8000;
	
	if (!oszi){
		i1 = i;
	}
	else if (oszi){
		i2 = i;
	}
	return out;
}
int triangle(int freq, int oct, bool oszi){
	static int16_t i;
	if (!oszi){
		i = i1;
	}
	else if (oszi){
		i = i2;
	}
	if (freq == 0){
		return 0;
	}
	int16_t period = 8000 / freq;
	static bool up1 = true;
	static bool up2 = true;
	int16_t out = 0;
	float t;
	int16_t test;
	
	float x = 0;
	if (oct == 0){
		x = 1;
	}
	if (oct > 0){
		x = (1<<oct);
	}
	else if (oct < 0){
		oct = abs(oct);
		x = (1<<oct);
		x = 1 / x;
	}
	t = i;
	t = x * 4 * (t / period);		//t is max (period / 4) so * 4 is needed vor normalisation to 1
	test = (period / (x * 4));
	if (!oszi){
		if (up1){
			i++;
		}
		else if (!up1){
			i--;
		}
		if (i == test){		//(period / 4) because the triangular wave consists of four quarter waves. The distance between (period / 4) and -(period / 4) is (period / 2) and is doubled, because the wave takes the way back, too.
			up1 = false;
		}
		if (i == -test){
			up1 = true;
		}
	}
	
	if (oszi){
		if (up2){
			i++;
		}
		else if (!up2){
			i--;
		}
		if (i == test){		//(period / 4) because the triangular wave consists of four quarter waves. The distance between (period / 4) and -(period / 4) is (period / 2) and is doubled, because the wave takes the way back, too.
			up2 = false;
		}
		if (i == -test){
			up2 = true;
		}
	}
	
	
	
	out = t * 8000;
	
	if (!oszi){
		i1 = i;
	}
	else if (oszi){
		i2 = i;
	}
	return out;
}


int sine(int freq, int oct, bool oszi){		//oct soll octave shifting brigen, dafür muss oct werte von 1,2,4,8,16 oder 1/2,1/4,1/8,1/16 annehmen
	static int16_t i;
	if (freq == 0){
		return 0;
	}
	if (!oszi){
		i = i1;
	}
	else if (oszi){
		i = i2;
	}
	float s;
	int16_t out;
	float t;
	float x = 0;
	if (oct > 0){
		x = (1<<oct);
	}
	else if (oct < 0){
		oct = abs(oct);
		x = (1<<oct);
		x = 1 / x;
	}
	else if (oct == 0){
		x = 1;
	}
	t = i;
	t = t / 8000;
	s = sin(2*PI*x*freq*t);
	out = s * 16000;
	i++;
	if (i == 8000){
		i = 0;
	}
	
	if (!oszi){
		i1 = i;
	}
	else if (oszi){
		i2 = i;
	}
	return out;
}

int mix(int in1, int in2, int lvl1, int lvl2){		//in = input signals; lvl is a factor the corresponding signal is multiplied with, needs to be 1<lvl<10
	int32_t array1;
	int32_t array2;
	int32_t out;
	lvl1 = 11 - lvl1;
	lvl2 = 11 - lvl2;
	array1 = (((in1 / lvl1) << 16) & 0xffff0000) + ((in1 / lvl1) & 0x0000ffff);
	array2 = (((in2 / lvl2) << 16) & 0xffff0000) + ((in2 / lvl2) & 0x0000ffff);
	out = array1 + array2;
	return out;
}

/*
float filt (int in, float b0, float b1, float b2, float a1, float a2){
	static int16_t delay_array[5];
	static float coeff[5];
	coeff[0] = b0;
	coeff[1] = b1;
	coeff[2] = b2;
	coeff[3] = a1;
	coeff[4] = a2;

	float out = 0;

	for (int i = 0; i < 5; i++){
		out = out + coeff[i] * delay_array[i];
	}
	
	delay_array[4] = delay_array[3];
	delay_array[3] = out;
	delay_array[2] = delay_array[1];
	delay_array[1] = delay_array[0];
	delay_array[0] = in;
	
	return out;
	
}
*/

float filt(int in){
	float out = 0;
	static float h[13];
	h[0] = 0.03286106;
	h[1] = 0.05152205;
	h[2] = 0.06970883;
	h[3] = 0.08587008;
	h[4] = 0.09858317;
	h[5] = 0.10670565;
	h[6] = 0.10949837;
	h[7] = 0.10670565;
	h[8] = 0.09858317;
	h[9] = 0.08587008;
	h[10] = 0.06970883;
	h[11] = 0.05152205;
	h[12] = 0.03286106;
	
	static float array_in[13];
	for(int i = 0; i < 13; i++){
		array_in[i+1] = array_in[i];
	}
	array_in[0] = in;
	
	for(int i = 0; i < 13; i++){
		out = out + h[i] * array_in[i];
	}
	return out;
}

int pval2int(int pval){
	uint8_t out = pval;
	return out;
}
