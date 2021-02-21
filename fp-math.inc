STROUT=$ab1e		; print string beginning in A/Y, terminated by zero
PRTSPC=$ab3f		; print a space
OUTDO=$AB47			; print the char in A
GIVAYF=$b391		; convert 2-byte int in Y/A to FP in FAC1
SNGET=$b3a2			; convert 1-byte int in Y to FP in FAC1
GARBA2=$b526		; do garbage collection
FSUBT=$b853			; FAC1=FAC2-FAC1
FADDT=$b86f			; FAC1+=FAC2
COMPLT=$b947		; FAC1=twos_complement(FAC1)
FMULTT=$ba30		; FAC1*=FAC2
FDIVT=$b814			; FAC1=FAC2/FAC1
MOVFA=$bbfc			; FAC1=FAC2
ROUND=$bc1b			; FAC1=ROUND(FAC1)
SIGN=$bc2b			; A=-1(FF)/0/1
ABS=$bc58			; FAC1=ABS(FAC1)
INT=$bccc			; FAC1=INT(FAC1)
FIN=$bcf3			; TXTPTR=ASCII string, then jsr GETCHR/jsr FIN puts val in FAC1
AADD=$bd7e			; FAC1+=A
FOUT=$bddd			; print FAC1 to ZT ASCII string starting at $100
FOUTIM=$be68		; call FOUT on TI
SQR=$BF71			; FAC1=SQR(FAC1)
EXP=$bfed			; FAC1=e^FAC1
RND=$e097			; FAC1=RND(FAC1). See BASICs RND function to see what rnd(FAC1) does when FAC1<=0
COS=$e264			; FAC1=COS(FAC1)
SIN=$e26b			; FAC1=SIN(FAC1)
TAN=$e2b4			; FAC1=TAN(FAC1)
ATN=$e30b			; FAC1=ARCTAN(FAC1)