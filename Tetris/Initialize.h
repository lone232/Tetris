#pragma once
#include"Tetris.h"
#include"framework.h"
extern Cube currentcube;
extern Cube nextcube;
extern Cube cube[7];
extern int map[10][30];
extern int r;
extern int next;
extern int v;
extern int best;
extern int score;
extern int pcs;


extern UINT timestep; //= 700;
extern UINT timestep2; //= 300;
extern UINT timestep3; //= 150;

extern int cwidth;
extern int cheight;

void ReadInit();
int CannotGenerate();
void GenerateRandCube();
void GenerateNextCube();
void Writeinini();