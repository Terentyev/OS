#include "system.h"

uint8 *vidmem;
uint8 attrib;
uint16 cur_x, cur_y;

void *memcpy( void *dst, const void *src, uint32 count )
{
	uint8 *d = (uint8*) dst;
	uint8 *s = (uint8*) src;
	while ( count-- ) *d++ = *s++;
	return dst;
}

void *memset( void *dst, uint8 val, uint32 count )
{
	uint8 *d = (uint8*) dst;
	while ( count-- ) *d++ = val;
	return dst;
}

void *memsetw( void *dst, uint16 val, uint32 count )
{
	uint16 *d = (uint16*) dst;
	while ( count-- ) *d++ = val;
	return dst;
}

uint32 strlen( const uint8 *str )
{
	uint32 l = 0;
	while ( *str++ != CHAR_NULL ) ++l;
	return l;
}

uint8 inportb( uint16 _port )
{
	uint8 rv;
	__asm__ __volatile__( "inb %1, %0" : "=a" (rv) : "dN" (_port) );
	return rv;
}

void outportb( uint16 _port, uint8 _data )
{
	__asm__ __volatile__( "outb %1, %0" : : "dN" (_port), "a" (_data) );
}

uint8 encode_color( uint8 bkg, uint8 frg )
{
	return (bkg << 4) | frg;
}

void init_video()
{
	vidmem = (uint8*) VIDEO_RAM_ADDRESS;
	attrib = encode_color( CLR_BLACK, CLR_LIGHT_GREY );
	clear_screen();
}

void clear_screen()
{
	uint32 i = 0;
	uint8 tmp = attrib;
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

	uint16 tmp = cur_y - CONSOLE_HEIGHT + 1;
	memcpy( vidmem,
		&vidmem[tmp * CONSOLE_WIDTH * CONSOLE_DEPTH],
		CONSOLE_DEPTH * CONSOLE_WIDTH * ( CONSOLE_HEIGHT - tmp ) );
	uint16 blank = ((uint16)attrib << 8) | CHAR_SPACE;
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

void putch( uint8 ch )
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
				uint8 *cur = &vidmem[(cur_y * CONSOLE_WIDTH + cur_x) * CONSOLE_DEPTH];
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

void puts( const uint8 *s )
{
	uint32 i = 0, n = strlen( s );
	while ( i < n ) putch( s[i++] );
}
