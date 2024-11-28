/*
 * Thai 8 line text mode library.
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

/* English to Thai conversion from character get from keyboard.
 * Output is in Kaset character encoding. */
const char thai_keyboard_table[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x2e, 0x5f, 0x32, 0x33, 0x34, 0xeb, 0xa5, 0x36, 0x37, 0x35, 0x39, 0xbf, 0xa2, 0xd3, 0xbb,
    0xa6, 0xc3, 0x2d, 0x2f, 0xbe, 0xb4, 0xd7, 0xdb, 0xa3, 0xb3, 0xa9, 0xc4, 0xb0, 0xa8, 0xc9, 0xde,
    0x31, 0xc2, 0x3f, 0xa7, 0xac, 0xad, 0xd2, 0xaa, 0xdf, 0xb1, 0xe3, 0xc6, 0xc5, 0x2c, 0xe4, 0xd6,
    0xab, 0x30, 0xaf, 0xa4, 0xb6, 0xe2, 0xcb, 0x22, 0x29, 0xe3, 0x28, 0xb8, 0x00, 0xc3, 0xd8, 0x38,
    0x00, 0xbd, 0xd9, 0xd1, 0xa1, 0xcf, 0xb2, 0xd0, 0xe1, 0xc1, 0xe0, 0xce, 0xc7, 0xb5, 0xdc, 0xb7,
    0xc0, 0xd5, 0xbc, 0xc8, 0xcc, 0xda, 0xca, 0xd4, 0xb9, 0xdd, 0xba, 0xae, 0x00, 0x2c, 0x00, 0x00
};

/* ============================ */
/*       Private Variable       */
/* ============================ */

/* Cursor position, used for display thai strings. */
int x_pos = 0;
int y_pos = 0;

/* Character attribute. */
char char_attr = NORMALATTR;

/* Flag indicate level of character.
 *  0 = lower, 1 = middle, 2 = upper, 3 = combined upper character
 */
int level_flag = 0;

/* Previous upper character, using in combined character. */
char prev_char = 0x00;

/* Flag indicate keyboard input mode.
 * 0 = English, 1 = Thai
 */
int mode_flag = 0;

int good_char = 1;

/* ============================ */
/*  Private Function Prototype  */
/* ============================ */

/** Change cursor shape to big rectangle, indicate Thai input */
void tcursor();

/** Change cursor shape to small rectangle, indicate English input */
void ecursor();

/** Write given character to video memory directly.
 *  \param[in]  p_char          Character to print.
 *  \param[in]  p_attr          Character attribute.
 *  \param[in]  p_col           Vertical position.
 *  \param[in]  p_row           Horizontal position.
 */
void prnchar(register char p_char, register char p_attr, int p_col, int p_row);

/** Write given character in middle level.
 *  \param[in]  p_char          Character to print.
 */
void putmiddle(char p_char);

/** Write given character in under level.
 *  \param[in]  p_char          Character to print.
 */
void putunder(char p_char);

/** Write given character in upper level.
 *  \param[in]  p_char          Character to print.
 */
void putupper(char p_char);

/** Find combined character code of given upper character.
 *  \param[in]  p_old           Previous upper character code.
 *  \param[in]  p_new           Current upper character code.
 *  \return char                Combined upper character code.
 */
char combinechar(char p_prev, char p_new);

/* ======================================================================== */

void gotoxy(int p_col, int p_row)
{
    union REGS r;

    r.h.ah = 0x02;          /* Set cursor position */
    r.h.bh = 0x00;          /* Page */
    r.h.dh = p_row;         /* Row */
    r.h.dl = p_col;         /* Column */
    int86(0x10, &r, &r);    /* BIOS video service */
}

int wherex()
{
    union REGS r;

    r.h.ah = 0x03;          /* Set cursor position */
    r.h.bh = 0x00;          /* Page */
    int86(0x10, &r, &r);    /* BIOS video service */
    return r.h.dl;          /* Column */
}

int wherey()
{
    union REGS r;

    r.h.ah = 0x03;          /* Set cursor position */
    r.h.bh = 0x00;          /* Page */
    int86(0x10, &r, &r);    /* BIOS video service */
    return r.h.dh;          /* Row */
}

