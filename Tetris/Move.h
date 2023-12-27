#pragma once
#include"framework.h"
#include"Tetris.h"

extern Cube currentcube;
extern int map[10][30];
extern int r;
extern int v;
extern int score;
int IsRepeat();
int IsGameOver();
int IsBumpDown();
int IsBumpLeft();
int IsBumpRight();
int IsOverlap(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
int CanRotate(int x1, int y1, int x2, int y2, int x3, int y3);
void ShowInMap();
void DissappearInMap();
void Rotate();
void Down(int v);
void Match();
void PressKey(WPARAM key);