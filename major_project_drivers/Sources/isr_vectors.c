#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "iic.h"


#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void UnimplementedISR(void)
{
   /* Unimplemented ISRs trap.*/
   asm BGND;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SoftwareInterrupt(void)
{
   /* ISRs trap for software interrupt.*/
   volatile int interrupt_time;
   interrupt_time = TCNT;
   asm BGND;
}



typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFF80 = {     /* Interrupt table */
        UnimplementedISR,                 /* vector 0x40 */
        UnimplementedISR,                 /* vector 0x3F */
        UnimplementedISR,                 /* vector 0x3E */
        UnimplementedISR,                 /* vector 0x3D */
        UnimplementedISR,                 /* vector 0x3C */
        UnimplementedISR,                 /* vector 0x3B */
        UnimplementedISR,                 /* vector 0x3A */
        UnimplementedISR,                 /* vector 0x39 */
        UnimplementedISR,                 /* vector 0x38 */
        UnimplementedISR,                 /* vector 0x37 */
        UnimplementedISR,                 /* vector 0x36 */
        UnimplementedISR,                 /* vector 0x35 */
        UnimplementedISR,                 /* vector 0x34 */
        UnimplementedISR,                 /* vector 0x33 */
        UnimplementedISR,                 /* vector 0x32 */
        UnimplementedISR,                 /* vector 0x31 */
        UnimplementedISR,                 /* vector 0x30 */
        UnimplementedISR,                 /* vector 0x2F */
        UnimplementedISR,                 /* vector 0x2E */
        UnimplementedISR,                 /* vector 0x2D */
        UnimplementedISR,                 /* vector 0x2C */
        UnimplementedISR,                 /* vector 0x2B */
        UnimplementedISR,                 /* vector 0x2A */
        UnimplementedISR,                 /* vector 0x29 */
        UnimplementedISR,                 /* vector 0x28 */
        UnimplementedISR,                 /* vector 0x27 */
        UnimplementedISR,                 /* vector 0x26 */
        UnimplementedISR,                 /* vector 0x25 */
        UnimplementedISR,                 /* vector 0x24 */
        UnimplementedISR,                 /* vector 0x23 */
        UnimplementedISR,                 /* vector 0x22 */
        UnimplementedISR,                 /* vector 0x21 */
        UnimplementedISR,                 /* vector 0x20 */
        UnimplementedISR,                 /* vector 0x1F */
        UnimplementedISR,                 /* vector 0x1D */
        UnimplementedISR,                 /* vector 0x1C */
        UnimplementedISR,                 /* vector 0x1B */
        UnimplementedISR,                 /* vector 0x1A */
        UnimplementedISR,                 /* vector 0x19 (PORT H) */
        UnimplementedISR,                 /* vector 0x18 (PORT J) */
        UnimplementedISR,                 /* vector 0x17 (ATD1) */
        UnimplementedISR,                 /* vector 0x16 (ATD0) */
        UnimplementedISR,                 /* vector 0x15 (SCI1) */
        UnimplementedISR,                 /* vector 0x14 (SCI0) */
        UnimplementedISR,                 /* vector 0x13 */
        UnimplementedISR,                 /* vector 0x12 */
        UnimplementedISR,                 /* vector 0x11 */
        UnimplementedISR,                 /* vector 0x10 (TOF) */
        TC7_ISR,                          /* vector 0x0F (TIE, C7I)  */
        UnimplementedISR,                 /* vector 0x0E (TIE, C6I)  */
        UnimplementedISR,                 /* vector 0x0C (TIE, C5I)  */
        UnimplementedISR,                 /* vector 0x0C (TIE, C4I)  */
        UnimplementedISR,                 /* vector 0x0B (TIE, C3I)  */
        UnimplementedISR,                 /* vector 0x0A (TIE, C2I)  */
        UnimplementedISR,                 /* vector 0x09 (TIE, C1I)  */
        UnimplementedISR,                 /* vector 0x08 (TIE, C0I) */
        UnimplementedISR,                 /* vector 0x07 (RTIE) */
        UnimplementedISR,                 /* vector 0x06 */
        UnimplementedISR,                 /* vector 0x05 */
        SoftwareInterrupt,                 /* vector 0x04 */
        UnimplementedISR,                 /* vector 0x03 */
        UnimplementedISR,                 /* vector 0x02 */
        UnimplementedISR,                 /* vector 0x01 */
       // _Startup                          /* vector 0x00 (RESET) */
   };
