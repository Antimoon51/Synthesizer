// FM4_slider_interface.h
/*
	Header code module to support the FM4 S6E2CC GUI slider interface app
	
	Six slider variables are stored in the global float array P_vals[6]. The initial
	values given to this array in the main module are the values used when a
	real-time DSP application first launches on the FM4 S6E2CC board.

  The main component in making this interface work is a UART running through the
	virtual comm port provided along side the CMSIS-DAP debug interface on the board.

  Copyright (C) 2016 Mark Wickert
	
	The Spansion (now part of Cypress) software is ackowledged below.
*/

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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mfs_hl.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define SAMPLE_UART_TX_BUFFSIZE         (128)
#define SAMPLE_UART_RX_BUFFSIZE         (256)
#define SAMPLE_UART_RX_BUFF_FILL_LVL    (1) // read just one character

struct FM4_slider_struct
{
	float32_t P_vals[6];
	char P_rcvd[10];
	uint8_t P_idx;
	stc_mfs_hl_uart_config_t stcMfsHlUartCfg;
	uint8_t  au8ReadBuf[2];
	uint16_t u16ReadCnt;
  uint8_t H_found;
	uint8_t idx_P_rec;
};

void init_slider_interface(struct FM4_slider_struct *FM4_slider,
	                         uint32_t baud_rate,
                           float32_t P_val0, float32_t P_val1, float32_t P_val2,
                           float32_t P_val3, float32_t P_val4, float32_t P_val5);

void update_slider_parameters(struct FM4_slider_struct *FM4_slider);

void write_uart0(char* message);
