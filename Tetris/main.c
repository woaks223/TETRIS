#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#pragma warning (disable:4996)

#define RIGHT_KEY 77
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

int main_cpy[MAP_Y][MAP_X];
int main_org[MAP_Y][MAP_X];
void map_reset();
void gotoxy(int x, int y);
void map();
char start();
void main() {
	char choice;
	choice = start();
	if (choice == '1') {
		map_reset();
		while (1) {
			map();
		}
	}
	else {
		exit(1);
	}
	return;
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
				gotoxy(MAIN_X+j,MAIN_Y+i);
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
	 
}
void gotoxy(int x, int y) { 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}