;
; annotated memory map
;

;
; zero page
;

D6510 = $0000					;(0) - 6510 On-chip Data Direction Register.
R6510 = $0001					;(1) - 6510 On-chip 8-bit Input/Output Register.
TEMP = $0002					;(2) - Unused. Free for user programs.
ADRAY1 = $0003-					;(3) - Jump Vector: Convert FAC to Integer in (A/Y)($B1AA).
ADRAY2 = $0005					;(5) - Jump Vector: Convert Integer in (A/Y) to Floating point in (FAC); ($B391).
CHARAC = $0007					;(7) - Search Character/Temporary Integer during INT.
ENDCHR = $0008					;(8) - Flag: Scan for Quote at end of String.
INTEGR = $0007					;(7) - Temporary Integer during OR/AND.
TRMPOS = $0009					;(9) - Screen Column for last TAB.
VERCK = $000A					;(10) - Flag: 0 = Load, 1 = Verify.
COUNT = $000B					;(11) - Input Buffer Pointer/Number of Subscripts.
DIMFLG = $000C					;(12) - Flag: Default Array dimension.
VALTYP = $000D					;(13) - Data type Flag: $00 = Numeric, $FF = String.
INTFLG = $000E					;(14) - Data type Flag: $00 = Floating point, $80 =Integer.
GARBFL = $000F					;(15) - Flag: DATA scan/List Quote/Garbage collection.
SUBFLG = $0010					;(16) - Flag: Subscript reference/User Function call.
INPFLG = $0011					;(17) - Input Flag: $00 = INPUT, $40 = GET, $98 = READ.
TANSGN = $0012					;(18) - Flag: TAN sign/Comparative result.
CHANNL = $0013					;(19) - File number of current Input Device.
LINNUM = $0014					;(20) - Temporary: Integer value.
TEMPPT = $0016					;(22) - Pointer: Temporary String Stack.
LASTPT = $0017					;(23) - Last temporary String Address.
TEMPST = $0019					;(25) - Stack for temporary Strings.
INDEX = $0022					;(34) - Utility Pointer Area.
INDEX1 = $0022					;(34) - First Utility Pointer.
INDEX2 = $0024					;(36) - Secong Utility Pointer.
RESHO = $0026					;(38) - Floating point product of Multiply andDivide.
TXTTAB = $002B					;(43) - Pointer: Start of BASIC Text Area ($0801).
VARTAB = $002D					;(45) - Pointer: Start of BASIC Variables.
ARYTAB = $002F					;(47) - Pointer: Start of BASIC Arrays.
STREND = $0031					;(49) - Pointer: End of BASIC Arrays + 1.
FRETOP = $0033					;(51) - Pointer: Bottom of String space.
FRESPC = $0035					;(53) - Utility String Pointer.
MEMSIZ = $0037					;(55) - Pointer: Highest Address available to BASIC($A000).
CURLIN = $0039					;(57) - Current BASIC Line number.
OLDLIN = $003B					;(59) - Previous BASIC Line number.
OLDTXT = $003D					;(61) - Pointer: BASIC Statement for CONT.
DATLIN = $003F					;(63) - Current DATA Line number.
DATPTR = $0041					;(65) - Pointer: Used by READ - current DATA Item Address.
INPPTR = $0043					;(67) - Pointer: Temporary storage of Pointer duringINPUT Routine.
VARNAM = $0045					;(69) - Name of Variable being sought in VariableTable.
VARPNT = $0047					;(71) - Pointer: to value of (VARNAM) if Integer, todescriptor if String.
FORPNT = $0049					;(73) - Pointer: Index Variable for FOR/NEXT loop.
VARTXT = $004B					;(75) - Temporary storage for TXTPTR during READ,INPUT and GET.
OPMASK = $004D					;(77) - Mask used during FRMEVL.
TEMPF3 = $004E					;(78) - Temporary storage for FLPT value.
FOUR6 = $0053					;(83) - Length of String Variable during Garbage Collection.
JMPER = $0054					;(84) - Jump Vector used in Function Evaluation - JMP followed by Address ($4C,$LB,$MB).
TEMPF1 = $0057					;(87) - Temporary storage for FLPT value.
TEMPF2 = $005C					;(92) - Temporary storage for FLPT value.
FAC = $0061						;(97) - Main Floating point Accumulator.
FACEXP = $0061					;(97) - FAC Exponent.
FACHO = $0062					;(98) - FAC Mantissa.
FACSGN = $0066					;(102) - FAC Sign.
SGNFLG = $0067					;(103) - Pointer: Series Evaluation Constant.
BITS = $0068					;(104) - Bit Overflow Area during normalisation Routine.
AFAC = $0069					;(105) - Auxiliary Floating point Accumulator.
ARGEXP = $0069					;(105) - AFAC Exponent.
ARGHO = $006A					;(106) - AFAC Mantissa.
ARGSGN = $006E					;(110) - AFAC Sign.
ARISGN = $006F					;(111) - Sign of result of Arithmetic Evaluation.
FACOV = $0070					;(112) - FAC low-order rounding.
FBUFPT = $0071					;(113) - Pointer: Used during CRUNCH/ASCII conversion.
CHRGET = $0073					;(115) - Subroutine: Get next Byte of BASIC Text.
;            ,0073  INC $7A       ,0082  BEQ $0073
;            ,0075  BNE $0079     ,0084  SEC
;            ,0077  INC $7B       ,0085  SBC #$30
;          ! ,0079  LDA $0801     ,0087  SEC
;            ,007C  CMP #$3A      ,0088  SBC #$D0
;            ,007E  BCS $008A     ,008A  RTS
;            ,0080  CMP #$20
CHRGOT = $0079					;(121) - Entry to Get same Byte again.
TXTPTR = $007A					;(122) - Pointer: Current Byte of BASIC Text.
RNDX = $008B					;(139) - Floating RND Function Seed Value.
STATUS = $0090					;(144) - Kernal I/O Status Word  ST.
STKEY = $0091					;(145) - Flag: $7F = STOP key.
SVXT = $0092					;(146) - Timing Constant for Tape.
VERCKK = $0093					;(147) - Flag: 0 = Load, 1 = Verify.
C3PO = $0094					;(148) - Flag: Serial Bus - Output Character buffered.
BSOUR = $0095					;(149) - Buffered Character for Serial Bus.
SYNO = $0096					;(150) - Cassette Sync. number.
TEMPX = $0097					;(151) - Temporary storage of X Register during CHRIN.
TEMPY = $0097					;(151) - Temporary storage of Y Register during RS232fetch.
LDTND = $0098					;(152) - Number of Open Files/Index to File Table.
DFLTN = $0099					;(153) - Default Input Device (0).
DFLTO = $009A					;(154) - Default Output Device (3).
PRTY = $009B					;(155) - Parity of Byte Output to Tape.
DPSW = $009C					;(156) - Flag: Byte received from Tape.
MSGFLG = $009D					;(157) - Flag: $00 = Program mode: Suppress Error Messages, $40 = Kernal Error Messages only,$80 = Direct mode: Full Error Messages.
FNMIDX = $009E					;(158) - Index to Cassette File name/Header ID for Tape write.
PTR1 = $009E					;(158) - Tape Error log pass 1.
PTR2 = $009F					;(159) - Tape Error log pass 2.
TIME = $00A0					;(160) - Real-time jiffy Clock (Updated by IRQ Interrupt approx. every 1/60 of Second) Update Routine: UDTIMK ($F69B).
TSFCNT = $00A3					;(163) - Bit Counter Tape Read or Write/Serial Bus OI (End Of Input) Flag.
TBTCNT = $00A4					;(164) - Pulse Counter Tape Read or Write/Serial Bus shift Counter.
CNTDN = $00A5					;(165) - Tape Synchronising count down.
BUFPNT = $00A6					;(166) - Pointer: Tape I/O buffer.
INBIT = $00A7					;(167) - RS232 temporary for received Bit/Tape temporary.
BITC1 = $00A8					;(168) - RS232 Input Bit count/Tape temporary.
RINONE = $00A9					;(169) - RS232 Flag: Start Bit check/Tape temporary.
RIDATA = $00AA					;(170) - RS232 Input Byte Buffer/Tape temporary.
RIPRTY = $00AB					;(171) - RS232 Input parity/Tape temporary.
SAL = $00AC					;(172) - Pointer: Tape Buffer/Screen scrolling.
EAL = $00AE					;(174) - Tape End Address/End of Program.
CMPO = $00B0					;(176) - Tape timing Constants.
TAPE1 = $00B2					;(178) - Pointer: Start Address of Tape Buffer ($033C).
BITTS = $00B4					;(180) - RS232 Write bit count/Tape Read timing Flag.
NXTBIT = $00B5					;(181) - RS232 Next Bit to send/Tape Read - End of Tape.
RODATA = $00B6					;(182) - RS232 Output Byte Buffer/Tape Read Error Flag.
FNLEN = $00B7					;(183) - Number of Characters in Filename.
LA = $00B8					;(184) - Current File - Logical File number.
SA = $00B9					;(185) - Current File - Secondary Address.
FA = $00BA					;(186) - Current File - First Address (Device number). OPEN LA,FA,SA;  OPEN 1,8,15,"I0":CLOSE 1
FNADR = $00BB					;(187) - Pointer: Current File name Address.
ROPRTY = $00BD					;(189) - RS232 Output Parity/Tape Byte to be Input or Output.
FSBLK = $00BE					;(190) - Tape Input/Output Block count.
MYCH = $00BF					;(191) - Serial Word Buffer.
CAS1 = $00C0					;(192) - Tape Motor Switch.
STAL = $00C1					;(193) - Start Address for LOAD and Cassette Write.
MEMUSS = $00C3					;(195) - Pointer: Type 3 Tape LOAD and general use.
LSTX = $00C5					;(197) - Matrix value of last Key pressed; No Key = $40.
NDX = $00C6					;(198) - Number of Characters in Keyboard Buffer queue.
RVS = $00C7					;(199) - Flag: Reverse On/Off; On = $01, Off = $00.
INDX = $00C8					;(200) - Pointer: End of Line for Input (Used to suppress trailing spaces).
LXSP = $00C9					;(201) - Cursor X/Y (Line/Column) position at start of Input.
SFDX = $00CB					;(203) - Flag: Print shifted Characters.
BLNSW = $00CC					;(204) - Flag: Cursor blink; $00 = Enabled, $01 = Disabled.
BLNCT = $00CD					;(205) - Timer: Count down for Cursor blink toggle.
GDBLN = $00CE					;(206) - Character under Cursor while Cursor Inverted.
BLNON = $00CF					;(207) - Flag: Cursor Status; $00 = Off, $01 = On.
CRSW = $00D0					;(208) - Flag: Input from Screen = $03, or Keyboard = $00.
PNT = $00D1					;(209) - Pointer: Current Screen Line Address.
PNTR = $00D3					;(211) - Cursor Column on current Line, including Wrap-round Line, if any.
QTSW = $00D4					;(212) - Flag: Editor in Quote Mode; $00 = Not.
LNMX = $00D5					;(213) - Current logical Line length: 39 or 79.
TBLX = $00D6					;(214) - Current Screen Line number of Cursor.
SCHAR = $00D7					;(215) - Screen value of current Input Character/Last Character Output.
INSRT = $00D8					;(216) - Count of number of inserts outstanding.
LDTB1 = $00D9					;(217) - Screen Line link Table/Editor temporaries. High Byte of Line Screen Memory Location.
USER = $00F3					;(243) - Pointer: Current Colour RAM Location.
KEYTAB = $00F5					;(245) - Vector: Current Keyboard decoding Table. ($EB81)
RIBUF = $00F7					;(247) - RS232 Input Buffer Pointer.
ROBUF = $00F9					;(249) - RS232 Output Buffer Pointer.
FREKZP = $00FB					;(251) - Free Zero Page space for User Programs.
BASZPT = $00FF					;(255) - BASIC temporary Data Area.
ASCWRK = $00FF					;(255) - Assembly Area for Floating point to ASCII conversion.


