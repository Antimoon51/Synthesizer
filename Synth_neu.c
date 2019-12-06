// fm4_Slider-GUI.c

#include <math.h>
#include <stdio.h>

#include "FM4_slider_interface.h"
#include "audio.h"

//#define PI 3.14159265358979
int16_t oszi1 = 0;
int16_t oszi2 = 0;
float right_float = 0;
float left_float = 0;
int32_t oszi1_OUT;
int32_t oszi2_OUT;
// create GUI slider instance data structure
struct FM4_slider_struct FM4_GUI;

/** I2C Interrupt handler **/
void I2S_HANDLER(void) {
	
	static uint16_t i = 0;
	static float t = 0;
	// audio in
	t = i;
	t = t / 32000;

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
	
	oszi1 = .5 * sin(2*PI*55*t) * 16000;			//2 Frequenzen werden generiert und faktorisiert mit werten 0<x<0,5 (GUI_slider!! mixer)
	oszi2 = .5 * sin(2*PI*110*t) * 16000;			//16 BIT!!!
	
	oszi1_OUT = ((oszi1 << 16) & 0xffff0000) + (oszi1 & 0x0000ffff);			//Frequenzen werden 2x hintereinander in ein 32BIT array geschrieben für Ausgabe links und rechts
	oszi2_OUT = ((oszi2 << 16) & 0xffff0000) + (oszi2 & 0x0000ffff);			//in audio_OUT werden beide arrays zusammen addiert -> Ausgabe zweier überlagerter Frequenzen 
	
	audio_OUT = (oszi1_OUT + oszi2_OUT);		//audio_OUT erwartet 32bit!!
	if (i++ == 32000)i=0;
	
	
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
