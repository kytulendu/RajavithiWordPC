#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "libthai.h"

char str[80];

int main( )
{
    clrscr();
    gotoxy(0,lineoffset[0]);
    tputstr("�Ρ��ʥ�����ʷ�Ͼ���Ե� ��ᡲ���� ESC");
    gotoxy(0,lineoffset[1]);
    tputstr("��̡�����в��ġݷ��� ��ݸй߷�����ݥ���");
    gotoxy(0,lineoffset[2]);
    setputattr(HIGHLIGHTATTR);
    tputstr("�ʡ�Ρҹ�ѡ����������������� ENTER ���᷸���ݲ");
    gotoxy(0,lineoffset[3]);
    setputattr(NORMALATTR);
    do {
        tgetstr(str, 80);
        printf("\n\n\nstr[]: %s\n\n\n", str);
    } while (str[0] != NULL);

    exit(0);
}
