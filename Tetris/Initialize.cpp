#include"Initialize.h"
#include<stdio.h>
void ReadInit() {
    switch (pcs) {
    case 0:
        break;
    case 1:
        timestep = GetPrivateProfileInt("Global", "timestep", timestep, "resource\\init.ini");
        timestep2 = GetPrivateProfileInt("Global", "timestep2", timestep2, "resource\\init.ini");
        
        best = GetPrivateProfileInt("Player", "best score", best, "resource\\init.ini");

        cwidth = GetPrivateProfileInt("Map", "cwidth", 10, "resource\\init.ini");
        cheight = GetPrivateProfileInt("Map", "cheight", 16, "resource\\init.ini");
        break;
    case 2:
        timestep = GetPrivateProfileInt("Global", "timestep", timestep, "resource\\init2.ini");
        timestep2 = GetPrivateProfileInt("Global", "timestep2", timestep2, "resource\\init2.ini");
       
        best = GetPrivateProfileInt("Player", "best score", best, "resource\\init2.ini");

        cwidth = GetPrivateProfileInt("Map", "cwidth", 10, "resource\\init2.ini");
        cheight = GetPrivateProfileInt("Map", "cheight", 16, "resource\\init2.ini");
        break;
    case 3:
        timestep = GetPrivateProfileInt("Global", "timestep", timestep, "resource\\init3.ini");
        timestep2 = GetPrivateProfileInt("Global", "timestep2", timestep2, "resource\\init3.ini");
        
        best = GetPrivateProfileInt("Player", "best score", best, "resource\\init3.ini");

        cwidth = GetPrivateProfileInt("Map", "cwidth", 10, "resource\\init2.ini");
        cheight = GetPrivateProfileInt("Map", "cheight", 16, "resource\\init2.ini");
        break;
    default:
        break;

    }
}


int CannotGenerate() {
    if ((map[cube[r % 8 - 1].c1[0]][cube[r % 8 - 1].c1[1] + 26 - cheight] != 0 &&
        map[cube[r % 8 - 1].c1[0]][cube[r % 8 - 1].c1[1] + 26 - cheight]  != r) ||
        (map[cube[r % 8 - 1].c2[0]][cube[r % 8 - 1].c2[1] + 26 - cheight] != 0 &&
            map[cube[r % 8 - 1].c2[0]][cube[r % 8 - 1].c2[1] + 26 - cheight] != r) ||
        (map[cube[r % 8 - 1].c3[0]][cube[r % 8 - 1].c3[1] + 26 - cheight] != 0 &&
            map[cube[r % 8 - 1].c3[0]][cube[r % 8 - 1].c3[1] + 26 - cheight] != r) ||
        (map[cube[r % 8 - 1].c4[0]][cube[r % 8 - 1].c4[1] + 26 - cheight] != 0 &&
            map[cube[r % 8 - 1].c4[0]][cube[r % 8 - 1].c4[1] + 26 - cheight] != r))
        return 1;
    else
        return 0;
}



void GenerateRandCube() {

    currentcube.c1[0] = cube[r % 8 - 1].c1[0];
    currentcube.c1[1] = cube[r % 8 - 1].c1[1]+ 26 - cheight;

    currentcube.c2[0] = cube[r % 8 - 1].c2[0];
    currentcube.c2[1] = cube[r % 8 - 1].c2[1]+ 26 - cheight;

    currentcube.c3[0] = cube[r % 8 - 1].c3[0];
    currentcube.c3[1] = cube[r % 8 - 1].c3[1] + 26 - cheight;

    currentcube.c4[0] = cube[r % 8 - 1].c4[0];
    currentcube.c4[1] = cube[r % 8 - 1].c4[1] + 26 - cheight;
}void GenerateNextCube() {

    nextcube.c1[0] = cube[next - 1].c1[0] + 15;
    nextcube.c1[1] = cube[next - 1].c1[1] + 2;

    nextcube.c2[0] = cube[next - 1].c2[0] + 15;
    nextcube.c2[1] = cube[next - 1].c2[1] + 2;

    nextcube.c3[0] = cube[next - 1].c3[0] + 15;
    nextcube.c3[1] = cube[next - 1].c3[1] + 2;

    nextcube.c4[0] = cube[next - 1].c4[0] + 15;
    nextcube.c4[1] = cube[next - 1].c4[1] + 2;
}

void Writeinini() {
    if (score > best) {
        CHAR bestscore[100];
        sprintf_s(bestscore, "%d", score);
        switch (pcs)
        {
        case 1:
            WritePrivateProfileString("Player", "best score", bestscore, "resource\\init.ini");
            break;
        case 2:
            WritePrivateProfileString("Player", "best score", bestscore, "resource\\init2.ini");
            break;
        case 3:
            WritePrivateProfileString("Player", "best score", bestscore, "resource\\init3.ini");
            break;
        default:
            break;
        }
        
    }
}