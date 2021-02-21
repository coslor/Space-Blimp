; LOADBIN - loads an arbitrary PRG file into memory using the Kernal routines
;
; call signature:
;	byte loadbin(char* filename, byte fname_len, byte device, unsigned int address);
;
.include "zeropage.inc"
.include "cbm_kernal.inc"
.include "io.inc"

.import popa,popptr1
.export _loadbin,run_lfs,run_setnam,run_load

.debuginfo on

.macro print_string	string
				pha
				tya
				pha
				
				turn_basic_on
				
				lda #<string
				ldy #>string
				jsr STROUT
				
				turn_basic_off
				
				pla
				tay
				pla
.endmacro

.macro print_cr
				pha
				lda #13
				jsr CHROUT
				pla
.endmacro

.macro print_num num_ptr
				pha
				txa
				pha
				
				lda num_ptr
				ldx num_ptr + 1
				jsr LINPRT
				
				pla
				tax
				pla
.endmacro


.macro print_a 
				sta $ff
				
				pha
				txa
				pha
				
				lda $ff
				ldx #0
				jsr LINPRT
				
				pla
				tax
				pla
.endmacro

.macro turn_basic_on
				pha
				
				lda $01
				sta $fe
				ora #01
				sta $01

				pla
.endmacro

.macro turn_basic_off
				pha
				
				lda $fe
				sta $01
				
				pla
.endmacro
			
_loadbin:		
				; lda #$80				; turn on kernal error messages
				; jsr SETMSG
				
				sta address				; rightmost arg is in A/X
				stx address+1
				
				jsr popa
				sta device
				
				jsr popa
				sta fn_len
				
				jsr popptr1
				lda ptr1
				sta fn
				lda ptr1+1
				sta fn+1
				
				; ldy #3					; read 3rd arg [device] from stack, store it in var device
				; lda (sp),y
				; sta device
				
				; dey
				; lda (sp),y
				; sta fn_len
				
				; dey 					
				; lda (sp),y
				; sta fn+1
				
				; dey						
				; lda (sp),y
				; sta fn
								
set_name:
				lda fn_len
				ldx fn
				ldy fn+1
				clc
				
run_setnam:		jsr SETNAM
				
				; turn_basic_on

				; print_string msg1
				; print_string setnam_msg
				; print_a
				
				; jsr CRDO
				
				; turn_basic_off

				bcs exit


set_lfs:
				lda #2
				ldx device
				ldy #0
				clc
				
run_lfs:		jsr SETLFS
				
				;pha
				
				
				; turn_basic_on
				
				; print_string msg1
				; print_string setlfs_msg
				; print_a
				
				; jsr CRDO

				; turn_basic_off				
				
				bcs exit				; carry means error occurred. A contains error code.
				
do_load:				
				lda #0					; relocating load
				ldx address
				ldy address+1
run_load:		jsr LOAD
				bcs exit

				lda #0					; no error
				
exit:			
				ldx #0
				rts
				
 
fn:				.addr $0000
fn_len:			.byte $00
device:			.byte $00
address:		.addr $0000

msg1:			.asciiz "Status after "
setlfs_msg:		.asciiz "SETLFS: "
setnam_msg:		.asciiz "SETNAM: "
load_msg:		.asciiz "LOAD: "
carry_msg:		.asciiz " Carry="
on_msg:			.asciiz "ON"
off_msg: 		.asciiz "OFF"