void scrollup(char p_line)
{
    union REGS r;

    r.h.ah = 0x06;          /* Scroll the screen up */
    r.h.al = p_line;        /* Number of lines to scroll */
    r.h.bh = 0x7;           /* Normal video attribute */
    r.w.cx = 0x0000;        /* Upper left corner is (0, 0) */
    r.w.dx = 0x184f;        /* Lower right corner is (4fh, 18h) */
    int86(0x10, &r, &r);    /* BIOS video service */
}

void scrolldown(char p_line)
{
    union REGS r;

    r.h.ah = 0x07;          /* Scroll the screen down */
    r.h.al = p_line;        /* Number of lines to scroll */
    r.h.bh = 0x7;           /* Normal video attribute */
    r.w.cx = 0x0000;        /* Upper left corner is (0, 0) */
    r.w.dx = 0x184f;        /* Lower right corner is (4fh, 18h) */
    int86(0x10, &r, &r);    /* BIOS video service */
}

void clrscr()
{
    union REGS r;

    r.h.ah = 0x06;          /* Scroll the screen up */
    r.h.al = 0x00;          /* Clear entire screen */
    r.h.bh = 0x7;           /* Normal video attribute */
    r.w.cx = 0x0000;        /* Upper left corner is (0, 0) */
    r.w.dx = 0x184f;        /* Lower right corner is (4fh, 18h) */
    int86(0x10, &r, &r);    /* BIOS video service */
}

void tcursor()
{
    outp(0x3d4, 0x0a);
    outp(0x3d5, 0x02);
}

void ecursor()
{
    outp(0x3d4, 0x0a);
    outp(0x3d5, 0x0b);
}

void beep()
{
    sound(1000);
    delay(200);
    nosound();
}

void prnchar(register char p_char, register char p_attr, int p_col, int p_row)
{
    char far* scrn = (char far*) 0xb8000000UL;/* CGA/VGA text mode VRAM */
    int offset = ((p_row * 0x50 + p_col) * 2) /*+ (pagenum * 0x1000)*/;

    scrn[offset] = p_char;
    scrn[offset + 1] = p_attr;
}

void setputattr(char p_attr)
{
    char_attr = p_attr;
}

void putcha(register char p_char)
{
    union REGS r;

    r.h.ah = 0x09;          /* Write a character at cursor position */
    r.h.al = p_char;        /* Character to display */
    r.h.bh = 0x00;          /* Page */
    r.h.bl = char_attr;     /* Attribute */
    r.w.cx = 1;             /* Number of times to write character */
    int86(0x10, &r, &r);    /* BIOS video service */
}

void putmiddle(char p_char)
{
    gotoxy(x_pos, y_pos);
    putcha(p_char);
    x_pos = x_pos + 1;
    gotoxy(x_pos, y_pos);
}

void putunder(char p_char)
{
    gotoxy(x_pos - 1, y_pos + 1);
    putcha(p_char);
    gotoxy(x_pos, y_pos);
}

void putupper(char p_char)
{
    gotoxy(x_pos - 1, y_pos - 1);
    putcha(p_char);
    gotoxy(x_pos, y_pos);
}

char combinechar(char p_prev, char p_new)
{
    char newch;
    char tmp_new;

    if (((p_prev >= SaraIe) && (p_prev <= Nikkhahit)) &&    /* if p_prev is sara */
        ((p_new >= MaiEk) && (p_new <= Karan)))             /* if p_new is wannayuk */
    {
        tmp_new = p_new - MaiEk;

        switch (p_prev)
        {
            case SaraIe:                            /* สระอิ */
                newch = combined_SaraIe_table[tmp_new];
                break;
            case SaraE:                             /* สระอี */
                if (p_new != Karan)
                {
                    newch = combined_SaraE_table[tmp_new];
                }
                break;
            case SaraUe:                            /* สระอึ */
                if (p_new != Karan)
                {
                    newch = combine_SaraUe_table[tmp_new];
                }
                break;
            case SaraUee:                           /* สระอือ */
                if (p_new != Karan)
                {
                    newch = combined_SaraUee_table[tmp_new];
                }
                break;
            case MaiHunAkad:                        /* ไม้หันอากาศ */
                if (p_new != Karan)
                {
                    newch = combined_MaiHunAkad_table[tmp_new];
                }
                break;
            case Nikkhahit:                         /* นิคหิต */
                if (p_new != Karan)
                {
                    newch = combined_Nikkhahit_table[tmp_new];
                }
                break;
        }
    }
    else
    {
        newch = 0x00;
        level_flag = 1;
        good_char = 0;
        beep();
    }

    return newch;
}

