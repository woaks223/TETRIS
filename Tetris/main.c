#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <process.h>

#pragma warning (disable:4996)

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define MAP_X 15
#define MAP_Y 25
#define MAIN_X 3
#define MAIN_Y 1

#define ACTIVE_BLOCK -2 //���� �̵����� ��
#define CEILLING -1 //���� �̵��Ҽ� �ִ� ��ġ�� 0�̳� ���� ������ ǥ��
#define EMPTY 0 
#define WALL 1     //���� �̵��Ҽ� ���� ��ġ�� ���� ������ ǥ��
#define INACTIVE_BLOCK 2

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 

int new_block_on;
int main_cpy[MAP_Y][MAP_X];
int main_org[MAP_Y][MAP_X];
int b_x = (MAP_X / 2) - 1; //���� x��ǥ
int b_y = 0; //���� y��ǥ
int temp[4][4];
int key = 0;
int crash_num = 1;
int game_speed = 1000;

void check_crash_turn(int x, int y, int arr[4][4]);
void check_crash(int x, int y);
void key_ent();
void move_block(int key);
void map_reset();
void gotoxy(int x, int y);
void map();
char start();
void new_block();
void block_turn(int block[4][4]);
void setcursortype(CURSOR_TYPE c);
void auto_down_blcok(void *p);
void line_check();

void main() {
	char choice;
	setcursortype(NOCURSOR);
	choice = start();
	_beginthread(auto_down_blcok, 0, 0);
	if (choice == '1') {
		map_reset();
		while (1) {
			map();
			if (new_block_on == 1) new_block();
			key_ent();

		}
	}
	else {
		exit(1);
	}
	return;
}

//�ڵ����� �������� �κ�
void auto_down_blcok(void *p) {
	Sleep(1000);
	while (1) {
		int temp_ = 0;
		check_crash(b_x, b_y + 1);
		if(crash_num==1)
			move_block(DOWN);
		else {
			for (int i = 0; i < MAP_Y; i++)
				for (int j = 0; j < MAP_X; j++)
					if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
			new_block();
		}

		Sleep(game_speed);
	}
}

//Ŀ�� ���ִ� �Լ�
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
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

//Ű �Է¹޴� �Լ�
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
				check_crash(b_x, b_y + 1);
				if (crash_num == 1) move_block(DOWN);
				break;
			}
			case RIGHT: {
				check_crash(b_x + 1, b_y);
				if (crash_num == 1) move_block(RIGHT);
				break;
			}
			case LEFT: {
				check_crash(b_x - 1, b_y);
				if (crash_num == 1) move_block(LEFT);
				break;
			}
			case UP: {
				block_turn(temp);
				break;
			}
			default:
				break;
			}
		}
		else {

		}

	}
	fflush(stdin);
}

//�ʱ�ȭ��
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
	char num = getch();
	system("cls");
	return num;
}

//���� �׷��ִ� �Լ�
void map() {

	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) {
				gotoxy(MAIN_X + j, MAIN_Y + i);
				switch (main_org[i][j])
				{
				case ACTIVE_BLOCK: { //�����̰� �ִ� ��
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

//�ʱ� �� ����
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
	for (int i = 1; i < MAP_X - 1; i++)
		main_org[2][i] = CEILLING;
	new_block();
}

//gotoxy �Լ�
void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//������ �Լ�
void new_block() {
	int block[5][4][4] = {
		{ { 0,0,0,0 },{ 0, -2, -2, 0 },{ 0, -2, -2, 0 } ,{ 0, 0, 0, 0 } },
		{ { 0,0,0,0 },{ 0,-2,0,0 },{ 0,-2,-2,0 },{ 0,-2,0,0 } },
		{ { 0,0,-2,0 },{ 0,0,-2,0 },{ 0,0,-2,0 },{ 0,0,-2,0 } },
		{ { 0,-2,0,0 },{ 0,-2,-2,0 },{ 0,0,-2,0 },{ 0,0,0,0 } },
		{ { 0,0,-2,0 },{ 0,-2,-2,0 },{ 0,-2,0,0 },{ 0,0,0,0 } },
	};

	int random_block;

	srand(time(NULL));
	b_x = (MAIN_X /2)+1;
	b_y = 0;
	random_block = rand() % 5;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			main_org[b_y + i][b_x + j] = block[random_block][i][j];
			temp[i][j] = block[random_block][i][j];
		}
	}

}

//�浹 üũ�Լ�
void check_crash(int x, int y) {
	int temp_ = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp[i][j] == -2 && main_org[y + i][x + j]>0) { 
				temp_++;
			}
		}
	}
	if (temp_ != 0) crash_num = 0;
	else crash_num = 1;
}
void check_crash_turn(int x, int y,int arr[4][4]) {
	int temp_ = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp[i][j] == -2 && main_org[y + i][x + j]>0) { //����
				temp_++;
			}
		}
	}
	if (temp_ != 0) crash_num = 0;
	else crash_num = 1;
}
//�� �̵��Լ�
void move_block(int key) {

	switch (key)
	{
	case DOWN: { //�Ʒ�
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2)
					main_org[b_y + i + 1][b_x + j] = ACTIVE_BLOCK; //�Լ��� ���̱�
			}
		}
		b_y++;
		break;
	}
	case RIGHT: { //������
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2)
					main_org[b_y + i][b_x + j + 1] = ACTIVE_BLOCK;
			}
		}
		b_x++;
		break;
	}
	case LEFT: { //����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2)
					main_org[b_y + i][b_x + j - 1] = ACTIVE_BLOCK;
			}
		}
		b_x--;
		break;
	}
	case UP: { //��
		block_turn(temp);
		break;
	}
	default:
		break;
	}
	
}

//�� ȸ�� �Լ�
void block_turn(int block[4][4]) {
	int arr[4][4];
	int n1, n2;
	n1 = 0;

	for (int i = 0; i < 4; i++) {
		n2 = 0;
		for (int j = 3; j > -1; j--) {
			arr[n1][n2] = block[j][i];
			n2++;
		}
		n1++;
	}
	check_crash_turn(b_x+1, b_y+1, *arr);
	if (crash_num == 1) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2) {
					main_org[b_y + i][b_x + j] = EMPTY;
				}
			}
		}
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = arr[i][j];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (temp[i][j] == -2)
					main_org[b_y + i][b_x + j] = ACTIVE_BLOCK;
			}
		}
	}
}

void line_check() {

}