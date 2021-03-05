#ifndef SPACE_BLIMP_H
#define SPACE_BLIMP_H 1
#endif

#define CLR 9
//0x93 
#define CHROUT 0xffd2
#define CLR_SCRN 0xe544

#define Y_MIN 49
#define Y_MAX 230
#define X_MIN 18
#define X_MAX 319

#define NUM_MOBS 2

#define BLIMP 6
#define BOMB 7

#define R_BLIMP_SPR 193
#define R_BOMB_SPR 192
#define L_BLIMP_SPR 195
#define L_BOMB_SPR 194

#define BOMB_MOB 1
#define BLIMP_MOB 0


#define DEBUG

#ifdef DEBUG
	#define DPRINT(arg1,arg2) printf("%s(%d):%s=%d\n",__FILE__,__LINE__,arg1,arg2);
#else
	#define DPRINT(arg1,arg2) 
#endif

#ifdef DEBUG
	#define START_TIMER(color) 	byte old_color; old_color = VIC.bordercolor; VIC.bordercolor=color;
	#define STOP_TIMER() 		VIC.bordercolor=old_color;
#else
	#define START_TIMER(color) ;
	#define STOP_TIMER() ;
#endif


#define SET_BIT(value,bit_num,bit_val) if (bit_val) {*value |= 1<<bit_num;} else {*value &= (0xFF - (1<<bit_num));};

//#define DPRINT(string,arg1,arg2,arg3,arg4) { ##ifdef DEBUG printf(##string,##arg1,##arg2,##arg3,##arg4); ##endif }

//#define TEST(a,b) { printf("%d\n",(##a + ##b)); }


typedef uint8_t byte;
typedef int8_t sbyte;
typedef uint16_t word;

typedef struct MOB MOB;
typedef void (*CollisionHandler)(byte, CollisionType);
typedef void (*MovementHandler)(byte);



typedef struct Move_Counter {
	byte sprite_move_timer;									
	byte sprite_move_interval;	
} Move_Counter;

typedef struct MOB {
	bool active;
	
	byte sprite_num;
	
	signed int x;
	signed int y;
	
	byte color;
	
	bool mcolor;
	
	bool expand_x;
	bool expand_y;
	
	sbyte xvel;
	sbyte yvel;
	
	Move_Counter x_counter;
	Move_Counter y_counter;
	
	CollisionHandler coll_handler;
	MovementHandler move_handler;

	byte sprite_ptrs_len;
	byte sprite_ptr_num;
	byte *sprite_ptrs;
	
	
	
} MOB;

typedef enum {CT_NONE,CT_RIGHT, CT_TOP, CT_LEFT, CT_BOTTOM} CollisionType;

byte get_device_num();
extern byte fastcall loadbin(char* filename, byte fname_len, byte device, unsigned int address);
//void clr_screen();

//byte handle_sprites();

//typedef void handle_collision(MOB mob, border_collision_type ct) CollisionHandler;
void init_MOB(byte num, bool active, byte sprite_num, bool mcolor, 						\
	byte* sprite_ptrs, byte sprite_ptrs_len,											\
	word x, bool expand_x, byte y, bool expand_y, sbyte xvel, sbyte yvel, byte color,	\
	Move_Counter *x_counter, Move_Counter *y_counter, 									\
	CollisionHandler coll_handler, MovementHandler move_handler);

void move_mobs();

// collision handlers
void sprite_switching_bouncy_border_collision_handler(byte, CollisionType);
void bouncy_border_collision_handler(byte, CollisionType);
void sprite_switching_bouncy_border_collision_handler(byte, CollisionType);
void bomb_border_collision_handler(byte, CollisionType);

//movement handlers
void velocity_movement_handler(byte);

void handle_border_collision(byte, CollisionType);

byte load_sprites();
byte load_chars();

void set_video_charset_addresses(word screen_addr,word charset_addr);

void init_mobs();
//void set_bit(byte *, byte, bool);
void move_mob(byte);
void move_mobs();
void draw_mobs();
void dump_mob(byte);
void draw_mob(byte);

void next_sprite_ptr(byte);
void prev_sprite_ptr(byte);

byte do_IRQ();
void reset_bomb();

void set_sprite(byte, byte);


typedef struct params_set_sprite_x {
	byte sprite_num;
	int x_pos;
} params_set_sprite_x;
//void set_sprite_x(byte, int);
void set_sprite_x(params_set_sprite_x *);

void draw_city(byte start_row,start_col);