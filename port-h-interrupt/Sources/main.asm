;*****************************************************************
;* Demonstration of interrupts using the I/O from port H         *
;* author: Eduardo Nebot                                         *
;* updated: Stewart Worrall 3/2021                               *
;*****************************************************************


; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point

; Include derivative-specific definitions 
		INCLUDE 'derivative.inc' 
		

ROMStart    EQU  $4000  ; absolute address to place my code/constant data


; variable/data section
 ifdef _HCS12_SERIALMON
            ORG $3FFF - (RAMEnd - RAMStart)
 else
            ORG RAMStart
 endif


Counter     DS.W 1    ; define a variable in RAM to store the current count

PORT_H_MASK EQU %00011001      ; mask for triggering inputs in port H
                               ; this will trigger if PH0, PH3 or PH4 have a 
                               ; transition between high and low

; code section
            ORG   ROMStart

Entry:
_Startup:

; *****************************************
;
;   Interrupt example using parallel port
;   Pins H0 and H4 are programmed as falling edge
;   interrupt. These port are connected to the dip
;   switches. Each time the user generate a 0 - 1
;   transition an interrupt is generated increasing
;   a counter displayed in LEDs
;
;   Use dip swithces 4 or 8. With dip switch 8 "on" you
;   can also use SW5 and will trigger interrupt when
;   switch releases
;

;    Main Program
;    enable the interrupt, loop while waiting for interrupt to trigger

     BSR   initialise_io   ;  set parallel interrupt
     BSR   set_led         ;  Enable LED to be operated with PORTB
     
     ldaa #$1              ; initialise counter as 1
     staa Counter         ; store the value in the counter variable
     
Loop 
     BRA Loop         ; Do nothing (stays in this loop forever)


; Program service functions

;  set parameters for Parallel PORTH interrupt
;  H0, H3 and H4 enables as input interrupts
;
initialise_io

      sei           ; disable interrupt
      LDAA  #PORT_H_MASK    ; to enable interrupt on H0, H3 and H4
      staa  PIEH    ; enable both
      
      coma          ; we want to trigger the interrupt on a falling edge, so 
                    ; we need to set the PPSH to 0 for each of the triggering
                    ; pins. This function inverts the port H mask to achieve this
                    
      staa  PPSH    ; select falling edge for interrupts
      cli           ; enable interrups
      rts           ; return
      
      

;   Interrupt service routine
;   each time this code runs is due to an interrupt
;   adds an amount to the counter and displays the value
;   using LEDs. Both flags are reset (only one should
;   be set. If both are pressed simultaneously this
;   program will only action one of them)

port_h_isr
      ldaa PTH        ; load the current value of port H
                      ; e.g. if H3 is pressed, PTH will be 1111 0111
                      
      coma            ; As the default value is 1 for each input, 
                      ; take the inverse of each bit
                      ; this will leave register A with an active 
                      ; bit for each button that was pressed
                      ; e.g. if H3 is pressed, A is now 0000 1000
                      
      adda Counter    ; add this to the counter and store
      staa Counter
      
      staa PORTB      ; send the count to LED
      
      bset PIFH, #PORT_H_MASK ; reset all interrupt flags 
                              ; by setting PIFH to 1 for each 
                              ; (I assume I can process fast enough)
      
      RTI             ; return from interrupt
      

;    Enabling LED
;    Set port J and B as outputs
;    Write 0 to port J to enable LEDs
;    Write 0F to port B to see it is running

set_led
    ldaa  #%11111111 ; code for output  ( same as $FF )
    staa  DDRB       ; B programmed as output
    staa  DDRJ       ; J programmed as output
    ldaa #$00        ;  Send low to J
    staa  PTJ        ; to enable LEDs
    ldaa #$0F        ; get a pattern to indicate
    staa  PORTB      ; the system is running 
    rts              ; back to main

    
;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            
    ORG  $FFCC
    DC.W  port_h_isr ; set interrupt vector table for port H
   
    ORG   $FFFE
    DC.W  Entry      ; Reset Vector
