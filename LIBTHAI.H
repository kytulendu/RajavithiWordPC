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

#if !defined(__LIBTHAI_H)
#define __LIBTHAI_H

/* ============================ */
/*           Defines            */
/* ============================ */

#define MAXCOL              80

/* ASCII character code. */
#define BS                  0x08
#define LF                  0x0a
#define CR                  0x0d
#define ESC                 0x1b
#define SPACE               0x20

#define SaraU               0xd7                /* สระอุ */
#define SaraUu              0xd8                /* สระอู */
#define SaraIe              0xd9                /* สระอิ */
#define SaraE               0xda                /* สระอี */
#define SaraUe              0xdb                /* สระอึ */
#define SaraUee             0xdc                /* สระอือ */
#define MaiHunAkad          0xdd                /* ไม้หันอากาศ */
#define Nikkhahit           0xde                /* นิคหิต */
#define MaiTaiKhu           0xdf                /* ไม้ไต่คู้ */
#define MaiEk               0xe0                /* ไม้เอก */
#define Karan               0xe4                /* การันต์ */

/* Character attribute. */
#define NORMALATTR          0x07
#define HIGHLIGHTATTR       0x0f

/* ============================ */
/*         Table Area           */
/* ============================ */

extern const int lineoffset[];

/* ============================ */
/*  Public Function Prototype   */
/* ============================ */

/** Move cursor to given position on the screen.
 *  \param[in]  p_col           Column.
 *  \param[in]  p_row           Row.
 */
void gotoxy(int p_col, int p_row);

/** Get row position of the cursor.
*   \return int                 Cursor position.
 */
int wherex();

/** Get column position of the cursor.
*   \return int                 Cursor position.
 */
int wherey();

/** Clear the screen by scroll the screen up. */
void clrscr();

/** Emit a beep sound */
void beep();

/** Write a character at current cursor position.
 *  \param[in]  p_char          Character to print.
 *  \param[in]  p_attr          Character attribute.
 */
void putcha(register char p_char, register char p_attr);

/** Write a Thai character to the screen.
 *  \param[in]  p_char          Character to print.
 */
void tputch(char p_char);

/** Write given Thai string to the screen.
 *  \param[in]  p_string        String to print.
 */
void tputstr(const char* p_string);

char tgetch();

void tgetstr(char* p_string, int p_length);

#endif  /* __LIBTHAI_H */
