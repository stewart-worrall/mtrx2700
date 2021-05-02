/*************************PLL.C***************************
*   boosts the CPU clock to 48 MHz                       *
*                                                        *
*   Created by Theodore Deden on 20 January 2004.        *
*   Modified by Theodore Deden on 9 February 2004.       *
*   Last Modified by Jonathan Valvano 2/16/04.            *
*                                                        *
*   Distributed underthe provisions of the GNU GPL ver 2 *
*   Copying, redistributing, modifying is encouraged.    *
*                                                        *
*********************************************************/

// modified to make PLL_Init depend on _BUSCLOCK (defined in pll.h)
// PLL now running at 48 MHz to be consistent with HCS12 Serial Monitor
// fw-07-04

#include <hidef.h>              /* common defines and macros */
#include <mc9s12dp256.h>        /* derivative information */
#include "pll.h"                /* macro _BUSCLOCK */

//********* PLL_Init ****************
// Set PLL clock to 48 MHz, and switch 9S12 to run at this rate
// Inputs: none
// Outputs: none
// Errors: will hang if PLL does not stabilize 
void PLL_Init(void){

  /* ensure we're running the controller at an appropriate clock speed */
  #if (_BUSCLOCK != 24 && _BUSCLOCK != 4)
  #error pll.h: _BUSCLOCK has to be set to 4 (MHz) or 24 (MHz)
  #endif
  
  /* set PLL clock speed */
  #if _BUSCLOCK == 24
  SYNR = 0x05;      // PLLOSC = 48 MHz
  #else
  SYNR = 0x00;      // PLLOSC = 8 MHz
  #endif
  
  REFDV = 0x00;
  
  /* PLLCLK = 2 * OSCCLK * (SYNR + 1) / (REFDV + 1)
	   Values above give PLLCLK of 48 MHz with 4 MHz crystal. 
	   (OSCCLK is Crystal Clock Frequency)                    */
  
  CLKSEL = 0x00;
  
  /*Meaning for CLKSEL:
  Bit 7: PLLSEL = 0 Keep using OSCCLK until we are ready to switch to PLLCLK
  Bit 6: PSTP   = 0 Do not need to go to Pseudo-Stop Mode
  Bit 5: SYSWAI = 0 In wait mode system clocks stop.
  But 4: ROAWAI = 0 Do not reduce oscillator amplitude in wait mode.
  Bit 3: PLLWAI = 0 Do not turn off PLL in wait mode
  Bit 2: CWAI	= 0 Do not stop the core during wait mode
  Bit 1: RTIWAI = 0 Do not stop the RTI in wait mode
  Bit 0: COPWAI = 0 Do not stop the COP in wait mode
  */
  
  
  PLLCTL = 0xD1;
  
  /*Meaning for PLLCTL:
  Bit 7: CME   = 1; Clock monitor enable - reset if bad clock when set
  Bit 6: PLLON = 1; PLL On bit
  Bit 5: AUTO  = 0; No automatic control of bandwidth, manual through ACQ
  But 4: ACQ   = 1; 1 for high bandwidth filter (acquisition); 0 for low (tracking)
  Bit 3:            (Not Used by 9s12c32)
  Bit 2: PRE   = 0; RTI stops during Pseudo Stop Mode
  Bit 1: PCE   = 0; COP diabled during Pseudo STOP mode
  Bit 0: SCME  = 1; Crystal Clock Failure -> Self Clock mode NOT reset.
  
  */
  
  while((CRGFLG&0x08) == 0){ 	  // Wait for PLLCLK to stabilize.
  }  
  CLKSEL_PLLSEL = 1;  // Switch to PLL clock
}

