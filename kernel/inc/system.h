#ifndef __SYSTEM_H_INCLUDE

#define __SYSTEM_H_INCLUDE

/* SYSTEM.C */
/* Types */
typedef unsigned int   uint32;
typedef          int   int32;
typedef unsigned short uint16;
typedef          short int16;
typedef unsigned char  uint8;
typedef          char  int8;

/* System functions */
extern void *memcpy( void *dst, const void *src, uint32 count );
extern void *memset( void *dst, uint8 val, uint32 count );
extern void *memsetw( void *dst, uint16 val, uint32 count );
extern uint32 strlen( const uint8 *str );
extern uint8 inportb( uint16 _port );
extern void outportb( uint16 _port, uint8 _data );

/* Output functions */
extern uint8 encode_color( uint8 bkg, uint8 frg );
extern void init_video();
extern void clear_screen();
extern void scroll();
extern void move_cursor();
extern void putch( uint8 ch );
extern void puts( const uint8 *s );

/* Constants */
#define VIDEO_RAM_ADDRESS 0xB8000
#define CONSOLE_WIDTH     80
#define CONSOLE_HEIGHT    25
#define CONSOLE_DEPTH     2
#define TAB_WIDTH         8
/* Colors */
#define CLR_BLACK         0
#define CLR_BLUE          1
#define CLR_GREEN         2
#define CLR_CYAN          3
#define CLR_RED           4
#define CLR_MAGENTA       5
#define CLR_BROWN         6
#define CLR_LIGHT_GREY    7
#define CLR_DARK_GREY     8
#define CLR_LIGHT_BLUE    9
#define CLR_LIGHT_GREEN   10
#define CLR_LIGHT_CYAN    11
#define CLR_LIGHT_RED     12
#define CLR_LIGHT_MAGENTA 13
#define CLR_LIGHT_BROWN   14
#define CLR_WHITE         15
/* Characters */
#define CHAR_NULL            '\0'
#define CHAR_BACKSPACE       0x08
#define CHAR_TAB             0x09
#define CHAR_CARRIAGE_RETURN '\r'
#define CHAR_NEW_LINE        '\n'
#define CHAR_SPACE           ' '

#endif // __SYSTEM_H_INCLUDE
