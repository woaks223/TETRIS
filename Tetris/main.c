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

#define ACTIVE_BLOCK -2 //���� �̵����� ��
#define CEILLING -1 //���� �̵��Ҽ� �ִ� ��ġ�� 0�̳� ���� ������ ǥ��
#define EMPTY 0 
#define WALL 1     //���� �̵��Ҽ� ���� ��ġ�� ���� ������ ǥ��
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
	printf("                                                ����                         \n"); Sleep(50);
	printf("       ������                ������    ��    ��             ���       \n"); Sleep(50);
	printf("           ��      �����          ��        ����      ��     ��    ��     \n"); Sleep(50);
	printf("           ��      ��                ��        ���        ��    ��            \n"); Sleep(50);
	printf("           ��      �����          ��        ��  ��      ��     ��           \n"); Sleep(50);
	printf("           ��      ��                ��        ��    ��    ��       ���       \n"); Sleep(50);
	printf("                   �����          ��        ��      ��  ��           ��     \n"); Sleep(50);
	printf("                                                           ��            ��    \n"); Sleep(50);
	printf("                                                                  ��    ��     \n"); Sleep(50);
	printf("                                                                    ���       \n"); Sleep(50);
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
				case ACTIVE_BLOCK:{ //�����̰� �ִ� ��
					printf("��");
					break;
				}
				case CEILLING: { //õ�� ���
					printf(". ");
					break;
				}
				case EMPTY: { //�� ����
					printf(" ");
					break;
				}
				case WALL: { //��
					printf("��");
					break;
				}
				case INACTIVE_BLOCK: {//�̵��� ���� ��
					printf("��");
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