// fm4_Slider-GUI.c

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "FM4_slider_interface.h"
#include "audio.h"



uint16_t freq1 = 55;		//darf aufgrund von Shannon nur ganzzahlige Werte von 1<var<16000 annehmen
uint16_t freq2 = 110;

//int16_t count;

//int16_t i = 0;

// functions:
int triangle(int freq, int oct, bool upshift);
int sine(int freq, int oct, bool upshift);
int sawtooth(int freq, int oct, bool upshift);
int square(int freq, int oct, bool upshift);
int mix(int in1, int in2, int lvl1, int lvl2);
	
	
// create GUI slider instance data structure
struct FM4_slider_struct FM4_GUI;

/** I2C Interrupt handler **/
void I2S_HANDLER(void) {
	

	// audio in
	/*
	Square workig, one side (needs to be doubled, audio_OUT expected 32Bit)
	*/
//	if (i == count / 2){
//		t = 1;
//	}
//	if (i == count){
//		t = -1;
//		i = 0;
//	}
//	i++;
//	
//	Main:count = 32000 / var;
//	

/*
sawtooth working, needs to be doubled for both sides
*/
//	count = 32000 / var;
//	t = i;
//	t = t / count;
//	if (i++ > count / 2) i = -(count / 2);

/*
working triangle, needs to be doubled...
*/
//count = 32000 / var;
//t = i;
//t = 2 * (t / count);
//if (up){
//	i++;
//}
//else if (!up){
//	i--;
//}
//if (i == (count / 4)){
//	up = false;
//}
//if (i == -(count / 4)){
//	up = true;
//}
	// audio out
	
//TEST:
	/***********************************************************************************************************************************************
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
		
************************************************************************************************************************************************/
	
/*
working
*/

//int16_t oszi1 = 0;
//int16_t oszi2 = 0;

//int32_t oszi1_OUT;
//int32_t oszi2_OUT;
//	t = i;
//	t = t / 32000;
//	
//	oszi1 = .5 * sin(2*PI*55*t) * 16000;			//2 Frequenzen werden generiert und faktorisiert mit werten 0<x<0,5 (GUI_slider!! mixer)
//	oszi2 = .5 * sin(2*PI*110*t) * 16000;			//16 BIT!!!
//	
//	oszi1_OUT = ((oszi1 << 16) & 0xffff0000) + (oszi1 & 0x0000ffff);			//Frequenzen werden 2x hintereinander in ein 32BIT array geschrieben für Ausgabe links und rechts
//	oszi2_OUT = ((oszi2 << 16) & 0xffff0000) + (oszi2 & 0x0000ffff);			//in audio_OUT werden beide arrays zusammen addiert -> Ausgabe zweier überlagerter Frequenzen 
//	
//	audio_OUT = (oszi1_OUT + oszi2_OUT);		//audio_OUT erwartet 32bit!!
//	if (i++ == 32000)i=0;
	
	
	int16_t oszi1;
	int16_t oszi2;
	oszi1 = sawtooth(freq2, 3, 0);
	//oszi1 = 0x00000000;
	oszi2 = sawtooth(freq2, 3, 0);
	
	audio_OUT = mix(oszi1, oszi2, 1, 1);			//¡audio_OUT expecting 32BIT!
	i2s_tx(audio_OUT);
}

int main(void)
{
  // initialize the slider interface by setting the baud rate (460800 or 921600)
  // and initial float values for each of the 6 slider parameter
  init_slider_interface(&FM4_GUI, 460800, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  
	audio_init(hz32000, line_in, intr, I2S_HANDLER);
  
	

  while(1){
    update_slider_parameters(&FM4_GUI);
  }
}

// prototypes
int sawtooth(int freq, int oct,  bool upshift){
	static int16_t i = 0;		//needs to be static, to be countetd each time function is called
	int16_t count = 32000 / freq;			//count is the itervalltime
	int16_t out;										//out is the funktions feedback
	float t;
	float x;
	if (upshift){
		x = (1<<oct);
	}
	else if (!upshift){
		x = (1<<oct);
		x = 1 / x;
	}
	t = x * i;
	t = t / count;				//t = i normalized to 1
	if (i > count / (2 * x)) i = -(count / (2 * x));		//i rises to (count/2) and will be resetet to -(count/2)
	i++;
	out = t * 8000;
	return out;
}

int square(int freq, int oct, bool upshift){
	static int16_t i = 0;
	int16_t count = 32000 / freq;
	int16_t out;
	float t;
	if (i == count / 2){		//t = 1 for count/2<i<count
		t = 1;
	}
	if (i == count){				//t = -1 for 0<i<count/2 ; i reset to 0
		t = -1;
		i = 0;
	}
	i++;
	out = t * 8000;
	return out;
}
int triangle(int freq, int oct, bool upshift){
	static int16_t i = 0;
	int16_t count = 32000 / freq;
	static bool up = true;
	int16_t out;
	float t;
	t = i;
	t = 4 * (t / count);		//t is max (count / 4) so * 4 is needed vor normalisation to 1
	if (up){
		i++;
	}
	else if (!up){
		i--;
	}
	if (i == (count / 4)){		//(count / 4) because the triangular wave consists of four quarter waves. The distance between (count / 4) and -(count / 4) is (count / 2) and is doubled, because the wave takes the way back, too.
		up = false;
	}
	if (i == -(count / 4)){
		up = true;
	}
	out = t * 8000;
	return out;
}


int sine(int freq, int oct, bool upshift){		//oct soll octave shifting brigen, dafür muss oct werte von 1,2,4,8,16 oder 1/2,1/4,1/8,1/16 annehmen
	static int16_t i = 0;
	float s;
	int16_t out;
	float t;
	float x;
	if (upshift){
		x = (1<<oct);
	}
	else if (!upshift){
		x = (1<<oct);
		x = 1 / x;
	}
	t = i;
	t = t / 32000;
	s = sin(2*PI*x*freq*t);
	out = s * 16000;
	if (i++ == 32000) i = 0;
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
