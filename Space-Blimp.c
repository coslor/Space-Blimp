#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <c64.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <6502.h>
#include <joystick.h>
#include <conio.h>

#include "space-blimp.h"

MOB mobs[NUM_MOBS];
char *sprite_defs=(char *)12288;
char *sprite_data_vicptr=(char *)2040;

char *screen = (char *)0x400;

byte pow2[]={1,2,4,8,16,32,64,128};
byte blimp_spr_ptrs[2] = {R_BLIMP_SPR,L_BLIMP_SPR};
byte bomb_spr_ptrs[2] = {R_BOMB_SPR,L_BOMB_SPR};

byte blimp_ptr_len = 2;
byte bomb_ptr_len = 2;

Move_Counter x_counter, y_counter;

char *sprite_fn  = "sprites.prg";
char *char_fn = "sb mc chars.prg";
//char *fn2 = "sprites";

byte irq_stack[64];

params_set_sprite_x	set_sprite_x_params;

int main(int argc, char **argv)
{
	byte t=0;
	
	clrscr();	//clear screen
	VIC.bgcolor0 = COLOR_BLACK;
	VIC.bordercolor = COLOR_BLACK;

	load_sprites();
	VIC.spr_ena = 3; //SPRITE_0_MASK | SPRITE_1_MASK;
	VIC.spr_mcolor = 255;

	VIC.spr_mcolors[0] = COLOR_RED;
	VIC.spr_mcolors[1] = COLOR_WHITE;
	
	VIC.spr_color[0] = COLOR_GRAY1;
	VIC.spr_color[1] = COLOR_GRAY1;
	
	load_chars();
	set_video_charset_addresses(0x0400,0x3800);
	*((byte *)53270) |= 0b00010000;		//enable mcolor
	VIC.bgcolor[1] = COLOR_GRAY1;
	VIC.bgcolor[2] = COLOR_GRAY2;
	
	
	printf("Space Blimp, motha motha!!!\n");

	x_counter.sprite_move_interval = 0;
	y_counter.sprite_move_interval = 0;
	
	init_mobs();
	draw_mobs();

	//run do_IRQ() to run every time the electron gun hits the blanking interval
	CIA1.icr = 0x7f;	//(DC0D)disable CIA interrupts
	VIC.ctrl1 &= 0b01111111;
	VIC.imr = 1; //IRQ mask register, 1=interrupt enabled
	VIC.rasterline=255;	
	
	set_irq(do_IRQ,irq_stack,sizeof(irq_stack));

	draw_city(22,17);
	
	while (true) {
		if (kbhit() && cgetc() == ' ') {
			printf("FIRE AWAY!\n");
			mobs[BOMB_MOB].yvel = 1;
			//mobs[BOMB_MOB].xvel = 0;
			mobs[BOMB_MOB].coll_handler = bomb_border_collision_handler;
		}				
	}
	return 0;
}

void draw_city(byte start_row,start_col) {
	byte r,c;
	word sr_offset,cr_offset,sc_offset,ch_offset;
	byte *sp,*cp;
	
	for (r=0;r<3; r++) {
		sr_offset = 40*(start_row + r);
		cr_offset = 6*r;
		
		for (c=0;c<6;c++) {
			sc_offset = sr_offset + start_col + c;
			ch_offset = cr_offset + c;
			
			sp=(byte *)(0x0400 + sc_offset);
			*sp=129 + ch_offset;
			cp=(byte *)(COLOR_RAM + sc_offset);
			*cp=9;
			
		}	//for c
	}	//for r
}	//draw_city


//TODO get rid of loadbin() and use cbm_load() instead
byte load_sprites() {
	byte dev;
	byte ret_code = 0;
	
	dev = get_device_num();
	ret_code=loadbin(sprite_fn,(byte)strlen(sprite_fn),dev,0x3000);
	
	if (ret_code != 0) {
		printf("Sprite load %s failed:code %d\n", sprite_fn, ret_code);
		exit(ret_code); 
	}
	else {
		printf("Sprites loaded!\n");
	}	
}

//TODO get rid of loadbin() and use cbm_load() instead
byte load_chars() {
	byte dev;
	byte ret_code = 0;
	
	dev = get_device_num();
	ret_code=loadbin(char_fn,(byte)strlen(char_fn),dev,0x3800);
	
	if (ret_code != 0) {
		printf("Char load %s failed: code %d\n", char_fn, ret_code);
		exit(ret_code); 
	}
	else {
		printf("Chars loaded!\n");
	}	
}

void set_video_charset_addresses(word screen_addr,word charset_addr) {
	word val;
	
	val = ((screen_addr >> 10) <<4) | ((charset_addr >> 11)<<1);
	VIC.addr = val;
}

byte do_IRQ() {
	START_TIMER(COLOR_WHITE);
	
	VIC.irr = 1;
	
	move_mobs();
	draw_mobs();
	
	
	STOP_TIMER();
	
	return IRQ_NOT_HANDLED;
}

