// FM4_slider_interface.c
/*
	Code module to support the FM4 S6E2CC GUI slider interface app
	
	Six slider variables are stored in the global float array P_vals[6]. The initial
	values given to this array in the main module are the values used when a
	real-time DSP application first launches on the FM4 S6E2CC board.

  The main component in making this interface work is a UART running through the
	virtual comm port provided along side the CMSIS-DAP debug interface on the board.

  Copyright (C) 2016 Mark Wickert
	
	
	The Spansion (now part of Cypress) software is ackowledged below.
*/

#include "FM4_slider_interface.h"

/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved.
*
* This software is owned and published by:
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion
* components. This software is licensed by Spansion to be adapted only
* for use in systems utilizing Spansion components. Spansion shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein.  Spansion is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

static uint8_t au8UartTxBuf[SAMPLE_UART_TX_BUFFSIZE];
static uint8_t au8UartRxBuf[SAMPLE_UART_RX_BUFFSIZE];

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

void init_slider_interface(struct FM4_slider_struct *FM4_slider,
	                            uint32_t baud_rate,
                              float32_t P_val0, float32_t P_val1, float32_t P_val2,
                              float32_t P_val3, float32_t P_val4, float32_t P_val5, float32_t P_val6, float32_t P_val7, float32_t P_val8)
{
	//Variables for parameter slider communication
	FM4_slider->P_vals[0] = P_val0;
  FM4_slider->P_vals[1] = P_val1;
	FM4_slider->P_vals[2] = P_val2;
	FM4_slider->P_vals[3] = P_val3;
	FM4_slider->P_vals[4] = P_val4;
	FM4_slider->P_vals[5] = P_val5;
	FM4_slider->P_vals[5] = P_val6;
	FM4_slider->P_vals[5] = P_val7;
	FM4_slider->P_vals[5] = P_val8;
	FM4_slider->H_found = 0;
	// Baud rate : 115200 bps (230400, 460800, 921600)
	FM4_slider->stcMfsHlUartCfg.u32DataRate = baud_rate; 
	// Bit direction : LSB first
	FM4_slider->stcMfsHlUartCfg.bBitDirection = FALSE; 
  // Inverted serial data format : NRZ
	FM4_slider->stcMfsHlUartCfg.bSignalSystem = FALSE; 
  // Inverted serial data format : NRZ
	FM4_slider->stcMfsHlUartCfg.bHwFlow = FALSE;
  // Inverted serial data format : NRZ
	FM4_slider->stcMfsHlUartCfg.pu8TxBuf = au8UartTxBuf;
  // Use the reception buffer in the driver (*2)
	FM4_slider->stcMfsHlUartCfg.pu8RxBuf = au8UartRxBuf;
  // Size of transmit buffer (for *1)  : 128bytes
	FM4_slider->stcMfsHlUartCfg.u16TxBufSize = SAMPLE_UART_TX_BUFFSIZE;
  // Size of reception buffer (for *2) : 256bytes
	FM4_slider->stcMfsHlUartCfg.u16RxBufSize = SAMPLE_UART_RX_BUFFSIZE; 
  // Unread counts of reception buffer to call RX Callback function : 1byte
	FM4_slider->stcMfsHlUartCfg.u16RxCbBufFillLvl = SAMPLE_UART_RX_BUFF_FILL_LVL;
	// Uart mode : Normal mode
	FM4_slider->stcMfsHlUartCfg.u8UartMode = MfsUartNormal;
  // Parity    : none
	FM4_slider->stcMfsHlUartCfg.u8Parity = MfsParityNone;
  // Stop bit  : 1bit
	FM4_slider->stcMfsHlUartCfg.u8StopBit = MfsOneStopBit;
  // Data bits : 8bit
	FM4_slider->stcMfsHlUartCfg.u8CharLength = MfsEightBits;
  // FIFO      : not use
	FM4_slider->stcMfsHlUartCfg.u8FifoUsage = MfsHlUseNoFifo; 
  // Callback function : if NULL ==> interrupt not used
	FM4_slider->stcMfsHlUartCfg.pfnRxCb = NULL; 
  // Callback function : if NULL ==> interrupt not used
	FM4_slider->stcMfsHlUartCfg.pfnTxCb = NULL; 
	
	//************ Configure UART Serial0 *********************
	// Disable Analog input (P21:SIN0_0/AN17, P22:SOT0_0/AN16)
	FM4_GPIO->ADE = 0;
	// Set UART Ch0_0 Port (SIN, SOT)
	FM4_GPIO->PFR2 = FM4_GPIO->PFR2 | 0x0006;
	FM4_GPIO->EPFR07 = FM4_GPIO->EPFR07 | 0x00000040;
	//*********************************************************
	
	// Initialize the MFS ch.0 as UART
	if (Ok != Mfs_Hl_Uart_Init(&MFS0, &FM4_slider->stcMfsHlUartCfg))
	{
		while(1);
	}
  
	// Write a test string
	//Mfs_Hl_Write(&MFS0, (uint8_t*) "Getting started\r\n", 17, FALSE, FALSE);
}
	
	
void update_slider_parameters(struct FM4_slider_struct *FM4_slider)
{
	// If data is received from UART,
	//Get character from internal buffer and
	//decode char string into slider float32_t
	//held in P_vals[] array
	// Receive data from UART asynchronously (Non-blocking)
	
	if (Ok != Mfs_Hl_Read(&MFS0, FM4_slider->au8ReadBuf, &FM4_slider->u16ReadCnt, 1, FALSE))
	{
		Mfs_Hl_Write(&MFS0, (uint8_t*) "Read Error\r\n", 12, FALSE, FALSE);
	}
	
	if ((FM4_slider->u16ReadCnt == 1) && (FM4_slider->au8ReadBuf[0] >= 0x2D)) {
		//gpio_set(TEST_PIN, HIGH); //Pin A3/P10
		Mfs_Hl_Write(&MFS0, FM4_slider->au8ReadBuf, FM4_slider->u16ReadCnt, FALSE, FALSE);
		//Wait for header char 'H'
		if (FM4_slider->H_found == 0) {
			if (FM4_slider->au8ReadBuf[0] == 0x48) {  // 'H' <=> 0x48
				//gpio_set(A4, HIGH); // A4/P11
				FM4_slider->H_found = 1;
			}
		}
		else {					
			// '0' <=> 0x30, '9' <=> 0x39, '.' <=> 0x2E, '-' <=> 0x2D
			if ((FM4_slider->au8ReadBuf[0] >= 0x30 && FM4_slider->au8ReadBuf[0] <= 0x39) || 
					(FM4_slider->au8ReadBuf[0] == 0x2E) || (FM4_slider->au8ReadBuf[0] == 0x2D)) {
				FM4_slider->P_rcvd[FM4_slider->idx_P_rec] = (char) FM4_slider->au8ReadBuf[0];
				FM4_slider->idx_P_rec++;
			}
			else if (FM4_slider->au8ReadBuf[0] == 0x3A) { // ':' <=> 0x3A
				FM4_slider->P_idx = (uint8_t) atoi(FM4_slider->P_rcvd);						
				FM4_slider->idx_P_rec = 0;
				memset(FM4_slider->P_rcvd, 0, sizeof(FM4_slider->P_rcvd)); //clear received char array
			}
			else if (FM4_slider->au8ReadBuf[0] == 0x54) { // 'T' <=> 0x54
				FM4_slider->P_vals[FM4_slider->P_idx] = (float32_t) atof(FM4_slider->P_rcvd);

				memset(FM4_slider->P_rcvd, 0, sizeof(FM4_slider->P_rcvd));
				FM4_slider->idx_P_rec = 0;
				FM4_slider->H_found = 0;
			}
			else {
				//memset(P_rcvd, 0, sizeof(P_rcvd));
				FM4_slider->H_found = 0;
			}
		}
	}
}


void write_uart0(char* message)
{
	// write a string to UART0
	Mfs_Hl_Write(&MFS0, (uint8_t*) message, strlen(message), FALSE, FALSE);
}


/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