void tputch(char p_char)
{
    /* Check if p_char is not control code. */
    if (p_char >= SPACE)
    {
        /* a character code is less than สระอุ */
        if (p_char < SaraU)
        {
            putmiddle(p_char);
            level_flag = 1;
            prev_char = p_char;
        }
        /* a character code is สระอุ and สระอู */
        else if ((p_char == SaraU) || (p_char == SaraUu))
        {
            if (level_flag == 1)
            {
                if ((prev_char >= KoKai) && (prev_char <= HoNokHuk))
                {
                    putunder(p_char);
                    level_flag = 0;
                }
                else
                {
                    good_char = 0;
                    beep();
                }
            }
            else
            {
                good_char = 0;
                beep();
            }
        }
        /* a character code is equal or more than สระอิ and less than การันต์ */
        else if (p_char >= SaraIe && p_char <= Karan)
        {
            if (level_flag == 0)
            {
                if ((p_char >= MaiEk) && (p_char < Karan))        /* if p_new is wannayuk */
                {
                    putupper(p_char);
                    prev_char = p_char;
                    level_flag = 2;
                }
            }
            else if (level_flag == 1)
            {
                putupper(p_char);
                prev_char = p_char;
                level_flag = 2;
            }
            else if (level_flag == 2)
            {
                if ((prev_char != p_char) &&
                    ((prev_char != MaiTaiKhu) || (prev_char != Karan)))
                {
                    putupper(combinechar(prev_char, p_char));
                    level_flag = 3;
                }
                else
                {
                    good_char = 0;
                    beep();
                }
            }
            else        /* level_flag == 3 */
            {
                good_char = 0;
                beep();
            }
        }
    }
}

void tputstr(const char* p_string)
{
    /* Set the x_pos, y_pos global variable. */
    x_pos = wherex();
    y_pos = wherey();

    while (*p_string != '\0')
    {
        /* Wait for vertical retrace (vsync). */
        while ((inp(0x03da) & 1) == 0);
        while ((inp(0x03da) & 1) != 0);

        /* Write a character at given position. */
        tputch(*p_string);
        p_string++;
    }
}

char tgetch()
{
    int ch;

    do {
        ch = getch();
        if (ch == ESC)
        {
            mode_flag = !mode_flag;
            if (mode_flag)
                tcursor();
            else
                ecursor();
        }
    } while (ch == ESC);

    return (mode_flag ? thai_keyboard_table[ch] : ch);
}

unsigned char idx;

void tdelch(char* p_string)
{
    char ch;
    if (idx > 0)
    {
        idx = idx - 1;
        ch = p_string[idx];
        if (ch < SaraU)
        {
            x_pos = x_pos - 1;
            gotoxy(x_pos, y_pos);
            putcha(SPACE);
            gotoxy(x_pos, y_pos);
        }
        else if (ch < SaraIe)
        {
            putunder(SPACE);
        }
        else
        {
            putupper(SPACE);
            ch = p_string[idx - 1];
            if (ch >= SaraIe)
            {
              putupper(ch);
              level_flag = 2;
              prev_char = ch;
            }
            else
            {
                level_flag = 1;
            }
        }
    }
}

void tgetstr(char* p_string, int p_length)
{
    char ch;

    idx = 0;
    mode_flag = 0;

    x_pos = wherex();
    y_pos = wherey();

    while (ch != CR) {
        good_char = 1;
        ch = tgetch();
        tputch(ch);

        if (!good_char)
        {
            ch = p_string[idx - 1];
            if ((ch == SaraU) || (ch == SaraUu))
            {
                gotoxy(x_pos, y_pos);
                level_flag = 0;
            }
            else if ((ch >= SaraIe) && (ch <= Karan))
            {
                prev_char = ch;
                ch = p_string[idx - 2];
                if ((ch >= SaraIe) && (ch <= Nikkhahit))
                {
                    level_flag = 3;
                }
                else
                {
                    level_flag = 2;
                }
            }
            else
            {
                level_flag = 1;
            }
        }

        if ((ch >= SPACE) && good_char)
        {
            p_string[idx] = ch;
            idx = idx + 1;
        }
        else
        {
            switch (ch)
            {
                case BS:
                    tdelch(p_string);
                    break;
            }
        }
    }
    p_string[idx] = '\0';
    ecursor();
}