byte get_device_num() {
	int d;
	
	// read last used device number
	d = *((byte*)0xba);
	if (d < 8 || d > 31) {
		d = 8;
	}
	//printf("device=%d\n",dev);
	return d;
}
// int load_sprites(char* fn, byte dev) {
	// byte flen, ret_code;
	
	// flen=(byte)strlen(fn);
	// ret_code=loadbin(fn,flen,dev,0x3000);
	////printf("loadbin returned with code %d\n",ret_code);
	
	// return ret_code;
// }

void move_mobs() {
	byte i;
	MOB *m;
	
	START_TIMER(COLOR_YELLOW);
	
	m=mobs;
	for (i=0;i<NUM_MOBS;i++) {
		
		if (m->active) {
			m->move_handler(i);		
		}
		++m;
	}
	STOP_TIMER();
}


void init_mobs() {
	
	//blimp
	init_MOB(BLIMP_MOB, true, 0, true, blimp_spr_ptrs,blimp_ptr_len,
		X_MIN, false, Y_MIN, false, 1,0,COLOR_GRAY1,
		&x_counter, &y_counter,
		sprite_switching_bouncy_border_collision_handler, velocity_movement_handler);
		
	//bomb
	init_MOB(BOMB_MOB, true, 1, true, bomb_spr_ptrs,bomb_ptr_len,
		X_MIN, false, Y_MIN, false, 1,0,COLOR_GRAY1,
		&x_counter, &y_counter,
		sprite_switching_bouncy_border_collision_handler, velocity_movement_handler);

}

void init_MOB(byte num, bool active, byte sprite_num, bool mcolor, 
	byte* sprite_ptrs, byte sprite_ptrs_len, 
	word x, bool expand_x, byte y, bool expand_y, sbyte xvel, sbyte yvel, byte color, 
	Move_Counter *x_counter, Move_Counter *y_counter,
	CollisionHandler coll_handler, MovementHandler move_handler) {
		MOB *m = mobs + num;
		m->active = active;
		m->sprite_num = sprite_num;
		m->sprite_ptrs = sprite_ptrs;
		m->sprite_ptrs_len = sprite_ptrs_len;
		m->sprite_ptr_num = 0;
		m->x = x;
		m->y = y;
		m->mcolor = mcolor;
		m->expand_x = expand_x;
		m->expand_y = expand_y;
		m->xvel = xvel;
		m->yvel = yvel;
		m->color = color;
		m->x_counter = *x_counter;
		m->y_counter = *y_counter;
		m->coll_handler = coll_handler;
		m->move_handler = move_handler;
		
		set_sprite(num, sprite_num);
		
		sprite_data_vicptr[m->sprite_num]=m->sprite_ptrs[m->sprite_ptr_num];
		
	}

	

void set_bit(byte *val, byte bit_num, bool bit_val) {
	byte pwr2;
	START_TIMER(COLOR_PURPLE);
	
	pwr2 = 1<<bit_num;
		
	if (bit_val) {
		*val |= pwr2;
	}
	else {
		*val &= (0xFF - pwr2);
	}
	STOP_TIMER()}

void draw_mobs() {
	byte i, n;
	MOB *m;
	
	START_TIMER(COLOR_GREEN);
	
	for (i=0; i < NUM_MOBS;i++) {
		m = mobs+i;
		if (m->active) {
			n = m->sprite_num;
			VIC.spr_pos[n].y = m->y;
			
			set_sprite_x_params.sprite_num=n;
			set_sprite_x_params.x_pos=m->x;
			set_sprite_x(&set_sprite_x_params);
		}
	}
	STOP_TIMER()}


void set_sprite(byte mob_num, byte sprite_num) {
	MOB *m;
	
	m=mobs+mob_num;
	m->sprite_num = sprite_num;
	SET_BIT(&VIC.spr_ena,sprite_num,true);
	//set_bit(&VIC.spr_exp_x,n,m->expand_x);
	//set_bit(&VIC.spr_exp_y,n,m->expand_y);
}

void dump_mob(byte mob_num) {
	byte sn;
	MOB *m;
	
	m-mobs+mob_num;
	printf("MOB %p Active: %d \n", m, m->active);
	printf("\tSprite %d Ptr:%d\n",m->sprite_num,m->sprite_ptrs[m->sprite_ptr_num]);
	printf("\tLoc: %d,%d\n",m->x, m->y);
	printf("\nSprite %d:\n",m->sprite_num);
	sn = m->sprite_num;
	printf("enabled:%d x:%d y:%d \n", (VIC.spr_ena & (1<<sn)),
		VIC.spr_pos[sn].x, VIC.spr_pos[sn].y);
}

