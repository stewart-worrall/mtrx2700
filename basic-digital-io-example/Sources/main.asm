;*************************************************
;*       Program for Laboratory 
;*
;*       A line starting with a ';' is treated as
;*       a comment. Also, anything after ";" will
;*       be considered a comment. 
;*       Please comment your code.
;*       It is assessable!
;*
;*************************************************

; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



; Include derivative-specific definitions 
    INCLUDE 'derivative.inc' 

ROMStart  EQU  $4000  ; absolute address to place my code/constant data
LEDON	    equ	 $01	  ; Value to write to Port B

; variable/data section

          ORG RAMStart
 ; Insert here your data definition.
Counter   DS.W 1


; code section
          ORG   ROMStart


Entry:
_Startup:
          LDS   #RAMEnd+1       ; initialize the stack pointer


;**** you may want to write your own equates here *****

          ldaa    #$FF
          staa    DDRB    ; Configure PORTB as output
          staa    DDRJ   ; Port J as output to enable LED
          ldaa    #00    ; need to write 0 to J0
          staa    PTJ    ; to enable LEDs
          
start:    ldaa    #LEDON	; load accumulator with value for port B
          staa    PORTB	; write value to LED bank
          bsr     delay	; delay for 1 second
          clr     PORTB	; now turn the LED(s) off
          bsr     delay	; delay for 1 second
          bra     start	; loop back to beginning


delay:
          ; <your code goes here>
          ;
          rts		; return from subroutine
  


;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
          ORG   $FFFE
          DC.W  Entry           ; Reset Vector
