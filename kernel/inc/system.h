#ifndef __SYSTEM_H_INCLUDE

#define __SYSTEM_H_INCLUDE

/* SYSTEM.C */
/* System functions */
extern void *memcpy( void *dst, const void *src, unsigned int count );
extern void *memset( void *dst, unsigned char val, unsigned int count );
extern unsigned int strlen( const unsigned char *str );
extern unsigned char inportb( unsigned short _port );
extern void outportb( unsigned short _port, unsigned char _data );

/* Output functions */
extern char encodecolor( char bkg, char frg );
extern void clear_screen();
extern void print2screen( char *message, unsigned int row, unsigned int col, unsigned int color );

/* Constants */
#define VIDEO_RAM_ADDRESS 0xB8000
#define CONSOLE_WIDTH     80
#define CONSOLE_HEIGHT    25
#define CONSOLE_DEPTH     2
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

#endif // __SYSTEM_H_INCLUDE