//void set_sprite_x(byte sprite_num, int x_pos) {
void set_sprite_x(params_set_sprite_x *params) {
	byte high_byte;
	
	START_TIMER(COLOR_LIGHTGREEN);
	
	VIC.spr_pos[params->sprite_num].x = params->x_pos;//(x_pos & 0xff);
	
	high_byte = params->x_pos >> 8; //x_pos / 256
	SET_BIT(&VIC.spr_hi_x,params->sprite_num,(high_byte!=0));
	
	STOP_TIMER();
}

void clr_screen() {
	__asm__("jsr %w", CLR_SCRN);
}

void bouncy_border_collision_handler(byte mob_num, CollisionType type) {
//	assert(m != NULL);	
	MOB *m;
	
	START_TIMER(COLOR_LIGHTRED);
	m=mobs+mob_num;

	switch(type) {
		case CT_LEFT: {
			m->x = X_MIN + 1;
			m->xvel *= -1;
			break;
		}
		case CT_RIGHT: {
			m->x = X_MAX-1;
			m->xvel *= -1;
			break;
		}
		case CT_TOP: {
			m->y = Y_MIN + 1;
			m->yvel *= -1;
			break;			
		}
		case CT_BOTTOM: {
			m->y = Y_MAX-1;
			m->yvel *= -1;
			break;			
		}
	}
	
	STOP_TIMER();
}

void sprite_switching_bouncy_border_collision_handler(byte mob_num, CollisionType type) {
	START_TIMER(COLOR_BLUE);
	
	bouncy_border_collision_handler(mob_num, type);
	if (type == CT_LEFT) {
		prev_sprite_ptr(mob_num);
	}
	else if (type == CT_RIGHT) {
		next_sprite_ptr(mob_num);
	}
	STOP_TIMER();
}	

void bomb_border_collision_handler(byte mob_num, CollisionType type) {
	START_TIMER(COLOR_RED);
	
	//assert(m != NULL);	
	//assert (type != CT_TOP); 	//if this happens we have a problem somewhere - the bomb should only fall DOWN!
	
	switch (type){
		case CT_LEFT: {
			mobs[mob_num].x = X_MAX;	//wrap around
			break;
		}
		case CT_RIGHT: {
			mobs[mob_num].x = X_MIN;	//wrap around
			break;
		}
		case CT_BOTTOM: {
			//TODO did we hit a city? If so, BOOOOM!!
			reset_bomb();
			break;
		}
		default: {
			//break;	//TODO we should log a message here somehow
			VIC.bgcolor0=COLOR_RED;
			exit(1);
		}
	}
	STOP_TIMER();
}

void reset_bomb() {
	MOB *m;

	m = mobs+BOMB_MOB;
	
	m->yvel = 0;
	m->xvel = mobs[BLIMP_MOB].xvel;
	
	m->x = mobs[BLIMP_MOB].x;
	m->y = mobs[BLIMP_MOB].y;
	
	m->sprite_ptr_num = mobs[BLIMP_MOB].sprite_ptr_num;
	m->coll_handler = sprite_switching_bouncy_border_collision_handler;
}


void velocity_movement_handler(byte mob_num) {
	CollisionType ct=CT_NONE;
	MOB *m;

	START_TIMER(COLOR_ORANGE);
	
	// Move the MOB ((60 for NTSC, 50 for PAL) / sprite_move_interval) times/sec
	m=mobs+mob_num;
	
	//	Use sprite_move_interval to slow a sprite's movement.
	if ((m->x_counter.sprite_move_timer--) == 0) {		
		m->x += m->xvel;
		if (m->x < X_MIN) {
			ct = CT_LEFT;
		} 
		else if (m->x >= X_MAX) {
			ct = CT_RIGHT;
		}
		m->x_counter.sprite_move_timer = m->x_counter.sprite_move_interval;
	}
	
	if ((m->y_counter.sprite_move_timer--) == 0) {
		m->y += m->yvel;
		if (m->y < Y_MIN) {
			ct = CT_TOP;
		}
		else if (m->y >= Y_MAX) {
			ct = CT_BOTTOM;
		}
		m->y_counter.sprite_move_timer = m->y_counter.sprite_move_interval;
	}
		
	if ((ct != CT_NONE) ) {
		m->coll_handler(mob_num, ct);
	}
	STOP_TIMER();
}
   
void next_sprite_ptr(byte mob_num) {
	MOB *m;
	
	m=mobs+mob_num;
	m->sprite_ptr_num = (m->sprite_ptr_num +(byte)1) % (m->sprite_ptrs_len);
	sprite_data_vicptr[m->sprite_num]=m->sprite_ptrs[m->sprite_ptr_num];

}

void prev_sprite_ptr(byte mob_num) {
	MOB *m;
	
	m=mobs+mob_num;
	m->sprite_ptr_num = (m->sprite_ptr_num -(byte)1) % (m->sprite_ptrs_len);
	sprite_data_vicptr[m->sprite_num]=m->sprite_ptrs[m->sprite_ptr_num];
	
}


			
