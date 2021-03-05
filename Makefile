# Simple cc65 Makefile

PROGRAM = Space-Blimp

SOURCES= $(PROGRAM).c loadbin.asm
VICE_HOME=C:\Users\chris\WinVice\GTK3VICE-3.4-win64-r37388
VICE=$(VICE_HOME)\x64sc.exe
1541=$(VICE_HOME)\c1541.exe
CC65_TARGET = c64
CC65_HOME=C:\Users\chris\cc65

CC      = $(CC65_HOME)\bin\cl65.exe
##CFLAGS  = -t $(CC65_TARGET) --create-dep -O
##LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map -g -Ln $(PROGRAM).vs
#CFLAGS   =  -Wl --dbgfile,$(PROGRAM).dbg -vm -l $(PROGRAM).lst -t $(CC65_TARGET) -Ln $(PROGRAM).vs -m $(PROGRAM).map -g 
CFLAGS  = -t $(CC65_TARGET) --create-dep $(<:.c=.d)  -Wl --dbgfile,$(PROGRAM).dbg -vm -l $(PROGRAM).lst -t $(CC65_TARGET) -Ln $(PROGRAM).vs -m $(PROGRAM).map -g -Oi
LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map
RM = del


.SUFFIXES:
.PHONY: all clean

#all: $(PROGRAM)
all: blimp-disk.d64

#$(PROGRAM):	$(SOURCES)
#	$(CC) $(CFLAGS) -O -o $(PROGRAM) $(SOURCES)


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROGRAM): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^

include $(wildcard $(SRCS:.c=.d))

#space-blimp:	space-blimp.c space-blimp.h

space-blimp.c: 
	space-blimp.h:

#clean:
#	del $(PROGRAM).d $(PROGRAM).o $(PROGRAM) $(PROGRAM).d64 

# %.d64: $(PROGRAM)
blimp-disk.d64:	$(PROGRAM)
#	$(1541) -attach blimp-disk.d64 -format $(PROGRAM),bd -write $(PROGRAM) -write sprites.prg -list
#	$(1541) -format "$(PROGRAM),xx" d64 $(PROGRAM).d64
#	$(1541) -attach $(PROGRAM).d64 -delete $(PROGRAM) -write $(PROGRAM) -dir
	$(1541) -format "blimp-disk,xx" d64 blimp-disk.d64 -attach blimp-disk.d64 -write $(PROGRAM) -write sprites.prg -write "sb mc chars.prg" -list	
	
clean:
#	$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map $(PROGRAM).vs blimp-disk.d64
	$(RM) *.o $(PROGRAM) $(PROGRAM).map $(PROGRAM).vs blimp-disk.d64 
	
#run: %.d64
run:	blimp-disk.d64
	$(VICE) blimp-disk.d64