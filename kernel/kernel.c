#include "system.h"

int main()
{
	clear_screen();
	print2screen( "Hello, world!", 0, 0, encodecolor(CLR_BLACK, CLR_WHITE) );
	for ( ;; ) ;
	return 0;
}
