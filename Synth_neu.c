// fm4_Slider-GUI.c

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "FM4_slider_interface.h"
#include "audio.h"


int16_t oszi1 = 0;
int16_t oszi2 = 0;
float right_float = 0;
float left_float = 0;
int32_t oszi1_OUT;
int32_t oszi2_OUT;
uint16_t var = 55;		//darf aufgrund von Shannon nur ganzzahlige Werte von 1<var<16000 annehmen
int16_t out;
float s;

int16_t i = 0;
float t = 0;

int16_t count;
bool up = true;


void sawtooth(void){
	
	t = i;
	t = t / count;
	if (i++ > count / 2) i = -(count / 2);
	out = t * 8000;
}

void square(void){
	if (i == count / 2){
		t = 1;
	}
	if (i == count){
		t = -1;
		i = 0;
	}
	i++;
	out = t * 8000;
}
void triangle(void){
	t = i;
	t = 2 * (t / count);
	if (up){
		i++;
	}
	else if (!up){
		i--;
	}
	if (i == (count / 4)){
		up = false;
	}
	if (i == -(count / 4)){
		up = true;
	}
	out = t * 8000;
}


void sine(void){
	t = i;
	t = t / 32000;
	s = sin(2*PI*var*t);
	out = s * 16000;
	if (i++ == 32000) i = 0;
}
	
	
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
	
	triangle();
	
	audio_OUT = ((out << 16) & 0xffff0000) + (out & 0x0000ffff);
	
	i2s_tx(audio_OUT);
}

int main(void)
{
  // initialize the slider interface by setting the baud rate (460800 or 921600)
  // and initial float values for each of the 6 slider parameter
  init_slider_interface(&FM4_GUI, 460800, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  
	audio_init(hz32000, line_in, intr, I2S_HANDLER);
  
	count = 32000 / var;

  while(1){
    update_slider_parameters(&FM4_GUI);
  }
}
