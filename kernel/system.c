#include "system.h"

unsigned char *vidmem;
unsigned char attrib;
unsigned short cur_x, cur_y;

void *memcpy( void *dst, const void *src, unsigned int count )
{
	unsigned char *d = (unsigned char*) dst;
	unsigned char *s = (unsigned char*) src;
	while ( count-- ) *d++ = *s++;
	return dst;
}

void *memset( void *dst, unsigned char val, unsigned int count )
{
	unsigned char *d = (unsigned char*) dst;
	while ( count-- ) *d++ = val;
	return dst;
}

void *memsetw( void *dst, unsigned short val, unsigned int count )
{
	unsigned short *d = (unsigned short*) dst;
	while ( count-- ) *d++ = val;
	return dst;
}

unsigned int strlen( const unsigned char *str )
{
	unsigned int l = 0;
	while ( *str++ != CHAR_NULL ) ++l;
	return l;
}

unsigned char inportb( unsigned short _port )
{
	unsigned char rv;
	__asm__ __volatile__( "inb %1, %0" : "=a" (rv) : "dN" (_port) );
	return rv;
}

void outportb( unsigned short _port, unsigned char _data )
{
	__asm__ __volatile__( "outb %1, %0" : : "dN" (_port), "a" (_data) );
}

unsigned char encode_color( unsigned char bkg, unsigned char frg )
{
	return (bkg << 4) | frg;
}

void init_video()
{
	vidmem = (unsigned char*) VIDEO_RAM_ADDRESS;
	attrib = encode_color( CLR_BLACK, CLR_LIGHT_GREY );
	clear_screen();
}

void clear_screen()
{
	unsigned int i = 0;
	unsigned char tmp = attrib;
	attrib = encode_color(CLR_BLACK, CLR_LIGHT_GREY);

	cur_x = 0;
	cur_y = 0;
	while ( i < CONSOLE_WIDTH * CONSOLE_HEIGHT )
	{
		putch( CHAR_SPACE );
		++i;
	}
	cur_x = 0;
	cur_y = 0;
	attrib = tmp;
}

void scroll()
{
	if ( cur_y < CONSOLE_HEIGHT ) return;

	unsigned short tmp = cur_y - CONSOLE_HEIGHT + 1;
	memcpy( vidmem,
		&vidmem[tmp * CONSOLE_WIDTH * CONSOLE_DEPTH],
		CONSOLE_DEPTH * CONSOLE_WIDTH * ( CONSOLE_HEIGHT - tmp ) );
	unsigned short blank = ((unsigned short)attrib << 8) | CHAR_SPACE;
	memsetw( &vidmem[CONSOLE_WIDTH * ( CONSOLE_HEIGHT - tmp )], blank, CONSOLE_WIDTH );
	cur_y = CONSOLE_HEIGHT - 1;
}

void move_cursor()
{
	unsigned tmp = cur_y * CONSOLE_WIDTH + cur_x;

	/* This sends a command to indicies 14 and 15 in the
	*  CRT Control Register of the VGA controller. These
	*  are the high and low bytes of the index that show
	*  where the hardware cursor is to be 'blinking'. To
	*  learn more, you should look up some VGA specific
	*  programming documents. A great start to graphics:
	*  http://www.brackeen.com/home/vga */
	outportb(0x3D4, 14);
	outportb(0x3D5, tmp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, tmp);
}

void putch( unsigned char ch )
{
	switch ( ch )
	{
		case CHAR_BACKSPACE:
			if ( cur_x != 0 ) --cur_x;
			break;
		case CHAR_TAB:
			cur_x = ( cur_x + TAB_WIDTH ) & ~( TAB_WIDTH - 1 );
			break;
		case CHAR_CARRIAGE_RETURN:
			cur_x = 0;
			break;
		case CHAR_NEW_LINE:
			cur_x = 0;
			++cur_y;
			break;
		default:
			if ( ch >= CHAR_SPACE )
			{
				unsigned char *cur = &vidmem[(cur_y * CONSOLE_WIDTH + cur_x) * CONSOLE_DEPTH];
				*cur = ch;
				*++cur = attrib;
				++cur_x;
			}
			break;
	}

	if ( cur_x >= CONSOLE_WIDTH )
	{
		cur_x = 0;
		++cur_y;
	}

	scroll();
	move_cursor();
}

void puts( const unsigned char *s )
{
	unsigned int i = 0, n = strlen( s );
	while ( i < n ) putch( s[i++] );
}
