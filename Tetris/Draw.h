#pragma once
#include "framework.h"
#include "Tetris.h"
extern int pcs;
extern int next;
extern int r;
extern Cube currentcube;
extern Cube nextcube;
extern Cube cube[7];
extern int map[10][30];
extern int score;
extern int best;
extern CHAR symbol[];
extern int direction;
extern UINT timestep;
extern UINT timestep2;

extern int cwidth;
extern int cheight;
extern int mapwidth;
extern int mapheight;

void TextInfo(HDC memhdc);
void DrawMap(HDC hdc );
void DrawNext(HDC hdc);
void TextGameOver(HDC hdc);
void TextButton(HDC hdc, CHAR* text, RECT rect, HWND hWnd, int x, int y,BOOL);
void DrawScene(HDC hdc);