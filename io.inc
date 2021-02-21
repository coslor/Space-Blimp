;
; Input / Output 
;

OUTDO=$AB47					; print the char in A

ERASE_LINE = $e9ff 			; IN: a=screen line to erase

STROUT = $ab1e 				; print zt string,addr in A/Y
LINPRT = $BDCD 				; print UNSIGNED int in A/X 

PRTSPC = $ab4d 				; print a space character
CRDO = $aad7 				; print a CR character, followed by LF
							;	if channel > 128

SCRNOUT =$e716 				;chrout for screen
NORMOUT =$f1ca 				;chrout vector
GETKBC=$e5b4				; get next char from keyboard queue, put it in A
PRT=$e716					; prints char in A, handling clr screen, del, color codes
DSPP=$ea13					; put char in A to current cursor pos. No checking of special codes.


 STATUS = $90				; ST for serial devices.						
							;	For serial devices:						
							;		bit 0:timeout (write)
							;		bit 1:timeout (read)
							;		bit 6:EOF
							;		bit 7:device not present 		
					

;
; The Kernal routines are included in another file. The below stuff is for ready
;	documentation only
;

					
; CHROUT = $FFD2			; write byte to default output
; CHRIN = $FFCF				; read byte from default input(uses=A,Y)
							;	when called from the keyboard, reads an entire line
							;	into a buffer at $200, then returns 1 char at a time,
							;	each time CHRIN is called, until the buffer is
							;	exhausted, at which point another line will be read
							;	from the screen.
							;	IN - A=character read
								
; SETMSG = $FF90			; turn on/off Kernal error,status messages
; SETLFS = $FFBA			; set logical file numbers (open a,x,y)
; SETNAM = $FFBD			; set file name(a=len,x/y=lo/hi for pointer)
; OPEN = $FFC0				; open file (out:c=err, a=1,2,4,5,8 error code, uses=AXY)
; CLOSE = $FFC3				; close file (a=fileno,uses=AXY)
; CHKIN = $FFC6				; set file as default input(a=filenumber,C=error,uses=AX)
; CHKOUT = $FFC9			; set file as default output(a=filenumber,C=error,uses=AX)
; CLRCHN = $FFCC			; close default input/output files(uses=AX)

;LOAD = $FFD5				; Load or verify file. (Must call SETLFS and SETNAM beforehand)
							;	IN: A: 0 = Load, 1-255 = Verify; 
							;	X/Y = Load address (if secondary address = 0)
							;	OUT:C: 1 = Error; A = KERNAL error code (if Carry = 1)
							;		X/Y = Address of last byte loaded/verified (if Carry = 0)
								
;SAVE = $FFD8				; Save file. (Must call SETLFS and SETNAM beforehand
							;	IN:	A = Address of ZP register holding start address to save
							;		X/Y = End address plus 1
							;	OUT: C:1=Error
								
;GETIN = $FFE4				; Read byte from default input (uses=AXY)
							;	when called for the keyboard, return the next character
							;	in the keyboard buffer at $631. depends on the
							;	IRQ routine to read the physical keyboard and fill 
							;	the keyboard buffer.
								  
;CLALL = $FFE7				; clear file table & call CLRCHN(uses=AX)
;READST = $ffb7				; read STatus, leaves it in A
;STOP = $ffe1				; check for STOP key. If pressed, 
							; 	set Z (BEQ), call CLRCHN, print "break".(uses=AX)

;VECTOR = $ff8d				; Copy vector table at memory addresses 
							;	$0314-$0333 from or into user table.			
							;	Inputs: 
							;		C=0: Copy user table into vector table
							;		C=1: Copy vector table into user table
							;		X/Y: Pointer to user table.			

;RESTOR = $ff8a				; Fill vector table at memory addresses 
							;		$0314-$0333 with default values
								

;PLOT = $fff0				; Save or restore cursor position
							; 	Inputs:
							;		C=0,X/Y=set cursor column,row
							;		C=1 output current cursor position
							;	Outputs:
							;		X,Y=current cursor row,col (if C=1)					
							
;
; misc
;
RESTORE_VECS = $fd15		; RESTOR calls RESTOR_VECS by default								
