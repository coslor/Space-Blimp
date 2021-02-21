;
; utility routines
;
;
CLR_SCREEN = $e544

PLOTK = $e50a 					; read/set cursor row(x), col(y) 
SCROL = $e8ea 					; scroll the screen up 1 line 
DSPP = $ea31 					; read the screen & put char in A, color in X 
 
MOVE_UP = $a3bf 				; move a block of memory up, or move memory  
								;	from one non-overlapping region to another.
								;	$5f-$60=source block starting address
								;	$5a-5b=source block ending address +1
								;	$58-59=destination's ending address +1


INLIN = $a560 					; input a line from keyboard into text buffer at $200 
FCERR = $b248 					; print ILLEGAL QUANTITY error message

GARBA2=$b526		; do garbage collection

SCROL=$e8ea			; scrolls screen up 1 line
TXTPTR=$7a			; 2-byte pointere into BASIC text, used by CHRGET, etc.

;
; Stuff to parse the remainder of a command line and use the values there
;
; For example(from BASIC): SYS 12345,"filename",8,1924
;
CHKCOM = $aefd 					; checks for a comma, and moves the
								;	BASIC char pointer up by one.
						
CHKCHAR = $aeff 				; checks for any character, by setting A to the 
								;	desired character code. Prints syntax err
								;	message if not found

FRMEVAL = $ad9e 				; Eval the next expression on the command line.
								;	Set the appropriate vals of VALTYP & INTFLAG,
								;	then call this. Displays a ?SYNTAX ERROR if
								;	the expression is invalid. 
								;	Puts numeric results in FAC1, string info
								; 	in the following bytes:
								;		FAC1:length
								;		FAC1+1:<address
								;		FAC1+2:>address
								;

FRMNUM = $ad8a 					; Evals the next expression as floating point, 
								;	stores it into FAC1					
						
GETBYT = $b79e 					; Evals the next expression as as unsigned byte,						
								;	stores it in X.						
										
COMBYT = $b7f1 					; check for a comma, then call GETBYT										
ERROR = $a437 					; prints an error message, error number in X-register. 
 								;	uses vector in ($0300) to jump to $E38B. 												  

FINDLN = $a613 					; search for basic line number in $20-$21. if found,
								;	address of line in $5f-$60. C set if found, else clear.


;
;	I/O ROUTINES
;


IOINIT = $fda3 					;	Restore I/O							
CINT = $e518 					;	Restore screen 

 							 
;
;	I/O vectors
;
OUTVEC  = $0326 	 			; output vector
STOPVEC = $0328 				; check stop vector
LOADVEC = $0330 				; load vector
SAVEVEC = $0332 				; save vector
IOABORT = $032c					; vector to CLALL

;
;	other I/O routines
;




STATUS = $90 					; ST for serial devices.						
								;	For serial devices:						
								;		bit 0:timeout (write)
								;		bit 1:timeout (read)
								;		bit 6:EOF
								;		bit 7:device not present 						
																		
 
;
;	interrupt vectors
;
CVINV = $314 					; point to IRQ handler, normally $ea31.
								;	NOTE: A,X,Y are saved on the stack before calling,
								;		but they are NOT automatically restored
						
CBINV = $316 					; BRK interrupt handler. Normally $fe66.  
NMINV = $318 					; NMI handler, normally $fe47.  
								;	NOTE: to disable RS/RESTORE, store a 0 in $318.
												  						 

;
;	passing data between basic and ml
;


A_STORAGE = $30c 				; the registers are read from these 
X_STORAGE = $30d 		 		;		locations before running a SYS routine,
Y_STORAGE = $30e 		 		; 		and the results are stored back into 
P_STORAGE = $30f 		 		;		them after the RTS. doesn't apply to USR.

USERADD = $311 					; the 16-bit address of a USR routine can be 
								; 		put into this vector. for example:
								;			x=usr(17) 								
								;		...puts the value of 17 in FAC1, calls
								; 		the routine in $311-312, and assigns the
								;		value of FAC1 upon exiting, to the var x.
;
;	zero page locs used by basic
;
CHRGET = $73 					; reads the next character for processing by basic.
								;	sets P to indicate what kind of char,  
								; 	and returns the char in A. C=0-9,Z=end of stmt.
						
CHRGOT = $79 					; does the same thing, but doesn't increment the						
								;	char pointer.						
												
