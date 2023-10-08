/*
이미지를 띄우고 방향키를 이용하여 이미지 움직이기 예시
S 를 눌러서 캐릭터 변경 가능
*/


#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "ImageLayer.h"
#include "SoundPlayer.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define S 115
#define M 77
#define SPEED 100

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;


void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();

int main() {
	int selectedCharacterIndex = 1;
	initialize();

	playBGM("start_bgm.wav");

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer);

	Image images[4] = {
		{"TestImage.bmp", 0, 0, 4},
		{"Character1Selected.bmp", 200, 200, 8},
		{"Character2.bmp", 600, 200, 8},
		{"Character3.bmp", 1200, 200, 8},
	};


	imageLayer.imageCount = 4;
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);

	imageLayer.fadeOut(&imageLayer, NULL);
	imageLayer.fadeIn(&imageLayer, NULL);

	while (1) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case S:
				selectedCharacterIndex++;
				if (selectedCharacterIndex == 4) {
					selectedCharacterIndex = 1;
				}

				if (selectedCharacterIndex == 1) {
					imageLayer.images[1].fileName = "Character1Selected.bmp";
					imageLayer.images[2].fileName = "Character2.bmp";
					imageLayer.images[3].fileName = "Character3.bmp";
				}
				else if (selectedCharacterIndex == 2) {
					imageLayer.images[2].fileName = "Character2Selected.bmp";
					imageLayer.images[1].fileName = "Character1.bmp";
					imageLayer.images[3].fileName = "Character3.bmp";
				}
				else {
					imageLayer.images[3].fileName = "Character3Selected.bmp";
					imageLayer.images[1].fileName = "Character1.bmp";
					imageLayer.images[2].fileName = "Character2.bmp";
				}

				break;

			case LEFT:
				imageLayer.images[selectedCharacterIndex].x -= SPEED;
				break;
			case RIGHT:
				imageLayer.images[selectedCharacterIndex].x += SPEED;
				break;
			case UP:
				imageLayer.images[selectedCharacterIndex].y -= SPEED;
				break;
			case DOWN:
				imageLayer.images[selectedCharacterIndex].y += SPEED;
				break;
			}
			imageLayer.renderAll(&imageLayer);
		}
	}

	return 0;
}


void getHandle() {
	CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	WINDOW_HANDLE = GetConsoleWindow();
}

void removeCursor() {
	CONSOLE_CURSOR_INFO c;
	c.bVisible = FALSE;
	c.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void resizeConsole(int w, int h) {
	char temp[100];
	sprintf(temp, "mode con cols=%d lines=%d", w, h);
	system(temp);
}

void initialize() {
	getHandle();
	resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	removeCursor();
}