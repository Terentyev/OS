#include "system.h"

void *memcpy( void *dst, const void *src, unsigned int count )
{
	unsigned char *d = (unsigned char*) dst;
	unsigned char *s = (unsigned char*) src;
	while ( count-- )
		d[count] = s[count];
	return dst;
}

unsigned char *memset( unsigned char *dst, unsigned char val, unsigned int count )
{
	while ( count-- )
		dst[count] = val;
	return dst;
}

unsigned int strlen( const unsigned char *str )
{
	unsigned int l = 0;
	while ( str[l++] != '\0' ) ;
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