VERCK = $A 						; flag:0=LOAD,1=VERIFY												
VALTYP = $D 					; flag:$FF=string,0=numeric							
INTFLG = $E 					; flag:$80=int,0=fp												
INPFLG = $11 					; flag:0=INPUT,$40=GET,$98=READ												
CHANNL = $13 					; current logical file number (not dev#)												
TXTTAB = $2b 					; beginning of BASIC text, normally $801 
MEMSIZ = $37 					; end of BASIC-available memory 
CURLIN = $39 					; current BASIC line#. $ff in $40 means immediate mode 
VARPNT = $47 					; descriptor of current BASIC variable value 
OPMASK = $4D 					; comparison operation flag: 1=<,2=> 
DSCPNT = $50 					; $50-51 point to current string descriptor, 
								; 	$52 holds string length
						
STKEY = $91 					; value of the row of the keybd when last scanned. 												 
								;	$ff=none,$fe=1,$fd=<-,$fb=CTRL,$ef=SPACE,
								;	$df=Commodore,$bf=Q,$7f=STOP.
								;	NOTE: this means that you can do this:
								;		LDA STKEY
								;		BPL handle_stop
						
						
VERCK2 = $93 						; flag for load routine: 0=load/1=verify												
DFLTN = $99 					; current default input device
DFLTO = $9A 					; current default output device
TIME = $A0 						; software jiffy clock, from $a0-a2. 
								;	24-bit count of jiffies (60/sec) since start.
								;	resets every 24 hours.

FNLEN = $b7 					; size of current filename						
LA = $b8 						; current logical file number(for a different						
								;	purpose than $13)						
														
SA = $b9 						; current secondary address												
FA = $ba 						; current device number												
FNADR = $BB 					; 2-byte pointer to filename												
LSTX = $c5 						; matrix coordinate of *last* keypress; 64=none												
BUFPTR = $c6 					; # of characters in keyboard buffer												
RVS = $c7 						; flag: print reverse characters? 0=no												
								;	NOTE: you can poke 0 here to cancel reverse mode												
																				
SFDX = $cb 						; matrix coords of *current* keypress; 64=none
BLNSW = $cc 					; cursor blink enable:0=flash
GDBLN = $ce 					; screen code of char under cursor
PNTR = $d3 						; cursor column on current line
QTSW = $d4 						; editor in quote mode? 0=no
TBLx = $d6 						; current cursor physical line # (starts with 0)
INSRT = $d8 					; insert mode? >0 is # of inserts
USER = $f3 						; 2-byte pointer to current screen color location

;	used by tape routines
TSERVO = $92 		
TEOB = $96 		
TEMPXY = $97 		
TPARIT = $9b 		
TBYTFL = $9c 		
HDRTYP = $9e 		
PTR1 = $9e 		
PTR2 = $9f 		
TSFCNT = $a3 		
TBTCNT = $a4 		
CNTDN = $A5 		
BUFPNT = $a6 		
PASNUM = $a7 		
RIDATA = $aa 		
TCKS = $ab 		
CMP00 = $b0 		
CMPB01 = $b1 		
TAPE10 = $b2 		
TAPE11 = $b3 		
;	used by rs-232
RIBUF0 = $f7 		
RIBUF1 = $f8 		
ROBUF0 = $f9 		
ROBUF1 = $fa 		
;	unused
MISC1 = $2 		
MISC_PTR1 = $fd 		

;
; misc locations of note
;
KEYBD_BUFR = $277 				; keyboard buffer, from $277-$280 (10 bytes)						

COLOR = $286 					; current foreground color for text
GDCOL = $287 					; color of character under cursor
HIBASE = $288 					; page of screen memory; normally contains 4(*256=1024)
								;	NOTE: $d018/$dd00 change ths *display*
								;	screen location - the one that shown onscreen.
								; 	this one is the memory written into by CHROUT,etc.
						
XMAX = $289 					; max keyvoard buffer size
								; 	should be <=10						
														
RPTFLAG = $28a 					; flag: which keys should repeat?						
								;	0=normal,$80=all,$40=none						
												
SHFLAG = $653 					; flag: modifier keys currently pressed?											
								;	bits: 1=SHIFT,2=Commodore,4=CTRL											
																	
MODE = $291 					; flag: enable changing char sets with SHIFT/C= ?																	
								;	$80=disabled, 0=enabled																	
																							
AUTODN = $292 					; flag: scroll screen on col 40/last line?																							
								;	0=yes; otherwise=no																							
																													
BUF = $200 						; BASIC line editor input buffer 
 
 												

;			
; keyboard constants			
;			
SHIFT_KEYS=$028d
KEY_SHIFT=%00000001
KEY_COMM=%000000010
KEY_CTRL=%00000100

;
;	zero page locations
;


;
;	 NOTE: ***DO NOT*** use this pointer ($FB/FC) in interrupt code, unless you 
;			cache the original value at the start of the IRQ routine and restore 
;			it upon exit. It is used continually to print strings, and if
;			scrambled in the middle of printing a string, unpredictable effects
;			will occur! If possible, don't use it at all ouside of 
;			print routines.
;
P_PTR = $fb 		


;
; 	I/O Registers
;

; SCREEN_REG1= $d011	; bits 0-2:vertical raster roll
							; bit 3: screen height (24/25 rows)
							; bit 4: screen off/on
							; bit 5: text/bitmap screen
							; bit 6: extended background mode
							; bit 7: 	read: current raster line
							;			write: line to generate IRQ at
					
;SCREEN_CTRL = $d016 			; 	bits 0-2:horiz raster scroll	
							;	bit 3: screen width - 38/40 cols	
							;	bit 4: multicolor mode	
						
MEM_SETUP = $d018 			;	bits 1-3: in text mode, pointer to
							;		character memory
							; 	bits 4-7: pointer to screen memory
					
SPRITE_PRI = $d01b 		 	;	bits determine whether sprite x drawn  
							;		in front of/behind background
					
										


SCREEN_RAM = $400
COLOR_RAM = $d800

PETSCII_COLR_TBL = $E8D1 		 ;PETASCII Color Code Equivalent Table

STACK = $100

PROCESSOR_DDR = $0 			; bits 0-7: set read/write for bit x 
							;	of processor port					
										
PROCESSOR_PORT = $1 			; 	bit 0: RAM/ROM at $a000-bfff										
							;	bit 1: RAM/ROM at $e000-ffff										
							;	bit 2: RAM/IO ports at $d000-dfff										
							;	bits 3-5: datasette										


