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
array_1       DC.B  4,7,12,36,21,45,80
number_of_elements_1 DC.B  7

array_2       DC.B  4,7,12,21,36,45,60,64,68,71,82,103
number_of_elements_2 DC.B  12



; stack frame
; define the position of each component of the stack
element_count equ 11
array_pointer equ 9
out_of_order  equ 8
correct_flag  equ 7
; return_address  equ 5
; tmp_storage_of_x  equ 3
; tmp_storage_of_a  equ 2
; tmp_storage_of_b  equ 1
prev_value    equ 0



; code section
            ORG   ROMStart


Entry:
_Startup:
            LDS   #RAMEnd+1       ; initialize the stack pointer

            CLI                     ; enable interrupts
mainLoop:
            ; pretend we were using X and A for something useful
            LDX #$ABCD
            LDAA  #$BA


            ; fill in the values on the stack to send to the function
            MOVB  number_of_elements_1, 1, -SP  ; one byte for the number of elements                           
            MOVW  #array_1, 2, -SP     ; two bytes for address of array       
            MOVW  #0, 2, -SP         ; one byte each for out of order number and correct count flag

            jsr test_if_sorted            
            
            leas 5, SP  ; deallocate the memory - basically move the SP 
                        ; to where it was before we called the function


            ; fill in the values on the stack to send to the function
            MOVB  number_of_elements_2, 1, -SP  ; one byte for the number of elements                           
            MOVW  #array_2, 2, -SP     ; two bytes for address of array       
            MOVW  #0, 2, -SP         ; one byte each for out of order number and correct count flag

            jsr test_if_sorted            
            
            leas 5, SP  ; deallocate the memory - basically move the SP 
                        ; to where it was before we called the function


            
            bra mainLoop
                                
            
test_if_sorted: 
            ; store the registers temporarily while we run the subroutine
            PSHX           
            PSHA
            PSHB
            
            ; allocate the local variable prev_value by allocating 1 byte on the stack
            movb  #0, 1, -SP
            
            ; now we are ready to work on the function. We can access the stack frame using:
            ;   prev_value -> ldaa prev_value, SP
            ;   array_pointer -> ldx array_pointer, SP
            ;   out_of_order -> ldx out_of_order, SP
            ;   correct_flag  -> ldaa correct_flag, SP
            ;   element_count -> ldaa element_count, SP
            
            
            ldx   array_pointer, SP
            ldaa  element_count, SP            
            
            ; store 0 as the previous value (assume that there are no negative numbers
            ldab  #0
            stab  prev_value, SP
            
test_loop:
            ldab  1, x+
            
            cmpb  prev_value, SP  ; tests b - memory address
            blt   failed_test     ; if b was less than the previous value, it is a fail
            
            stab  prev_value, SP
            
            deca
            bne test_loop
            bra finish_function
            
failed_test:
            ; do something when the thing fails
            staa out_of_order, SP
            ldaa element_count, SP            
            suba out_of_order, SP
            staa out_of_order, SP
            
            ldaa  #1
            staa correct_flag, SP
            
            
finish_function:
            ldab element_count, SP  ; load the element count into register A
            
            
                      
            ; clear the local variable, restore the stack pointer
            leas  1, SP
            
            ; restore the registers to their former values before we started using them            
            PULB
            PULA
            PULX
            rts
    

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
