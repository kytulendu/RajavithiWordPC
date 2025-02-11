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

/* Message is in Kaset (�ɵ�) Thai character encoding.
 * Don't change the message if your text editor can't display the text correctly. */
const char msg_banner1[] = "�����������������������������������";
const char msg_banner2[] = "�                                 �";
const char msg_banner3[] = "�       ����Կң��ʿ���г���        �";        /* �������ä��������� */
const char msg_banner4[] = "�         �����θ���Ψ�ٴ�          �";        /* �ç��Һ���Ҫ�Զ� */
const char msg_banner5[] = "��� �Ψ�ٴ�  WORD PC   version 1.2 ��";    /* �Ҫ�Զ�  WORD PC   version 1.2 */

const char msg_mainmenu[] = "<MAIN MENU>";
const char msg_menu1[] = "(1)  ���Υ ���� ѡ�Ԣ FILE            (2)  �ٿ�� FILE"; /* "      (1)  ���ҧ ���� ��� FILE            (2)  ����� FILE" */
const char msg_menu2[] = "(3)  DOS COMMAND                   (4)  EXIT";

const char msg_select[] = "ҹ�����ʡ : ";  /* "�ô���͡ : " in KU code. */

const char msg_anykey[] = "PRESS ANY KEY TO CONTINUE :";

/* ======================================================================== */

/** Display menu. */
void dispmenu()
{
    /* Rajavithi Word PC banner and version info. */
    setputattr(HIGHLIGHTATTR);
    gotoxy(21, 0);
    tputstr(msg_banner1);
    gotoxy(21, 1);
    tputstr(msg_banner2);
    gotoxy(21, 3);
    tputstr(msg_banner2);
    gotoxy(21, 2);
    tputstr(msg_banner3);
    gotoxy(21, 4);
    tputstr(msg_banner4);
    gotoxy(21, 5);
    tputstr(msg_banner2);
    gotoxy(21, 6);
    tputstr(msg_banner5);

    /* <MAIN MENU> */
    setputattr(NORMALATTR);
    gotoxy(33, 11);
    tputstr(msg_mainmenu);

    /* Menu list */
    gotoxy(15, 13);
    tputstr(msg_menu1);
    gotoxy(15, 15);
    tputstr(msg_menu2);

    /* Please select */
    gotoxy(9, 19);
    tputstr(msg_select);
    gotoxy(20, 19);
}

/** Main function. */
int main()
{
    char ch;
    int run = 1;

    clrscr();

    dispmenu();

    /* Loop for keyboard input. */
    do
    {
        /* Get keyboard input character. */
        ch = getch();

        gotoxy(24, 17);

        switch (ch)
        {
            case '1':
                if (spawnlp(P_WAIT, "RWMAIN.COM", "RWMAIN.COM", NULL) == -1)
                {
                    if (spawnlp(P_WAIT, "RWMAIN.EXE", "RWMAIN.EXE", NULL) == -1)
                    {
                        puts("Cannot find file : RWMAIN");
                        getch();
                    }
                }
                clrscr();
                dispmenu();
                break;
            case '2':
                if (spawnlp(P_WAIT, "NLQ.EXE", "NLQ.EXE", NULL) == -1)
                {
                    puts("  Cannot find file : NLQ.EXE ");
                    getch();
                }
                clrscr();
                dispmenu();
                break;
            case '3':
                puts("        Not implemented.     ");
                getch();
                clrscr();
                dispmenu();
                break;
            case '4':
            case 27:                                /* escape key */
                run = 0;
                break;
            default:
                puts("  Please select number 1-4   ");
        }

        gotoxy(20, 19);

    } while (run);

    exit(0);
}
