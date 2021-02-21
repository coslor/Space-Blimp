#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <c64.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "space-blimp.h"

MOB mobs[NUM_MOBS];
char *sprite_defs=(char *)12288;
char *sprite_data_vicptr=(char *)2040;

char *screen = (char *)0x400;

byte pow2[]={1,2,4,8,16,32,64,128};
byte blimp_ptrs[2] = {193,195};
byte bomb_ptrs[2] = {192,194};

byte blimp_ptr_len = 2;
byte bomb_ptr_len = 2;

Move_Counter x_counter, y_counter;

char *fn  = "sprites.prg";
char *fn2 = "sprites";

int main(int argc, char **argv)
{
	int ret_code, ret_code2;
	byte dev;
	byte t=0;
	
	clr_screen();
		
	//
	// sprite filename might depend on whether we're running on a real machine
	//	or an emulator, so try 'sprites.prg' first, then 'sprites'
	//
	dev = get_device_num();
	ret_code=load_sprites(fn, dev);
	
	if (ret_code != 0) {
		printf("Failed to load '%s' with error code %d.\n Trying alternate filename '%s'...\n",
			fn, ret_code, fn2);
		ret_code2 = load_sprites(fn2,dev);
		
		if (ret_code2 != 0) {
			printf("Sprite load failed with code %d\n", ret_code);
			exit(ret_code); 
		}
	}
	else {
		printf("sprites loaded!\n");
	}
	
	VIC.spr_ena = 3; //SPRITE_0_MASK | SPRITE_1_MASK;
	VIC.spr_mcolor = 255;

	VIC.spr_mcolors[0] = COLOR_RED;
	VIC.spr_mcolors[1] = COLOR_WHITE;
	
	VIC.spr_color[0] = COLOR_GRAY1;
	VIC.spr_color[1] = COLOR_GRAY1;
	
	printf("Space Blimp, motha motha!!!\n");

	x_counter.sprite_move_interval = 3;
	y_counter.sprite_move_interval = 1;
	
	init_mobs();
	draw_mobs();
	
	//while (true) {};
	

	while (true) {

		//TODO replace with an IRQ for rasterline 251
		while (VIC.rasterline<251) {};	//wait for raster to go off screen
		
		//clr_screen();
		move_mobs();
		draw_mobs();
		
/*		
		
		 VIC.spr_pos[0].y = 50;
		 VIC.spr_pos[1].y = 50;
		 
		// right-pointing sprites
		sprite_data_vicptr[0]=193;
		sprite_data_vicptr[1]=192;
	
		for (i=16;i<319;i++) {
			while (VIC.rasterline<251) {};	//wait for raster to go off screen
			set_sprite_x(0,i);
			set_sprite_x(1,i);
			while (VIC.rasterline<250) {};	//wait for raster to go off screen
		}

		// left-pointing sprites		
		sprite_data_vicptr[0]=194;
		sprite_data_vicptr[1]=195;
		
		for (i=319;i>=16;i--) {
			while (VIC.rasterline<251) {};	//wait for raster to go off screen
			set_sprite_x(0,i);
			set_sprite_x(1,i);
			while (VIC.rasterline<250) {};	//wait for raster to go off screen
		}

		// right-pointing sprites
		sprite_data_vicptr[0]=193;
		sprite_data_vicptr[1]=192;

		for (i=16;i<170;i++) {
			while (VIC.rasterline<251) {};	//wait for raster to go off screen
			set_sprite_x(0,i);
			set_sprite_x(1,i);
			while (VIC.rasterline<250) {};	//wait for raster to go off screen
		}

		//drop the bomb
		for (i=50; i<250;i++) {
			while (VIC.rasterline>0) {};	//wait for raster to go off screen
			VIC.spr_pos[1].y=i;
			while (VIC.rasterline<250) {};	//wait for raster to go off screen
		}
*/	
	}
	
	return 0;
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
int load_sprites(char* fn, byte dev) {
	byte flen, ret_code;
	
	flen=(byte)strlen(fn);
	ret_code=loadbin(fn,flen,dev,0x3000);
	//printf("loadbin returned with code %d\n",ret_code);
	
	return ret_code;
}

void move_mobs() {
	int i;
	
	for (i=0;i<8;i++) {
		if (mobs[i].active == true) {
			move_mob(mobs+i);
		}
	}
}

void move_mob(MOB *m) {
	m->move_handler(m);
}

void init_mobs() {
	
	//int i;
	
	// printf("blimp_ptrs:");
	// for (i=0;i<2;i++) {
		// printf("%d=%d ",i,blimp_ptrs[i]);
	// }
	// printf("\n");
	
	//blimp
	init_MOB(0, true, 0, true, blimp_ptrs,blimp_ptr_len,
		16, false, 50, false, 1,1,COLOR_GRAY1,
		&x_counter, &y_counter,
		sprite_switching_bouncy_border_collision_handler, velocity_movement_handler);
	//bomb
	init_MOB(1, true, 1, true, bomb_ptrs,bomb_ptr_len,
		16, false, 50, false, 1,1,COLOR_GRAY1,
		&x_counter, &y_counter,
		sprite_switching_bouncy_border_collision_handler, velocity_movement_handler);

}

MOB  *init_MOB(byte num, bool active, byte sprite_num, bool mcolor, 
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
		
		return m;
	}

	

void set_bit(byte *val, byte bit_num, bool bit_val) {
	byte pwr2 = pow2[bit_num];
	
	assert(bit_num <= 8);
	
	if (bit_val) {
		*val |= pwr2;
	}
	else {
		*val &= (0xFF - pwr2);
	}
}
void draw_mobs() {
	byte i;
	
	for (i=0; i < NUM_MOBS;i++) {
		MOB *m = mobs+i;
		draw_mob(m);
	}
}

void draw_mob(MOB *m) {
	if (m->active == true) {
		byte n = m->sprite_num;
		
		set_bit(&VIC.spr_ena,n,m->active);
		
		VIC.spr_pos[n].y = m->y;
		set_sprite_x(n,m->x);
		
		sprite_data_vicptr[n]=m->sprite_ptrs[m->sprite_ptr_num];
		
		set_bit(&VIC.spr_exp_x,n,m->expand_x);
		set_bit(&VIC.spr_exp_y,n,m->expand_y);
	}
	else {
		DPRINT("sprite %d is inactive!\n",m->sprite_num);
	}
}


void dump_mob(MOB *m) {
	byte sn;
	
	printf("MOB %p Active: %d \n", m, m->active);
	printf("\tSprite %d Ptr:%d\n",m->sprite_num,m->sprite_ptrs[m->sprite_ptr_num]);
	printf("\tLoc: %d,%d\n",m->x, m->y);
	printf("\nSprite %d:\n",m->sprite_num);
	sn = m->sprite_num;
	printf("enabled:%d x:%d y:%d \n", (VIC.spr_ena & (2^sn)),
		VIC.spr_pos[sn].x, VIC.spr_pos[sn].y);
}

void set_sprite_x(byte sprite_num, int x_pos) {
	byte high_byte;
	
	assert(sprite_num<=8);
	
	VIC.spr_pos[sprite_num].x = (x_pos & 0xff);
	
	high_byte = x_pos / 256;
	set_bit(&(VIC.spr_hi_x),sprite_num,(high_byte!=0));
}

void clr_screen() {
	__asm__("jsr %w", CLR_SCRN);
}

void bouncy_border_collision_handler(MOB *m, CollisionType type) {
	assert(m != NULL);
	
	
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
}

void velocity_movement_handler(MOB *m) {
	CollisionType ct=CT_NONE;

	assert(m != NULL);
	

	// Move the MOB (60 / sprite_move_interval) times/sec
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
		
		
	assert(m->coll_handler != NULL);
	if ((ct != CT_NONE) ) {
		m->coll_handler(m, ct);
	}
}

void sprite_switching_bouncy_border_collision_handler(MOB *m, CollisionType type) {
	assert(m != NULL && type != NULL);
	
	bouncy_border_collision_handler(m, type);
	if (type == CT_LEFT) {
		prev_sprite_ptr(m);
	}
	else if (type == CT_RIGHT) {
		next_sprite_ptr(m);
	}
}	


   
void next_sprite_ptr(MOB *m) {
	m->sprite_ptr_num = (m->sprite_ptr_num +(byte)1) % (m->sprite_ptrs_len);
}

void prev_sprite_ptr(MOB *m) {
	m->sprite_ptr_num = (m->sprite_ptr_num -(byte)1) % (m->sprite_ptrs_len);	
}

