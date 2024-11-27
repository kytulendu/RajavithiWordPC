#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "libthai.h"

char str[80];

int main( )
{
    clrscr();
    gotoxy(0,lineoffset[0]);
    tputstr("ÈÎ¡³áÊ¥¡ÎÁ¹áÊ·£Ï¾ÎÆÎÔµÀ ÓÈá¡²£ÚÀä ESC");
    gotoxy(0,lineoffset[1]);
    tputstr("ÑÃÌ¡²£ÚÀäĞ²ÚÀÄ¡İ··Úá ¡Ãİ¸Ğ¹ß·¾ÎÆÎÊİ¥¡ÂÆ");
    gotoxy(0,lineoffset[2]);
    setputattr(HIGHLIGHTATTR);
    tputstr("ÊÊ¡¦Î¡Ò¹ÁÑ¡Á¿·Úá²áÄÀ¡ÎÁ¡²£ÚÀä ENTER µÚà³á·¸ÁÁµİ²");
    gotoxy(0,lineoffset[3]);
    setputattr(NORMALATTR);
    do {
        tgetstr(str, 80);
        printf("\n\n\nstr[]: %s\n\n\n", str);
    } while (str[0] != NULL);

    exit(0);
}
