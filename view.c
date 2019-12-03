#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <unistd.h>
#include <wchar.h>
#include <fcntl.h>
#include "view.h"
const int red = 4;
const int white = 7;
void textcolor(int color, int bg){
    CONSOLE_SCREEN_BUFFER_INFO buffer;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &buffer);

	SetConsoleTextAttribute(h,color + (bg << 4));
}

void ChangePosition(int column, int line){
    COORD where;
    where.X = column;
    where.Y = line;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(h, where))
    {
       printf("something went wrong");
    }
}
void Draw(card* Card, int x, int y) {
    const int red= 4;
    const int white= 7;
	char znak;
	char symbole[5] = { 'T','J','Q', 'K', 'A' };
	int wartosc;
	wartosc = (Card->power) + 2;
	if (wartosc >= 10) {
        if(wartosc%10<5){
		    znak = symbole[(wartosc % 10)];
        }
	}
	else{
        znak = 48+wartosc;
	}
	if (Card->color < 2) {
		textcolor(4, 7);
	}
	else {
		textcolor(0, 7);
	}
	ChangePosition(x, y);
	printf("%c       ",znak);
	y++;
	ChangePosition(x, y);
	printf("  .--.  ");
	y++;
	ChangePosition(x, y);
	printf("  (\\/)  ");
	y++;
	ChangePosition(x, y);
	printf("  :\\/:  ");
	y++;
	ChangePosition(x, y);
	printf("  '--'  ");
	y++;
	ChangePosition(x, y);
	printf("       %c",znak);
	if(Card->color==1){
        ChangePosition(x+2, y-3);
        printf(":/\\:");
        ChangePosition(x+2, y-2);
        printf(":\\/:");
	}
	if(Card->color==2){
        ChangePosition(x+2, y-3);
        printf(":/\\:");
        ChangePosition(x+2, y-2);
        printf("(__)");
	}
	if(Card->color==3){
        ChangePosition(x+2, y-3);
        printf(":():");
        ChangePosition(x+2, y-2);
        printf("()()");
	}
	ChangePosition(x+2, y+6);
}
void DrawBattle (card* A, card*B){
    Draw(A,10,5);
    textcolor(7,0);
    Draw(B,26,5);
}
void DrawBack(int x, int y){
    int back1 = 176;
    int back = 177;
    textcolor(10,0);
    ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back1,back1,back1,back1,back1,back1,back1);
	y++;
	ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back,back,back,back,back,back,back1);
	y++;
	ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back,back,back,back,back,back,back1);
	y++;
	ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back,back,back,back,back,back,back1);
	y++;
	ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back,back,back,back,back,back,back1);
	y++;
	ChangePosition(x, y);
	printf("%c%c%c%c%c%c%c%c",back1,back1,back1,back1,back1,back1,back1,back1);
	ChangePosition(x+2, y+6);
}
void DrawWar (card* A, card* B, int x, int y){
    DrawBack(x+2,y+2);
    DrawBack(x+18,y+2);
    Draw(A,x+4,y+4);
    Draw(B,x+20,y+4);
    ChangePosition(10, 20);
}