BAD = $0100					;(256) - Tape Input Error log.
STACK = $0100					;(256) - 6510 Hardware Stack Area.
BSTACK = $013F					;(319) - BASIC Stack Area.
BUF = $0200					;(512) - BASIC Input Buffer (Input Line from Screen).
LAT = $0259					;(601) - Kernal Table: Active logical File numbers.
FAT = $0263					;(611) - Kernal Table: Active File First Addresses (Device numbers).
SAT = $026D					;(621) - Kernal Table: Active File Secondary Addresses.
KEYD = $0277					;(631) - Keyboard Buffer Queue (FIFO).
MEMSTR = $0281					;(641) - Pointer: Bottom of Memory for Operating System ($0800).
MEMSIZ = $0283					;(643) - Pointer: Top of Memory for Operating System ($A000).
TIMOUT = $0285					;(645) - Serial IEEE Bus timeout defeat Flag.
COLOR = $0286					;(646) - Current Character Colour code.
GDCOL = $0287					;(647) - Background Colour under Cursor.
HIBASE = $0288					;(648) - High Byte of Screen Memory Address ($04).
XMAX = $0289					;(649) - Maximum number of Bytes in Keyboard Buffer ($0A).
RPTFLG = $028A					;(650) - Flag: Repeat keys; $00 = Cursors, INST/DEL & Keys repeat ($00).
KOUNT = $028B					;(651) - Repeat Key: Speed Counter ($04).
DELAY = $028C					;(652) - Repeat Key: First repeat delay Counter ($10).
SHFLAG = $028D					;(653) - Flag: Shift Keys: Bit 1 = Shift, Bit 2 = CBM, Bit 3 = CTRL; ($00 = None, $01 = Shift, etc.).
LSTSHF = $028E					;(654) - Last Shift Key used for debouncing.
KEYLOG = $028F					;(655) - Vector: Routine to determine Keyboard table to use based on Shift Key Pattern ($EB48).
MODE = $0291					;(657) - Flag: Upper/Lower Case change: $00 = Disabled, $80 = Enabled ($00).
AUTODN = $0292					;(658) - Flag: Auto scroll down: $00 = Disabled ($00).
M51CTR = $0293					;(659) - RS232 Pseudo 6551 control Register Image.
M51CDR = $0294					;(660) - RS232 Pseudo 6551 command Register Image.
M51AJB = $0295					;(661) - RS232 Non-standard Bits/Second.
RSSTAT = $0297					;(663) - RS232 Pseudo 6551 Status Register Image.
BITNUM = $0298					;(664) - RS232 Number of Bits left to send.
BAUDOF = $0299					;(665) - RS232 Baud Rate; Full Bit time microseconds.
RIDBE = $029B					;(667) - RS232 Index to End of Input Buffer.
RIDBS = $029C					;(668) - RS232 Pointer: High Byte of Address of Input Buffer.
RODBS = $029D					;(669) - RS232 Pointer: High Byte of Address of Output Buffer.
RODBE = $029E					;(670) - RS232 Index to End of Output Buffer.
IRQTMP = $029F					;(671) - Temporary store for IRQ Vector during Tape operations.
ENABL = $02A1					;(673) - RS232 Enables.
TODSNS = $02A2					;(674) - TOD sense during Tape I/O.
TRDTMP = $02A3					;(675) - Temporary storage during Tape READ.
TD1IRQ = $02A4					;(676) - Temporary D1IRQ Indicator during Tape READ.
TLNIDX = $02A5					;(677) - Temporary for Line Index.
TVSFLG = $02A6					;(678) - Flag: TV Standard: $00 = NTSC, $01 = PAL.
TEMP = $02A7					;(679) - Unused.
SPR11 = $02C0					;(704) - Sprite #11 Data Area.
;                                (SCREEN + $03F8 + SPR number)
;                                POKE 1024+1016+0,11  to use Sprite#0 DATA
;                                from ($02C0-$02FE).
IERROR = $0300					;(768) - Vector: Indirect entry to BASIC Error Message, (X) points to Message ($E38B).
IMAIN = $0302					;(770) - Vector: Indirect entry to BASIC Input Line and Decode ($A483).
ICRNCH = $0304					;(772) - Vector: Indirect entry to BASIC Tokenise Routine ($A57C).
IQPLOP = $0306					;(774) - Vector: Indirect entry to BASIC LIST Routine ($A71A).
IGONE = $0308					;(776) - Vector: Indirect entry to BASIC Character dispatch Routine ($A7E4).
IEVAL = $030A					;(778) - Vector: Indirect entry to BASIC Token evaluation ($AE86).
SAREG = $030C					;(780) - Storage for 6510 Accumulator during SYS.
SXREG = $030D					;(781) - Storage for 6510 X-Register during SYS.
SYREG = $030E					;(782) - Storage for 6510 Y-Register during SYS.
SPREG = $030F					;(783) - Storage for 6510 Status Register during SYS.
USRPOK = $0310					;(784) - USR Function JMP Instruction ($4C).
USRADD = $0311					;(785) - USR Address ($LB,$MB).
TEMP = $0313					;(787) - Unused.
CINV = $0314					;(788) - Vector: Hardware IRQ Interrupt Address ($EA31).
CNBINV = $0316					;(790) - Vector: BRK Instruction Interrupt Address ($FE66).
NMINV = $0318					;(792) - Vector: Hardware NMI Interrupt Address ($FE47).
IOPEN = $031A					;(794) - Vector: Indirect entry to Kernal OPEN Routine ($F34A).
ICLOSE = $031C					;(796) - Vector: Indirect entry to Kernal CLOSE Routine ($F291).
ICHKIN = $031E					;(798) - Vector: Indirect entry to Kernal CHKIN Routine ($F20E).
ICKOUT = $0320					;(800) - Vector: Indirect entry to Kernal CHKOUT Routine ($F250).
ICLRCH = $0322					;(802) - Vector: Indirect entry to Kernal CLRCHN Routine ($F333).
IBASIN = $0324					;(804) - Vector: Indirect entry to Kernal CHRIN Routine ($F157).
IBSOUT = $0326					;(806) - Vector: Indirect entry to Kernal CHROUT Routine ($F1CA).
ISTOP = $0328					;(808) - Vector: Indirect entry to Kernal STOP Routine ($F6ED).
IGETIN = $032A					;(810) - Vector: Indirect entry to Kernal GETIN Routine ($F13E).
ICLALL = $032C					;(812) - Vector: Indirect entry to Kernal CLALL Routine ($F32F).
USRCMD = $032E					;(814) - User Defined Vector ($FE66).
ILOAD = $0330					;(816) - Vector: Indirect entry to Kernal LOAD Routine ($F4A5).
ISAVE = $0332					;(818) - Vector: Indirect entry to Kernal SAVE Routine ($F5ED).
TEMP = $0334					;(820) - Unused.
TBUFFR = $033C					;(828) - Tape I/O Buffer.
SPR13 = $0340					;(832) - Sprite #13.
SPR14 = $0380					;(896) - Sprite #14.
SPR15 = $03C0					;(960) - Sprite #15.
TEMP = $03FC					;(1020) - Unused.($3c-3ff)
VICSCN = $0400					;(1024) - Default Screen Video Matrix. (400-7e7)
TEMP = $07E8					;(2024) - Unused.(7e8-7e7)
SPNTRS = $07F8					;(2040) - Default Sprite Data Pointers.

