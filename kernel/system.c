#include "system.h"

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

unsigned int strlen( const unsigned char *str )
{
	unsigned int l = 0;
	while ( *str++ != '\0' ) ++l;
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

char encodecolor( char bkg, char frg )
{
	return bkg << 4 | frg;
}

void clear_screen()
{
	char *vidmem = (char*) VIDEO_RAM_ADDRESS;
	unsigned int i = 0;
	char color = encodecolor(CLR_BLACK, CLR_LIGHT_GREY);

	while ( i < CONSOLE_WIDTH * CONSOLE_HEIGHT * CONSOLE_DEPTH )
	{
		vidmem[i] = ' ';
		++i;
		vidmem[i] = color;
		++i;
	}
}

void print2screen( char *message, unsigned int row, unsigned int col, unsigned int color )
{
	char *vidmem = (char*) VIDEO_RAM_ADDRESS;
	unsigned int i = (row * CONSOLE_WIDTH + col) * CONSOLE_DEPTH;

	while ( i < CONSOLE_WIDTH * CONSOLE_HEIGHT * CONSOLE_DEPTH )
	{
		if ( *message == '\n' )
		{
			++row;
			i = row * CONSOLE_WIDTH * CONSOLE_DEPTH;
		}
		else
		{
			vidmem[i++] = *message;
			vidmem[i++] = color;
		}
		++message;
	}
}
