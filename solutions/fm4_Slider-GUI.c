// fm4_Slider-GUI.c

#include "audio.h"
#include "FM4_slider_interface.h"

// create GUI slider instance data structure
struct FM4_slider_struct FM4_GUI;

/** I2C Interrupt handler **/
void I2S_HANDLER(void) {

	// rx audio signal
	audio_IN = i2s_rx();

  // do some processing
  
  // tx audio signal to CODEC buffer
	i2s_tx(audio_IN);
}

int main(void)
{
  // initialize the slider interface by setting the baud rate (460800 or 921600)
  // and initial float values for each of the 6 slider parameter
  init_slider_interface(&FM4_GUI, 460800, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);
  
  // see drivers/audio.c for details
  audio_init(hz8000, line_in, intr, I2S_HANDLER);
  
  // send a test string to command line
  write_uart0("Hello FM4 world!\r\n");
  
  while(1){
    update_slider_parameters(&FM4_GUI);
  }
}
