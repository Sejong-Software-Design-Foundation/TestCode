/*
�̹����� ���� ����Ű�� �̿��Ͽ� �̹��� �����̱� ����
S �� ������ ĳ���� ���� ����
*/


#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "ImageLayer.h"
#include "SoundPlayer.h"
#include <math.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define S 115
#define M 77
#define SPEED 48
#define ESC 27

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

int tileInfo[26][26];
void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();
void dig(int x, int y, ImageLayer* imageLayer);

int main() {
	initialize();

	playBGM("start_bgm.wav");

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer);

	Image images[1100] = {
		{"PlayerCharacter.bmp", 240,48, 1},
		/*{"TestImage.bmp", 0, 0, 4},
		{"Character1Selected.bmp", 200, 200, 8},
		{"Character2.bmp", 600, 200, 8},
		{"Character3.bmp", 1200, 200, 8},
		{"Ball.bmp", 1500, 500, 1},*/
		//{"simpleMap.bmp", 0, 240, 1}
	};

	imageLayer.imageCount = 2;
	for (int y = 240;y < 240 + 48 * 25;y+=48) {
		for (int x = 0;x < 48 * 25;x += 48) {
			Image newTile = { "simpleMap.bmp", x, y, 1 };
			images[imageLayer.imageCount++] = newTile;
			tileInfo[(y - 240) / 48][x / 48] = 1;
		}
	}

	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);


	while (1) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case S:
				break;
			case LEFT:
				if (collisionCheck(imageLayer.images[0].x - SPEED, imageLayer.images[0].y))
					dig(imageLayer.images[0].x - SPEED, imageLayer.images[0].y, &imageLayer);
				else imageLayer.images[0].x -= SPEED;
				imageLayer.renderAll(&imageLayer);
				break;
			case RIGHT:
				if (collisionCheck(imageLayer.images[0].x + SPEED, imageLayer.images[0].y))
					dig(imageLayer.images[0].x + SPEED, imageLayer.images[0].y, &imageLayer);
				else imageLayer.images[0].x += SPEED;
				imageLayer.renderAll(&imageLayer);
				break;
			case UP:
				if (collisionCheck(imageLayer.images[0].x, imageLayer.images[0].y - SPEED))
					dig(imageLayer.images[0].x, imageLayer.images[0].y-SPEED, &imageLayer);
				else imageLayer.images[0].y -= SPEED;
				imageLayer.renderAll(&imageLayer);
				break;
			case DOWN:
				if (collisionCheck(imageLayer.images[0].x, imageLayer.images[0].y + SPEED))
					dig(imageLayer.images[0].x, imageLayer.images[0].y+SPEED, &imageLayer);
				else imageLayer.images[0].y += SPEED;
				imageLayer.renderAll(&imageLayer);
				break;
			case ESC:
				return;
				break;
			}
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

int collisionCheck(int x, int y) {
	int infoX = x / 48;
	if (y - 240 < 0) return 0;
	int infoY = (y-240) / 48;
	return tileInfo[infoY][infoX];
}

void dig(int x, int y, ImageLayer *imageLayer) {
	int infoX = x / 48;
	int infoY = (y - 240) / 48;
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	Image newImage = { NULL,x,y,1 };
	imageLayer->images[infoY * 25 + infoX + 2] = newImage;
	tileInfo[infoY][infoX] = 0;
}