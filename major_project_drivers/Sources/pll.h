/*************************PLL.h***************************
*   boosts the CPU clock to 48 MHz                       *
*                                                        *
*   Created by Theodore Deden on 20 January 2004.        *
*   Modified by Theodore Deden on 9 February 2004.       *
*   Last Modified by Jonathan Valvano 2/9/04.            *
*                                                        *
*   Distributed underthe provisions of the GNU GPL ver 2 *
*   Copying, redistributing, modifying is encouraged.    *
*                                                        *
*********************************************************/

// modified to define _BUSCLOCK
// PLL now running at 48 MHz to be consistent with HCS12 Serial Monitor
// fw-07-04


#ifndef _PPL_H_
#define _PLL_H_

/* Define the desired bus clock frequency:
   no PLL (crystal) -> SYSCLOCK = 4 MHz   -> BUSCLOCK = 2 MHz
   PLL on           -> SYSCLOCK = 48 MHz  -> BUSCLOCK = 24 MHz
   This is used by sci0.c and/or sci1.c to determine the baud rate divider */
#define _BUSCLOCK 24


//********* PLL_Init ****************
// Set PLL clock to 48 MHz, and switch 9S12 to run at this rate
// Inputs: none
// Outputs: none
// Errors: will hang if PLL does not stabilize 
void PLL_Init(void);

#endif  /* _PLL_H_ */

