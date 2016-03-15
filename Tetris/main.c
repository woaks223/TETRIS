#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#pragma warning (disable:4996)

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define MAP_X 11
#define MAP_Y 15
#define MAIN_X 3
#define MAIN_Y 1

#define ACTIVE_BLOCK -2 //현재 이동중인 블럭
#define CEILLING -1 //블럭이 이동할수 있는 위치는 0이나 음의 정수로 표현
#define EMPTY 0 
#define WALL 1     //블럭이 이동할수 없는 위치는 양의 정수로 표현
#define INACTIVE_BLOCK 2

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 

int new_block_on;
int main_cpy[MAP_Y][MAP_X];
int main_org[MAP_Y][MAP_X];
int b_x = (MAP_X / 2) - 1; //블럭의 x좌표
int b_y = 0; //블럭의 y좌표
int temp[4][4];
int key = 0;

int check_crash(int x, int y);
void key_ent();
void move_block(int key);
void map_reset();
void gotoxy(int x, int y);
void map();
char start();
void new_block();
int** block_turn(int block[4][4]);
void setcursortype(CURSOR_TYPE c);

void main() {
	char choice;
	setcursortype(NOCURSOR);
	choice = start();
	if (choice == '1') {
		map_reset();
		while (1) {
			map();
			if(new_block_on==1) new_block();
			key_ent();
			//move_block(DOWN);
		}
	}
	else {
		exit(1);
	}
	return;
}

void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
	void key_ent() {
	key = 0;
		if (kbhit()) {
			
			key = getch();

			if (key == 224) {
				
				do {
					key = getch();
				} while (key == 244);
				switch (key)
				{
				case DOWN: {
					if ((check_crash(b_x, b_y+1))==1) move_block(DOWN);
					break;
				}
				case RIGHT: {
					break;
				}
				case LEFT: {
					break;
				}
				case UP: {
					break;
				}
				default:
					break;
				}
			}
			else {
				printf("%d", key);
			}
			
		}
		
}
char start() {
	printf("                                                                           \n\n\n"); Sleep(50);
	printf("                                                ■■■                         \n"); Sleep(50);
	printf("       ■■■■■                ■■■■■    ■    ■             ■■       \n"); Sleep(50);
	printf("           ■      ■■■■          ■        ■■■      ■     ■    ■     \n"); Sleep(50);
	printf("           ■      ■                ■        ■■        ■    ■            \n"); Sleep(50);
	printf("           ■      ■■■■          ■        ■  ■      ■     ■           \n"); Sleep(50);
	printf("           ■      ■                ■        ■    ■    ■       ■■       \n"); Sleep(50);
	printf("                   ■■■■          ■        ■      ■  ■           ■     \n"); Sleep(50);
	printf("                                                           ■            ■    \n"); Sleep(50);
	printf("                                                                  ■    ■     \n"); Sleep(50);
	printf("                                                                    ■■       \n"); Sleep(50);
	printf("                             1. START                                          \n"); Sleep(50);
	printf("                             2. EXIT                                           \n"); Sleep(50);
	printf("                                                                               \n"); 
	char num=getch();
	system("cls");
	return num;
}
void map() {
		
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) {
				gotoxy(MAIN_X + j, MAIN_Y + i);
				switch (main_org[i][j])
				{
				case ACTIVE_BLOCK:{ //움직이고 있는 블럭
					printf("■");
					break;
				}
				case CEILLING: { //천장 모양
					printf(". ");
					break;
				}
				case EMPTY: { //빈 공간
					printf(" ");
					break;
				}
				case WALL: { //벽
					printf("▩");
					break;
				}
				case INACTIVE_BLOCK: {//이동이 끝난 블럭
					printf("□");
					break;
				}
				default:
					break;
				}
			}
		}
	}
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			main_cpy[i][j] = main_org[i][j];
		}
	}
}
void map_reset() {
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			main_org[i][j] = 0;
			main_cpy[i][j] = 100;
		}
	}
	for (int i = 0; i < MAP_Y; i++) {
		main_org[i][0] = WALL;
		main_org[i][MAP_X - 1] = WALL;
	}
	for (int j = 0; j < MAP_X; j++) {
		main_org[MAP_Y - 1][j] = WALL;
	}
	for (int i = 1; i < MAP_X-1; i++)
		main_org[2][i] = CEILLING;
	new_block();
}
void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void new_block() {
	int block[5][4][4] = {
		{ { 0,0,0,0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 } ,{ 0, 0, 0, 0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,1,0,0 } },
		{ { 0,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } },
		{ { 0,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } },
		{ { 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
	};

	int random_block;

	srand(time(NULL));

	random_block = rand() % 5;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			main_org[b_y + i][b_x + j] = block[random_block][i][j];
			temp[i][j] = block[random_block][i][j];
		}
	}
	
}
int check_crash(int x, int y) {
	int n = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp[i][j] == 1 && main_org[y + i][x + j]>0) 
				return n-1;
		}
	}
	return n;
}
void move_block(int key) {
	
	switch (key)
	{
	case DOWN: { //아래
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1)
					main_org[b_y + i + 1][b_x + j] = ACTIVE_BLOCK;
			}
		}
		b_y++;
		break;
	}
	case RIGHT: { //오른쪽
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1)
					main_org[b_y + i + 1][b_x + j+1] = ACTIVE_BLOCK;
			}
		}
		b_x++;
		break;
	}
	case LEFT: { //왼쪽
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == 1)
					main_org[b_y + i + 1][b_x + j-1] = ACTIVE_BLOCK;
			}
		}
		b_x--;
		break;
	}
	case UP: { //턴
		block_turn(temp);
		break;
	}
	default:
		break;
	}
	
}
int** block_turn(int block[4][4]) {

}