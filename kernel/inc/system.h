#ifndef __SYSTEM_H_INCLUDE

#define __SYSTEM_H_INCLUDE

/* SYSTEM.C */
extern void *memcpy( void *dst, const void *src, unsigned int count );
extern void *memset( void *dst, unsigned char val, unsigned int count );
extern unsigned int strlen( const unsigned char *str );
extern unsigned char inportb( unsigned short _port );
extern void outportb( unsigned short _port, unsigned char _data );

#endif // __SYSTEM_H_INCLUDE
