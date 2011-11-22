/**
 * @file vga_text.c
 * VGA_Text native device driver interface.
 *
 * Copyright (c) 2008, Steve Denson
 * See end of file for terms of use.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <propeller.h>

//#define TV
//#define VGA

#define C3

#if defined(TV)
#include "term_tv.h"
#elif defined (VGA)
#include "term_vga.h"
#else
#include "term_serial.h"
#endif

#ifdef C3
#define TVPIN	12
#define VGAPIN	16
#else
#define TVPIN	0
#define VGAPIN	8
#endif

int main(void)
{
#if defined(TV)
	TERM_TV tvTerm;
#elif defined(VGA)
	TERM_VGA vgaTerm;
#else
	TERM_SERIAL serialTerm;
#endif
	TERM *term;
    int ii = 85;
    int jj = 0;
    
#if defined(TV)
	term = tvTerm_start(&tvTerm, TVPIN); 
#elif defined(VGA)
	term = vgaTerm_start(&vgaTerm, VGAPIN); 
#else
	term = serialTerm_start(&serialTerm, stdout);
#endif

#if defined(C3) && !defined(TV)
    DIRA |= 1<<15;
    OUTA &= ~(1<<15);
#endif
    
#if !defined(TV) && !defined(VGA)
	Term_str(term, "Hello, world!\n");
#else
	Term_print(term, "\nzoot ");
    Term_print(term, "color");
    Term_setXY(term, 0,0);
    Term_print(term, "Hi\n");
    Term_print(term, "zoot");
    Term_setCoordPosition(term, 1,3);
    Term_print(term, "abcd");
    Term_setCurPosition(term, 5,5);
    
    Term_print(term, "Hello World!\r");
    Term_setY(term, Term_getY(term)+1);
    Term_str(term, "Decimal ");
    Term_dec(term, ii);
    Term_setY(term, Term_getY(term)+1);

    for(jj = 10; jj < 20; jj++) {
        Term_setColors(term, (jj-10));
        Term_setXY(term, jj, jj % Term_getRows(term));
        Term_str(term, "0x");
        Term_hex(term, ii++, 4);
    }
#endif

    while(1);
}

/*
+------------------------------------------------------------------------------------------------------------------------------+
�                                                   TERMS OF USE: MIT License                                                  �                                                            
+------------------------------------------------------------------------------------------------------------------------------�
�Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation    � 
�files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,    �
�modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software�
�is furnished to do so, subject to the following conditions:                                                                   �
�                                                                                                                              �
�The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.�
�                                                                                                                              �
�THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE          �
�WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR         �
�COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   �
�ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                         �
+------------------------------------------------------------------------------------------------------------------------------+
*/
