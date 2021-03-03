#include <stdint.h>
#include <c64.h>
#include <6502.h>

#define CINV (*(uint16_t *) 0x0314)
#define GHOST (*(uint8_t *) 0x3fff)
#define RASTERLINE_TOP    (249)
#define RASTERLINE_BOTTOM (RASTERLINE_TOP + 3)

#define STACK_SIZE 20
unsigned char stack[STACK_SIZE];

void ISR(void) {
  if (VIC.rasterline < RASTERLINE_BOTTOM) {
    VIC.ctrl1 = 0x13; //25 rows,y dot-pos 2
	VIC.bordercolor=1;
    VIC.rasterline = RASTERLINE_BOTTOM;
  } else {
    VIC.ctrl1 = 0x1b;
	VIC.bordercolor=2;
    VIC.rasterline = RASTERLINE_TOP;
  }
  VIC.irr = 1; //ACK raster compare IRQ
  __asm__("jmp $ea81");
}

void main(void) {
  CIA1.icr = 0x7f;	//disable CIA interrupts
  CINV = (uint16_t) ISR;	//set interrupt vector to our ISR function;
  //set_irq(ISR,stack,STACK_SIZE);
  
  VIC.rasterline = RASTERLINE_TOP;
  VIC.ctrl1 = 0x1b;	//0001 1011 = blank scrn, to border,24 rows, y dot-position 3(?)
  VIC.imr = 1; //IRQ mask register, 1=interrupt enabled


  for (;;) {
    ++GHOST;
  }
} 