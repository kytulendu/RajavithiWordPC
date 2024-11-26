/*
 * Rajavithi Word PC 1.2 Main Menu Re-Creation.
 * Copyright (c) 2017-2024 Khralkatorrix <https://github.com/kytulendu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <conio.h>
#include <i86.h>
#include <process.h>

#include "libthai.h"

/* ============================ */
/*        Message Area          */
/* ============================ */

/* Message is in Kaset (‡°…µ√) Thai character encoding.
 * Don't change the message if your text editor can't display the text correctly. */
const char msg_banner1[] = "ïûûûûûûûûûûûûûûûûûûûûûûûûûûûûûûûûûó";
const char msg_banner2[] = "ü                                 ü";
const char msg_banner3[] = "ü       ®ø¡ø‘ø“£¡£ øºŸƒ–≥ ¡‰        ü";        /* ™¡√¡‰¡‚§√§Õ¡æ‘«‡µÕ√Ï */
const char msg_banner4[] = "ü         “¡•º¿Œ∏Œ√¡Œ®ƒŸ¥⁄          ü";        /* ‚√ßæ¬“∫“≈√“™«‘∂’ */
const char msg_banner5[] = "õûû ¡Œ®ƒŸ¥⁄  WORD PC   version 1.2 ûù";    /* √“™«‘∂’  WORD PC   version 1.2 */

const char msg_mainmenu[] = "<MAIN MENU>";
const char msg_menu1[] = "(1)  «¡·Œ• »¡‹  —°·‘¢ FILE            (2)  ºŸøº‰ FILE"; /* "      (1)   √È“ß À√◊Õ ·°È‰¢ FILE            (2)  æ‘¡æÏ FILE" */
const char msg_menu2[] = "(3)  DOS COMMAND                   (4)  EXIT";

const char msg_select[] = "“π¡≤–√‹ ° : ";  /* "‚ª√¥‡≈◊Õ° : " in KU code. */

const char msg_anykey[] = "PRESS ANY KEY TO CONTINUE :";

/* ======================================================================== */

/** Display menu. */
void dispmenu( )
{
    /* Rajavithi Word PC banner and version info. */
    tprnstr( msg_banner1, HIGHLIGHTATTR, 21, 0 );
    tprnstr( msg_banner2, HIGHLIGHTATTR, 21, 1 );
    tprnstr( msg_banner2, HIGHLIGHTATTR, 21, 3 );
    tprnstr( msg_banner3, HIGHLIGHTATTR, 21, 2 );
    tprnstr( msg_banner4, HIGHLIGHTATTR, 21, 4 );
    tprnstr( msg_banner2, HIGHLIGHTATTR, 21, 5 );
    tprnstr( msg_banner5, HIGHLIGHTATTR, 21, 6 );

    /* <MAIN MENU> */
    tprnstr( msg_mainmenu, NORMALATTR, 33, 11 );

    /* Menu list */
    tprnstr( msg_menu1, NORMALATTR, 15, 13 );
    tprnstr( msg_menu2, NORMALATTR, 15, 15 );

    /* Please select */
    tprnstr( msg_select, NORMALATTR, 9, 19 );
    gotoxy( 20, 19 );
}

/** Main function. */
int main( )
{
    char ch;
    int run = 1;

    clrscr( );

    dispmenu( );

    /* Loop for keyboard input. */
    do
    {
        /* Get keyboard input character. */
        ch = getch( );

        gotoxy( 24, 17 );

        switch ( ch )
        {
            case '1':
                if ( spawnlp( P_WAIT, "RWMAIN.COM", "RWMAIN.COM", NULL ) == -1 )
                {
                    if ( spawnlp( P_WAIT, "RWMAIN.EXE", "RWMAIN.EXE", NULL ) == -1 )
                    {
                        puts( "Cannot find file : RWMAIN" );
                        getch( );
                    }
                }
                clrscr( );
                dispmenu( );
                break;
            case '2':
                if ( spawnlp( P_WAIT, "NLQ.EXE", "NLQ.EXE", NULL ) == -1 )
                {
                    puts( "  Cannot find file : NLQ.EXE " );
                    getch( );
                }
                clrscr( );
                dispmenu( );
                break;
            case '3':
                puts( "        Not implemented.     " );
                getch( );
                clrscr( );
                dispmenu( );
                break;
            case '4':
            case 27:                                /* escape key */
                run = 0;
                break;
            default:
                puts( "  Please select number 1-4   " );
        }

        gotoxy( 20, 19 );

    } while ( run );

    exit( 0 );
}
