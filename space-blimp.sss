ca65 V2.19 - Git 43881af
Main file   : loadbin.asm
Current file: loadbin.asm

000000r 1               ; LOADBIN - loads an arbitrary PRG file into memory using the Kernal routines
000000r 1               ;
000000r 1               ; call signature:
000000r 1               ;	byte loadbin(char* filename, byte fname_len, byte device, unsigned int address);
000000r 1               ;
000000r 1               .include "zeropage.inc"
000000r 2               ;
000000r 2               ; zeropage.inc
000000r 2               ;
000000r 2               ; (C) Copyright 2002-2012, Ullrich von Bassewitz (uz@cc65.org)
000000r 2               ;
000000r 2               
000000r 2               ; Assembler include file that imports the runtime zero page locations used
000000r 2               ; by the compiler, ready for usage in asm code.
000000r 2               
000000r 2               
000000r 2                       .globalzp       sp, sreg, regsave
000000r 2                       .globalzp       ptr1, ptr2, ptr3, ptr4
000000r 2                       .globalzp       tmp1, tmp2, tmp3, tmp4
000000r 2                       .globalzp       regbank
000000r 2               
000000r 2               ; The size of the register bank
000000r 2               regbanksize     = 6
000000r 2               
000000r 2               ; The total amount of zero page space used
000000r 2               zpspace         = 26
000000r 2               
000000r 2               ; The amount of space that needs to be saved by an interrupt handler that
000000r 2               ; calls C code (does not include the register bank, which is saved by the
000000r 2               ; generated C code if required).
000000r 2               zpsavespace     = zpspace - regbanksize
000000r 2               
000000r 2               
000000r 1               .include "cbm_kernal.inc"
000000r 2               ;
000000r 2               ; Olli Savia <ops@iki.fi>
000000r 2               ; Greg King
000000r 2               ;
000000r 2               ; Commodore-compatibles Kernal functions
000000r 2               ;
000000r 2               
000000r 2               .if .def(__CX16__)
000000r 2                 ; CX16 extended jump table
000000r 2                 ENTROPY_GET                   := $FECF
000000r 2                 KEYBRD_BUF_PUT                := $FED2
000000r 2                 CONSOLE_SET_PAGE_MSG          := $FED5
000000r 2                 CONSOLE_PUT_IMAGE             := $FED8
000000r 2                 CONSOLE_INIT                  := $FEDB
000000r 2                 CONSOLE_PUT_CHAR              := $FEDE
000000r 2                 CONSOLE_GET_CHAR              := $FEE1
000000r 2                 MEMORY_FILL                   := $FEE4
000000r 2                 MEMORY_COPY                   := $FEE7
000000r 2                 MEMORY_CRC                    := $FEEA
000000r 2                 MEMORY_DECOMPRESS             := $FEED
000000r 2                 SPRITE_SET_IMAGE              := $FEF0
000000r 2                 SPRITE_SET_POSITION           := $FEF3
000000r 2                 FB_INIT                       := $FEF6
000000r 2                 FB_GET_INFO                   := $FEF9
000000r 2                 FB_SET_PALETTE                := $FEFC
000000r 2                 FB_CURSOR_POSITION            := $FEFF
000000r 2                 FB_CURSOR_NEXT_LINE           := $FF02
000000r 2                 FB_GET_PIXEL                  := $FF05
000000r 2                 FB_GET_PIXELS                 := $FF08
000000r 2                 FB_SET_PIXEL                  := $FF0B
000000r 2                 FB_SET_PIXELS                 := $FF0E
000000r 2                 FB_SET_8_PIXELS               := $FF11
000000r 2                 FB_SET_8_PIXELS_OPAQUE        := $FF14
000000r 2                 FB_FILL_PIXELS                := $FF17
000000r 2                 FB_FILTER_PIXELS              := $FF1A
000000r 2                 FB_MOVE_PIXELS                := $FF1D
000000r 2                 GRAPH_INIT                    := $FF20
000000r 2                 GRAPH_CLEAR                   := $FF23
000000r 2                 GRAPH_SET_WINDOW              := $FF26
000000r 2                 GRAPH_SET_COLORS              := $FF29
000000r 2                 GRAPH_DRAW_LINE               := $FF2C
000000r 2                 GRAPH_DRAW_RECT               := $FF2F
000000r 2                 GRAPH_MOVE_RECT               := $FF32
000000r 2                 GRAPH_DRAW_OVAL               := $FF35
000000r 2                 GRAPH_DRAW_IMAGE              := $FF38
000000r 2                 GRAPH_SET_FONT                := $FF3B
000000r 2                 GRAPH_GET_CHAR_SIZE           := $FF3E
000000r 2                 GRAPH_PUT_CHAR                := $FF41
000000r 2                 MULTI_ACPTR                   := $FF44
000000r 2                 RESTORE_BASIC                 := $FF47
000000r 2                 CLOCK_SET_DATE_TIME           := $FF4D
000000r 2                 CLOCK_GET_DATE_TIME           := $FF50
000000r 2                 JOYSTICK_SCAN                 := $FF53
000000r 2                 JOYSTICK_GET                  := $FF56
000000r 2                 SCREEN_SET_MODE               := $FF5F
000000r 2                 SCREEN_SET_CHARSET            := $FF62
000000r 2                 MOUSE_CONFIG                  := $FF68
000000r 2                 MOUSE_GET                     := $FF6B
000000r 2               .endif
000000r 2               
000000r 2               .if .def(__C128__)
000000r 2                 ; C128 extended jump table
000000r 2                 C64MODE      := $FF4D
000000r 2                 SWAPPER      := $FF5F
000000r 2                 SETBNK       := $FF68
000000r 2               .endif
000000r 2               
000000r 2               .if .def(__C128__) || .def(__CX16__)
000000r 2                 ; Extended jump table
000000r 2                 CLSALL       := $FF4A
000000r 2                 LKUPLA       := $FF59
000000r 2                 LKUPSA       := $FF5C
000000r 2                 PFKEY        := $FF65
000000r 2                 JSRFAR       := $FF6E
000000r 2                 INDFET       := $FF74
000000r 2                 INDSTA       := $FF77
000000r 2                 INDCMP       := $FF7A
000000r 2                 PRIMM        := $FF7D
000000r 2               .endif
000000r 2               
000000r 2               .if .def(__C64__) || .def(__C128__) || .def(__C16__) || .def(__CX16__)
000000r 2                 CINT         := $FF81
000000r 2                 IOINIT       := $FF84
000000r 2                 RAMTAS       := $FF87
000000r 2               .elseif .def(__VIC20__)
000000r 2                 CINT         := $E518         ; No entries are in the Kernal jump table of the VIC-20 for these three (3) functions.
000000r 2                 IOINIT       := $FDF9         ; The entries for these functions have been set to point directly to the functions
000000r 2                 RAMTAS       := $FD8D         ; in the Kernal, to maintain compatibility with the other Commodore platforms.
000000r 2               .elseif .def(__CBM510__) || .def(__CBM610__)
000000r 2                 IOINIT       := $FF7B
000000r 2                 CINT         := $FF7E
000000r 2               .endif
000000r 2               
000000r 2               .if .def(__VIC20__) || .def(__C64__) || .def(__C128__) || .def(__C16__) || .def(__CX16__)
000000r 2                 RESTOR       := $FF8A
000000r 2                 VECTOR       := $FF8D
000000r 2               .elseif .def(__CBM510__) || .def(__CBM610__)
000000r 2                 VECTOR       := $FF84
000000r 2                 RESTOR       := $FF87
000000r 2               .endif
000000r 2               
000000r 2               .if .def(__CBM510__) || .def(__CBM610__) || .def(__VIC20__) || .def(__C64__) || .def(__C128__) || .def(__C16__) || .def(__CX16__)
000000r 2                 SETMSG       := $FF90
000000r 2                 SECOND       := $FF93
000000r 2                 TKSA         := $FF96
000000r 2                 MEMTOP       := $FF99
000000r 2                 MEMBOT       := $FF9C
000000r 2                 SCNKEY       := $FF9F
000000r 2                 SETTMO       := $FFA2
000000r 2                 ACPTR        := $FFA5
000000r 2                 CIOUT        := $FFA8
000000r 2                 UNTLK        := $FFAB
000000r 2                 UNLSN        := $FFAE
000000r 2                 LISTEN       := $FFB1
000000r 2                 TALK         := $FFB4
000000r 2                 READST       := $FFB7
000000r 2                 SETLFS       := $FFBA
000000r 2                 SETNAM       := $FFBD
000000r 2                 OPEN         := $FFC0
000000r 2                 CLOSE        := $FFC3
000000r 2               .endif
000000r 2               
000000r 2               ; Available on all platforms including PET
000000r 2               CHKIN          := $FFC6
000000r 2               CKOUT          := $FFC9
000000r 2               CHKOUT         := $FFC9
000000r 2               CLRCH          := $FFCC
000000r 2               CLRCHN         := $FFCC
000000r 2               BASIN          := $FFCF
000000r 2               CHRIN          := $FFCF
000000r 2               BSOUT          := $FFD2
000000r 2               CHROUT         := $FFD2
000000r 2               
000000r 2               .if .def(__CBM510__) || .def(__CBM610__) || .def(__VIC20__) || .def(__C64__) || .def(__C128__) || .def(__C16__) || .def(__CX16__)
000000r 2                 LOAD         := $FFD5
000000r 2                 SAVE         := $FFD8
000000r 2                 SETTIM       := $FFDB
000000r 2                 RDTIM        := $FFDE
000000r 2               .endif
000000r 2               
000000r 2               ; Available on all platforms including PET
000000r 2               STOP           := $FFE1
000000r 2               GETIN          := $FFE4
000000r 2               CLALL          := $FFE7
000000r 2               UDTIM          := $FFEA
000000r 2               
000000r 2               .if .def(__CBM510__) || .def(__CBM610__) || .def(__VIC20__) || .def(__C64__) || .def(__C128__) || .def(__C16__) || .def(__CX16__)
000000r 2                 SCREEN       := $FFED
000000r 2                 PLOT         := $FFF0
000000r 2                 IOBASE       := $FFF3
000000r 2               .endif
000000r 2               
000000r 2               ; ---------------------------------------------------------------------------
000000r 2               ; Kernal routines, direct entries
000000r 2               ;
000000r 2               ; Unlike the above, these are not standard functions with entries in the jump
000000r 2               ; table. They do not exist in all Kernals, and where they do the entry point is
000000r 2               ; specific to that particular machine and possibly even Kernal version.
000000r 2               ;
000000r 2               ; This list is not comprehensive: missing items for particular machines
000000r 2               ; should be added as needed.
000000r 2               ;
000000r 2               ; UPDCRAMPTR: Updates the color RAM pointer to match the screen RAM pointer.
000000r 2               ;
000000r 2               
000000r 2               .if .def(__VIC20__)
000000r 2                 CLRSCR       := $E55F
000000r 2                 KBDREAD      := $E5CF
000000r 2                 UPDCRAMPTR   := $EAB2
000000r 2               .elseif .def(__C64__)
000000r 2                 CLRSCR       := $E544
000000r 2                 KBDREAD      := $E5B4
000000r 2                 NMIEXIT      := $FEBC
000000r 2                 UPDCRAMPTR   := $EA24
000000r 2               .elseif .def(__C128__)
000000r 2                 CLRSCR       := $C142
000000r 2                 KBDREAD      := $C006
000000r 2                 NMIEXIT      := $FF33
000000r 2                 NEWLINE      := $C363
000000r 2                 PRINT        := $C322
000000r 2                 CURS_SET     := $CD57
000000r 2                 CURS_ON      := $CD6F
000000r 2                 CURS_OFF     := $CD9F
000000r 2               .elseif .def(__C16__)
000000r 2                 CLRSCR       := $D88B
000000r 2                 KBDREAD      := $D8C1
000000r 2               .endif
000000r 2               
000000r 1               .include "io.inc"
000000r 2               ;
000000r 2               ; Input / Output
000000r 2               ;
000000r 2               
000000r 2               OUTDO=$AB47					; print the char in A
000000r 2               
000000r 2               ERASE_LINE = $e9ff 			; IN: a=screen line to erase
000000r 2               
000000r 2               STROUT = $ab1e 				; print zt string,addr in A/Y
000000r 2               LINPRT = $BDCD 				; print UNSIGNED int in A/X
000000r 2               
000000r 2               PRTSPC = $ab4d 				; print a space character
000000r 2               CRDO = $aad7 				; print a CR character, followed by LF
000000r 2               							;	if channel > 128
000000r 2               
000000r 2               SCRNOUT =$e716 				;chrout for screen
000000r 2               NORMOUT =$f1ca 				;chrout vector
000000r 2               GETKBC=$e5b4				; get next char from keyboard queue, put it in A
000000r 2               PRT=$e716					; prints char in A, handling clr screen, del, color codes
000000r 2               DSPP=$ea13					; put char in A to current cursor pos. No checking of special codes.
000000r 2               
000000r 2               
000000r 2                STATUS = $90				; ST for serial devices.
000000r 2               							;	For serial devices:
000000r 2               							;		bit 0:timeout (write)
000000r 2               							;		bit 1:timeout (read)
000000r 2               							;		bit 6:EOF
000000r 2               							;		bit 7:device not present
000000r 2               
000000r 2               
000000r 2               ;
000000r 2               ; The Kernal routines are included in another file. The below stuff is for ready
000000r 2               ;	documentation only
000000r 2               ;
000000r 2               
000000r 2               
000000r 2               ; CHROUT = $FFD2			; write byte to default output
000000r 2               ; CHRIN = $FFCF				; read byte from default input(uses=A,Y)
000000r 2               							;	when called from the keyboard, reads an entire line
000000r 2               							;	into a buffer at $200, then returns 1 char at a time,
000000r 2               							;	each time CHRIN is called, until the buffer is
000000r 2               							;	exhausted, at which point another line will be read
000000r 2               							;	from the screen.
000000r 2               							;	IN - A=character read
000000r 2               
000000r 2               ; SETMSG = $FF90			; turn on/off Kernal error,status messages
000000r 2               ; SETLFS = $FFBA			; set logical file numbers (open a,x,y)
000000r 2               ; SETNAM = $FFBD			; set file name(a=len,x/y=lo/hi for pointer)
000000r 2               ; OPEN = $FFC0				; open file (out:c=err, a=1,2,4,5,8 error code, uses=AXY)
000000r 2               ; CLOSE = $FFC3				; close file (a=fileno,uses=AXY)
000000r 2               ; CHKIN = $FFC6				; set file as default input(a=filenumber,C=error,uses=AX)
000000r 2               ; CHKOUT = $FFC9			; set file as default output(a=filenumber,C=error,uses=AX)
000000r 2               ; CLRCHN = $FFCC			; close default input/output files(uses=AX)
000000r 2               
000000r 2               ;LOAD = $FFD5				; Load or verify file. (Must call SETLFS and SETNAM beforehand)
000000r 2               							;	IN: A: 0 = Load, 1-255 = Verify;
000000r 2               							;	X/Y = Load address (if secondary address = 0)
000000r 2               							;	OUT:C: 1 = Error; A = KERNAL error code (if Carry = 1)
000000r 2               							;		X/Y = Address of last byte loaded/verified (if Carry = 0)
000000r 2               
000000r 2               ;SAVE = $FFD8				; Save file. (Must call SETLFS and SETNAM beforehand
000000r 2               							;	IN:	A = Address of ZP register holding start address to save
000000r 2               							;		X/Y = End address plus 1
000000r 2               							;	OUT: C:1=Error
000000r 2               
000000r 2               ;GETIN = $FFE4				; Read byte from default input (uses=AXY)
000000r 2               							;	when called for the keyboard, return the next character
000000r 2               							;	in the keyboard buffer at $631. depends on the
000000r 2               							;	IRQ routine to read the physical keyboard and fill
000000r 2               							;	the keyboard buffer.
000000r 2               
000000r 2               ;CLALL = $FFE7				; clear file table & call CLRCHN(uses=AX)
000000r 2               ;READST = $ffb7				; read STatus, leaves it in A
000000r 2               ;STOP = $ffe1				; check for STOP key. If pressed,
000000r 2               							; 	set Z (BEQ), call CLRCHN, print "break".(uses=AX)
000000r 2               
000000r 2               ;VECTOR = $ff8d				; Copy vector table at memory addresses
000000r 2               							;	$0314-$0333 from or into user table.
000000r 2               							;	Inputs:
000000r 2               							;		C=0: Copy user table into vector table
000000r 2               							;		C=1: Copy vector table into user table
000000r 2               							;		X/Y: Pointer to user table.
000000r 2               
000000r 2               ;RESTOR = $ff8a				; Fill vector table at memory addresses
000000r 2               							;		$0314-$0333 with default values
000000r 2               
000000r 2               
000000r 2               ;PLOT = $fff0				; Save or restore cursor position
000000r 2               							; 	Inputs:
000000r 2               							;		C=0,X/Y=set cursor column,row
000000r 2               							;		C=1 output current cursor position
000000r 2               							;	Outputs:
000000r 2               							;		X,Y=current cursor row,col (if C=1)
000000r 2               
000000r 2               ;
000000r 2               ; misc
000000r 2               ;
000000r 2               RESTORE_VECS = $fd15		; RESTOR calls RESTOR_VECS by default
000000r 2               
000000r 1               
000000r 1               .import popa,popptr1
000000r 1               .export _loadbin,run_lfs,run_setnam,run_load
000000r 1               
000000r 1               .debuginfo on
000000r 1               
000000r 1               .macro print_string	string
000000r 1               				pha
000000r 1               				tya
000000r 1               				pha
000000r 1               
000000r 1               				turn_basic_on
000000r 1               
000000r 1               				lda #<string
000000r 1               				ldy #>string
000000r 1               				jsr STROUT
000000r 1               
000000r 1               				turn_basic_off
000000r 1               
000000r 1               				pla
000000r 1               				tay
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               .macro print_cr
000000r 1               				pha
000000r 1               				lda #13
000000r 1               				jsr CHROUT
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               .macro print_num num_ptr
000000r 1               				pha
000000r 1               				txa
000000r 1               				pha
000000r 1               
000000r 1               				lda num_ptr
000000r 1               				ldx num_ptr + 1
000000r 1               				jsr LINPRT
000000r 1               
000000r 1               				pla
000000r 1               				tax
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               
000000r 1               .macro print_a
000000r 1               				sta $ff
000000r 1               
000000r 1               				pha
000000r 1               				txa
000000r 1               				pha
000000r 1               
000000r 1               				lda $ff
000000r 1               				ldx #0
000000r 1               				jsr LINPRT
000000r 1               
000000r 1               				pla
000000r 1               				tax
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               .macro turn_basic_on
000000r 1               				pha
000000r 1               
000000r 1               				lda $01
000000r 1               				sta $fe
000000r 1               				ora #01
000000r 1               				sta $01
000000r 1               
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               .macro turn_basic_off
000000r 1               				pha
000000r 1               
000000r 1               				lda $fe
000000r 1               				sta $01
000000r 1               
000000r 1               				pla
000000r 1               .endmacro
000000r 1               
000000r 1               _loadbin:
000000r 1               				; lda #$80				; turn on kernal error messages
000000r 1               				; jsr SETMSG
000000r 1               
000000r 1  8D rr rr     				sta address				; rightmost arg is in A/X
000003r 1  8E rr rr     				stx address+1
000006r 1               
000006r 1  20 rr rr     				jsr popa
000009r 1  8D rr rr     				sta device
00000Cr 1               
00000Cr 1  20 rr rr     				jsr popa
00000Fr 1  8D rr rr     				sta fn_len
000012r 1               
000012r 1  20 rr rr     				jsr popptr1
000015r 1  A5 rr        				lda ptr1
000017r 1  8D rr rr     				sta fn
00001Ar 1  A5 rr        				lda ptr1+1
00001Cr 1  8D rr rr     				sta fn+1
00001Fr 1               
00001Fr 1               				; ldy #3					; read 3rd arg [device] from stack, store it in var device
00001Fr 1               				; lda (sp),y
00001Fr 1               				; sta device
00001Fr 1               
00001Fr 1               				; dey
00001Fr 1               				; lda (sp),y
00001Fr 1               				; sta fn_len
00001Fr 1               
00001Fr 1               				; dey
00001Fr 1               				; lda (sp),y
00001Fr 1               				; sta fn+1
00001Fr 1               
00001Fr 1               				; dey
00001Fr 1               				; lda (sp),y
00001Fr 1               				; sta fn
00001Fr 1               
00001Fr 1               set_name:
00001Fr 1  AD rr rr     				lda fn_len
000022r 1  AE rr rr     				ldx fn
000025r 1  AC rr rr     				ldy fn+1
000028r 1  18           				clc
000029r 1               
000029r 1  20 BD FF     run_setnam:		jsr SETNAM
00002Cr 1               
00002Cr 1               				; turn_basic_on
00002Cr 1               
00002Cr 1               				; print_string msg1
00002Cr 1               				; print_string setnam_msg
00002Cr 1               				; print_a
00002Cr 1               
00002Cr 1               				; jsr CRDO
00002Cr 1               
00002Cr 1               				; turn_basic_off
00002Cr 1               
00002Cr 1  B0 1C        				bcs exit
00002Er 1               
00002Er 1               
00002Er 1               set_lfs:
00002Er 1  A9 02        				lda #2
000030r 1  AE rr rr     				ldx device
000033r 1  A0 00        				ldy #0
000035r 1  18           				clc
000036r 1               
000036r 1  20 BA FF     run_lfs:		jsr SETLFS
000039r 1               
000039r 1               				;pha
000039r 1               
000039r 1               
000039r 1               				; turn_basic_on
000039r 1               
000039r 1               				; print_string msg1
000039r 1               				; print_string setlfs_msg
000039r 1               				; print_a
000039r 1               
000039r 1               				; jsr CRDO
000039r 1               
000039r 1               				; turn_basic_off
000039r 1               
000039r 1  B0 0F        				bcs exit				; carry means error occurred. A contains error code.
00003Br 1               
00003Br 1               do_load:
00003Br 1  A9 00        				lda #0					; relocating load
00003Dr 1  AE rr rr     				ldx address
000040r 1  AC rr rr     				ldy address+1
000043r 1  20 D5 FF     run_load:		jsr LOAD
000046r 1  B0 02        				bcs exit
000048r 1               
000048r 1  A9 00        				lda #0					; no error
00004Ar 1               
00004Ar 1               exit:
00004Ar 1  A2 00        				ldx #0
00004Cr 1  60           				rts
00004Dr 1               
00004Dr 1               
00004Dr 1  00 00        fn:				.addr $0000
00004Fr 1  00           fn_len:			.byte $00
000050r 1  00           device:			.byte $00
000051r 1  00 00        address:		.addr $0000
000053r 1               
000053r 1  D3 54 41 54  msg1:			.asciiz "Status after "
000057r 1  55 53 20 41  
00005Br 1  46 54 45 52  
000061r 1  D3 C5 D4 CC  setlfs_msg:		.asciiz "SETLFS: "
000065r 1  C6 D3 3A 20  
000069r 1  00           
00006Ar 1  D3 C5 D4 CE  setnam_msg:		.asciiz "SETNAM: "
00006Er 1  C1 CD 3A 20  
000072r 1  00           
000073r 1  CC CF C1 C4  load_msg:		.asciiz "LOAD: "
000077r 1  3A 20 00     
00007Ar 1  20 C3 41 52  carry_msg:		.asciiz " Carry="
00007Er 1  52 59 3D 00  
000082r 1  CF CE 00     on_msg:			.asciiz "ON"
000085r 1  CF C6 C6 00  off_msg: 		.asciiz "OFF"
000089r 1               
000089r 1               
