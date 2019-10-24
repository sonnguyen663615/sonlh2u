// game_snack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<time.h>
#include <stdio.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include "console.h"
#include<MMsystem.h >
#define ngang 60
#define doc 30


struct ToaDo {
	int x, y;
};
enum trangthai { UP, DOWN, LEFT, RIGHT };
struct Snake {
	ToaDo dot[499];
	int n;
	trangthai tt;
};

struct Moi
{
	int x1, y1;
};


void KhoiTao(Snake & snake,Moi &moi) {
	snake.n = 1;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;
	snake.tt = RIGHT;
	moi.x1 = 10;
	moi.y1 = 20;
}
//hien thi
void HienThi(Snake snake,Moi moi) {
	clrscr();
	TextColor(7);
	for (int i = 0; i < doc; i++) {
		gotoXY(ngang, i);
		putchar(179);
	}
	TextColor(10);
	gotoXY(moi.x1, moi.y1);
	putchar('P');
	TextColor(13);
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar(2);
	for (int i = 1; i < snake.n; i++) {
		gotoXY(snake.dot[i].x,snake.dot[i].y);
		putchar('*');
	}

}
void DieuKhien_DiChuyen(Snake &snake) {
	for (int i = snake.n - 1; i > 0; i--) {
		snake.dot[i] = snake.dot[i - 1];
	}
	if (kbhit()) {
		char key = getch();
		if (key == 'A' || key == 'a')
			snake.tt = LEFT;
		else if (key == 'D' || key == 'd')
			snake.tt = RIGHT;
		else if (key == 'S' || key == 's')
			snake.tt = DOWN;
		else if (key == 'W' || key == 'w')
			snake.tt = UP;
		else if (key ==77)
			snake.tt = RIGHT;
		else if (key == 72)
			snake.tt = UP;
		else if (key == 80)
			snake.tt = DOWN;
		else if (key == 75)
			snake.tt = LEFT;
	}
	if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == LEFT)
		snake.dot[0].x--;
	else if (snake.tt == RIGHT)
		snake.dot[0].x++;
	//if(snake.dot[0].x==ngang-1)
}

int  Xuli(Snake& snake, Moi& moi,int &s) {
	if (snake.dot[0].x == moi.x1 && snake.dot[0].y == moi.y1) {
		for(int i= snake.n;i>0;i-- )
			snake.dot[i]=snake.dot[i-1];
		snake.n++;
		if (snake.tt == DOWN)
			snake.dot[0].y++;
		else if (snake.tt == UP)
			snake.dot[0].y--;
		else if (snake.tt == LEFT)
			snake.dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.dot[0].x++;
		moi.x1 = rand() % ngang;
		moi.y1 = rand() % doc;
		if (s > 30)
			s = s - 20;
	}
	//game over
	if (snake.dot[0].x<0 || snake.dot[0].x>ngang || snake.dot[0].y<0 || snake.dot[0].y>doc)
		return -1;
	for (int i = 1; i < snake.n; i++)
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
			return -1;
}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void setCursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
//tat con tro nhap nhay
int main()
{
	PlaySound(TEXT("son.wav"), NULL, SND_ASYNC);
	char ten[99];
	printf("nhap ten cua ban : ");
	scanf("%s", &ten);
	srand(time(NULL));
	Snake snake;
	Moi moi;
	int ma;
	int s = 200;
	KhoiTao(snake,moi);
	setCursor(0, 1);//ham tat dau nhay 
	while (1) {
		//hien thi
		HienThi(snake ,moi);

		//dieu khien 
		DieuKhien_DiChuyen(snake);
		//xu li
		ma =Xuli(snake, moi,s);
		//thua game hoac thang game
		if (ma ==-1) {
			gotoXY(ngang + 1, 10);
			printf("GAME OVER .%s BAN LA 1 CON GA\n ",ten);
			printf("SON VAN 2711");

			while (getch() != 13);
				
			break;
		}
		Sleep(s);
	}
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file