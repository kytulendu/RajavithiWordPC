/*
 * Rajavithi Word PC 1.2 Main Menu Re-Creation.
 * Copyright (c) 2017 Khralkatorrix <https://github.com/kytulendu>
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

/* ============================ */
/*           Defines            */
/* ============================ */

#define MAXCOL              80

/* ASCII character code. */
#define SPACE               0x20

#define SaraU               0xd7                /* สระอุ */
#define SaraIe              0xd9                /* สระอิ */
#define SaraE               0xda                /* สระอี */
#define SaraUe              0xdb                /* สระอึ */
#define SaraUee             0xdc                /* สระอือ */
#define MaiHunAkad          0xdd                /* ไม้หันอากาศ */
#define Nikkhahit           0xde                /* นิคหิต */
#define MaiEk               0xe0                /* ไม้เอก */
#define Karan               0xe4                /* การันต์ */

/* Character attribute. */
#define NORMALATTR          0x07
#define HIGHLIGHTATTR       0x0f

/* ============================ */
/*        Message Area          */
/* ============================ */

/* Don't change the message if your text editor can't display the text correctly. */
const char msg_banner1[] = "•—";
const char msg_banner2[] = "                                 ";
const char msg_banner3[] = "       จฟมฟิฟาฃมฃสฟผูฤะณสมไ        ";        /* ชมรมไมโครคอมพิวเตอร์ */
const char msg_banner4[] = "         ามฅผภฮธฮรมฮจฤูดฺ          ";        /* โรงพยาบาลราชวิถี */
const char msg_banner5[] = " มฮจฤูดฺ  WORD PC   version 1.2 ";    /* ราชวิถี  WORD PC   version 1.2 */

const char msg_mainmenu[] = "<MAIN MENU>";
const char msg_menu1[] = "(1)  วมแฮฅ ศมÜส ักแิข FILE            (2)  ผูฟผไ FILE"; /* "      (1)  สร้าง หรือ แก้ไข FILE            (2)  พิมพ์ FILE" */
const char msg_menu2[] = "(3)  DOS COMMAND                   (4)  EXIT";

const char msg_select[] = "านมฒะรÜสก : ";  /* "โปรดเลือก : " in KU code. */

const char msg_anykey[] = "PRESS ANY KEY TO CONTINUE :";

/* ============================ */
/*         Table Area           */
/* ============================ */

/* Offset of middle character in 8 line Thai display. */
const int lineoffset[] = {
    1, 4, 7, 10, 13, 16, 19, 22
};

/* สระอิ combined character. */
const char combined_SaraIe_table[] = {
    0x0ee, 0x0ef, 0x0f0, 0x0f1, 0x0f2
};

/* สระอี combined character. */
const char combined_SaraE_table[] = {
    0x0f3, 0x0f4, 0x0f5, 0x0f6,
};

/* สระอึ combined character. */
const char combine_SaraUe_table[] = {
    0x0f7, 0x0f8, 0x0f9, 0x0fa,
};

/* สระอือ combined character. */
const char combined_SaraUee_table[] = {
    0x0fb, 0x0fc, 0x0fd, 0x0fe,
};

/* ไม้หันอากาศ combined character. */
const char combined_MaiHunAkad_table[] = {
    0x0ea, 0x0eb, 0x0ec, 0x0ed,
};

/* นิคหิต combined character. */
const char combined_Nikkhahit_table[] = {
    0x0e6, 0x0e7, 0x0e8, 0x0e9,
};

/* ============================ */
/*       Global Variable        */
/* ============================ */

/* Cursor position, used for display thai strings. */
int x_pos = 0;
int y_pos = 0;

/* Character attribute. */
char attr;

/* Flag indicate upper/combined character.
*  0 = middle, 1 = upper, 2 = combined upper character */
int upperflag = 0;

/* Previous upper character, using in combined character. */
char prev_char;

/* ======================================================================== */

/** Move cursor to given position on the screen. */
void gotoxy( int p_col, int p_row ) {
    union REGS r;

    r.h.ah = 0x02;          /* Set cursor position */
    r.h.bh = 0x00;          /* Page */
    r.h.dh = p_row;         /* Row */
    r.h.dl = p_col;         /* Column */
    int86( 0x10, &r, &r );  /* BIOS video service */
}

/** Clear the screen by scroll the screen up. */
void clrscr( ) {
    union REGS r;

    r.h.ah = 0x06;          /* Scroll the screen up */
    r.h.al = 0x00;          /* Clear entire screen */
    r.h.bh = 0x7;           /* Normal video attribute */
    r.w.cx = 0x0000;        /* Upper left corner is (0, 0) */
    r.w.dx = 0x184f;        /* Lower right corner is (4fh, 18h) */
    int86( 0x10, &r, &r );  /* BIOS video service */
}

/** Write given character to video memory.
*   \param[in]  p_char          Character to print.
*   \param[in]  p_attr          Character attribute.
*   \param[in]  p_col           Vertical position.
*   \param[in]  p_row           Horizontal position. */
void prnchar( register char p_char, register char p_attr, int p_col, int p_row ) {
    char far* scrn = ( char far* ) 0xb8000000UL;
    int offset = ( ( p_row * 0x50 + p_col ) * 2 ) /*+ ( pagenum * 0x1000 )*/;

    scrn[offset] = p_char;
    scrn[offset + 1] = p_attr;
}

