#ifndef __SYSTEM_H_INCLUDE

#define __SYSTEM_H_INCLUDE

/* SYSTEM.C */
extern void *k_memcpy( void *dst, const void *src, unsigned int count );
extern unsigned char *k_memset( unsigned char *dst, unsigned char val, unsigned int count );
extern unsigned int k_strlen( const unsigned char *str );
extern unsigned char k_inportb( unsigned short _port );
extern void k_outportb( unsigned short _port, unsigned char _data );

#endif // __SYSTEM_H_INCLUDE
