#include <stdint.h>
#include <c64.h>
#include <6502.h>
#include <stdbool.h>


#define CINV (*(uint16_t *) 0x0314)
//#define GHOST (*(uint8_t *) 0x3fff)
//#define RASTERLINE_TOP    (249)
//#define RASTERLINE_BOTTOM (RASTERLINE_TOP + 3)
#define SCRN_CELL1 *((byte *) 0x400)



#define SET_ISR(isr_addr) 		\
	__asm__("sei"); 			\
	CINV = (uint16_t)isr_addr;	\
	__asm__("cli");

#define EXIT_ISR() 				\
	__asm__("jmp $ea81");

#define RED_START 	75
#define WHITE_START	125
#define BLUE_START	175
#define OLD_START	225

typedef uint8_t byte;


byte ISR_RED();
byte ISR_WHITE();
byte ISR_BLUE();
byte ISR_OLD();


byte old_color;

byte stack[32];


byte ISR_RED() {
	VIC.irr = 1; //ACK raster compare IRQ


	//asm("asl %g",ISR);
	VIC.bordercolor = COLOR_RED;
	
	VIC.rasterline = WHITE_START;
	
	//for (i=0;i=10;i++) {
	//	__asm__("nop");
	//}
	
	//VIC.bordercolor = old_color;
	

	set_irq(ISR_WHITE,stack,sizeof(stack));
	//SET_ISR(ISR2)
	
	
	//return IRQ_NOT_HANDLED;
	//__asm__("jmp $ea31");
	
  // if (VIC.rasterline < RASTERLINE_BOTTOM) {
    // VIC.ctrl1 = 0x13; //25 rows,y dot-pos 2
    // VIC.rasterline = RASTERLINE_BOTTOM;
  // } else {
    // VIC.ctrl1 = 0x1b;
    // VIC.rasterline = RASTERLINE_TOP;
  // }
  // VIC.irr = 1; //ACK raster compare IRQ
  // __asm__("jmp $ea81");
  
	return IRQ_NOT_HANDLED;
	//EXIT_ISR()
}

byte ISR_WHITE() {
	VIC.irr = 1; //ACK raster compare IRQ
	
	VIC.bordercolor = COLOR_WHITE;

	
	VIC.rasterline = BLUE_START;
	set_irq(ISR_BLUE, stack, sizeof(stack));
	//SET_ISR(ISR3)
	//VIC.bgcolor0=1;
	return IRQ_NOT_HANDLED;
	//EXIT_ISR()
	
}

byte ISR_BLUE() {
	VIC.irr = 1; //ACK raster compare IRQ

	VIC.bordercolor = COLOR_BLUE;
	
	VIC.rasterline = OLD_START;
	set_irq(ISR_OLD, stack, sizeof(stack));
	
	//SET_ISR(ISR)
	//VIC.bgcolor0=1;
	return IRQ_NOT_HANDLED;
	//EXIT_ISR()
	
}

byte ISR_OLD() {
	VIC.irr = 1;
	VIC.bordercolor = old_color;
	VIC.rasterline = RED_START;

	set_irq(ISR_RED,stack,sizeof(stack));
	return IRQ_NOT_HANDLED;
}

void main(void) {

	old_color = VIC.bordercolor;
	
	//VIC.bordercolor=7;

	
	CIA1.icr = 0x7f;	//(DC0D)disable CIA interrupts
	VIC.ctrl1 &= 0b01111111;

	//SEI();
	//CINV = (uint16_t) ISR;
	//set_irq (&ISR, stack,sizeof(stack));
	
	//VIC.rasterline = RASTERLINE_TOP;
	//VIC.ctrl1 = 0x1b;	//0001 1011 = blank scrn, to border,24 rows, y dot-position 3(?)
	VIC.ctrl1 &= 0b01111111;
	VIC.imr = 1; //IRQ mask register, 1=interrupt enabled
	
	VIC.rasterline = RED_START;
	set_irq (ISR_RED, stack,sizeof(stack));
	//SET_ISR(ISR)

	//CLI();

main_loop:
//	exit(0);
	while (true) {
		--SCRN_CELL1;
	}
} 