/** Write given character in middle level.
*   \param[in]  p_char          Character to print. */
void putmiddle( char p_char ) {
    prnchar( p_char, attr, x_pos, y_pos );
    x_pos = x_pos + 1;
    upperflag = 0;
}

/** Write given character in under level.
*   \param[in]  p_char          Character to print. */
void putunder( char p_char ) {
    y_pos = y_pos - 1 / 80;
    prnchar( p_char, attr, x_pos - 1, y_pos + 1 );
}

/** Write given character in upper level.
*   \param[in]  p_char          Character to print. */
void putupper( char p_char ) {
    prnchar( p_char, attr, x_pos - 1, y_pos - 1 );
}

/** Find combined character code of given upper character.
*   \param[in]  p_old           Previous upper character code.
*   \param[in]  p_new           Current upper character code.
*   \return char                Combined upper character code. */
char combinechar( char p_prev, char p_new ) {
    char newch;
    char tmp_new;

    if ( ( p_prev >= SaraIe && p_prev <= Nikkhahit )    /* if p_prev is sara */
        && p_new >= MaiEk && p_new <= Karan ) { /* if p_new is wannayuk */

        tmp_new = p_new - MaiEk;

        switch ( p_prev ) {
        case SaraIe:                            /* สระอิ */
            newch = combined_SaraIe_table[tmp_new];
            break;
        case SaraE:                             /* สระอี */
            if ( p_new != Karan ) {
                newch = combined_SaraE_table[tmp_new];
            } else {
                /* Invalid. */
            }
            break;
        case SaraUe:                            /* สระอึ */
            if ( p_new != Karan ) {
                newch = combine_SaraUe_table[tmp_new];
            } else {
                /* Invalid. */
            }
            break;
        case SaraUee:                           /* สระอือ */
            if ( p_new != Karan ) {
                newch = combined_SaraUee_table[tmp_new];
            } else {
                /* Invalid. */
            }
            break;
        case MaiHunAkad:                        /* ไม้หันอากาศ */
            if ( p_new != Karan ) {
                newch = combined_MaiHunAkad_table[tmp_new];
            } else {
                /* Invalid. */
            }
            break;
        case Nikkhahit:                         /* นิคหิต */
            if ( p_new != Karan ) {
                newch = combined_Nikkhahit_table[tmp_new];
            } else {
                /* Invalid. */
            }
            break;
        }


    } else {
        newch = 0x00;
        upperflag = 0;
    }

    return newch;
}

/** Write a Thai character to the screen.
*   \param[in]  p_string        String to print.
*   \param[in]  p_attr          String attribute. */
void tprnch( char p_char, char p_attr ) {
    attr = p_attr;

    /* Check if p_char is not control code. */
    if ( p_char >= SPACE ) {

        /* a character code is less than สระอุ */
        if ( p_char < SaraU ) {
            putmiddle( p_char );

        /* a character code is less than สระอิ */
        } else if ( p_char < SaraIe ) {
            putunder( p_char );

        /* a character code is equal or more than สระอิ and less than การันต์ */
        } else if ( p_char >= SaraIe && p_char <= Karan ) {
            upperflag = upperflag + 1;

            if ( upperflag == 1 ) {
                putupper( p_char );
                prev_char = p_char;
            } else if ( upperflag == 2 ) {
                putupper( combinechar( prev_char, p_char ) );
            } else {
                /* Invalid. */
            }
        }
    }
}

/** Write given Thai string to the screen.
*   \param[in]  p_string        String to print.
*   \param[in]  p_attr          String attribute.
*   \param[in]  p_col           Vertical position.
*   \param[in]  p_row           Horizontal position. */
void tprnstr( const char* p_string, char p_attr, int p_col, int p_row ) {
    /* Set the x_pos, y_pos global variable. */
    x_pos = p_col;
    y_pos = p_row;

    while ( ( *p_string != '\0' ) && ( p_col < MAXCOL ) ) {
        /* Wait for vertical retrace (vsync). */
        while ( ( inp( 0x03da ) & 1 ) == 0 );
        while ( ( inp( 0x03da ) & 1 ) != 0 );

        /* Write a character at given position. */
        tprnch( *p_string, p_attr );
        p_string++;
    }
}

/** Display menu. */
void dispmenu( ) {
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
int main( ) {
    char ch;
    int run = 1;

    clrscr( );

    dispmenu( );

    /* Loop for keyboard input. */
    do {
        /* Get keyboard input character. */
        ch = getch( );

        gotoxy( 24, 17 );

        switch ( ch ) {
        case '1':
            if ( spawnlp( P_WAIT, "RWMAIN.COM", "RWMAIN.COM", NULL ) == -1 ) {
                puts( "Cannot find file : RWMAIN.COM" );
                getch( );
            }
            clrscr( );
            dispmenu( );
            break;
        case '2':
            if ( spawnlp( P_WAIT, "NLQ.EXE", "NLQ.EXE", NULL ) == -1 ) {
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
