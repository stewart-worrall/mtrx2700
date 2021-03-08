;*****************************************************************
;* This stationery serves as the framework for a                 *
;* user application (single file, absolute assembly application) *
;* For a more comprehensive program that                         *
;* demonstrates the more advanced functionality of this          *
;* processor, please see the demonstration applications          *
;* located in the examples subdirectory of the                   *
;* Freescale CodeWarrior for the HC12 Program directory          *
;*****************************************************************

; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



; Include derivative-specific definitions 
		INCLUDE 'derivative.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data

; variable/data section

            ORG RAMStart
; Insert here your data definition.
output_string   DS.B  16     ; allocate 16 bytes at the address output_string
input_string    FCC   "this is a string"  ; make a string in memory
test_character  FCC "s"
string_length   DS.B  1     ; one byte to store the string length
test_count      DS.B  1     ; one byte to store the count of the test_character



; code section
            ORG   ROMStart


Entry:
_Startup:
            LDS   #RAMEnd+1       ; initialize the stack pointer

            CLI                     ; enable interrupts
mainLoop:
            LDAA  #0
            STAA  test_count

            LDAA  #$10        ; store the value 16 (the length of the string)
            STAA  string_length
            
            LDX   #input_string
            LDY   #output_string

innerLoop:    
            LDAB  1, x+
            CMPB  test_character
            BNE   skipUpdate
            STAB  0, y
            INC   test_count
            
skipUpdate:
            INY
            DECA
            BNE innerLoop                        
            
            BRA mainLoop

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
