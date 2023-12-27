#include"Draw.h"
#include"framework.h"

#include<stdio.h>


void TextInfo(HDC memhdc) {
    static RECT rc;
    rc.left = 500;
    rc.right = 700;
    rc.top = 0;
    rc.bottom = 1000;

    static RECT rc2;
    rc2.left = 500;
    rc2.right = 700;
    rc2.top = 300;
    rc2.bottom = 1000;

    CHAR str[16];
    CHAR str2[100];
    CHAR buttom[100] = "***********************************************************************************";
    CHAR buttom2[200] = "===-----------------------------------------------------------------------------------------------------------------+++";
    CHAR buttom3[100] = "@-TETRIS__DEVELOPED_BY_WEEZZ--------v23.01.1";
    CHAR buttom4[100];
    CHAR left[500] = "|||||||||||||||||||||||||||||||||||||||||||||||||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n|||||||||||||||||||||||||||||||||||||||||||||||||\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|||||||||||||||||||||||||||||||||||||||||||||||||";
    CHAR right[500] = "|\n||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|";
    CHAR info[100] = "LEFT: ←\n\nRIGHT: →\n\nROTATE: ↑\n\nSPEED UP: ↓";

    sprintf_s(str, "SCORE:%d", score);
    sprintf_s(str2, "BEST SCORE:%d", best);
    sprintf_s(buttom4, "%c MONITOR: CURRENT VALUE: %d=>>>=NEXT VALUE: %d****TIMESTEP1: %d++++TIMESTEP2: %d", symbol[direction], r, next,timestep,timestep2);
    SetBkMode(memhdc, TRANSPARENT);
    SetTextColor(memhdc, RGB(50, 150, 100));

    TextOut(memhdc, 50, 50, str, strlen(str));
    TextOut(memhdc, 530, 450, str2, strlen(str2));
    TextOut(memhdc, 0, 800, buttom, strlen(buttom));
    TextOut(memhdc, 0, 805, buttom2, strlen(buttom2));
    TextOut(memhdc, 5, 820, buttom3, strlen(buttom3));
    TextOut(memhdc, 5, 840, buttom4, strlen(buttom4));
    DrawText(memhdc, right, strlen(right), &rc, DT_RIGHT);
    DrawText(memhdc, left, strlen(left), &rc, DT_LEFT);
    DrawText(memhdc, info, strlen(info), &rc2, DT_CENTER);
   
   
    
    HPEN hpen = CreatePen(PS_SOLID, 0, RGB(50, 150, 100)); 
    HPEN oldhpen = (HPEN)SelectObject(memhdc, hpen); // 画笔选入设备环境，并保留先前画笔
    MoveToEx(memhdc, mapwidth - (mapheight / cheight) * cwidth, 0, NULL);
    LineTo(memhdc, mapwidth - (mapheight / cheight) * cwidth, mapheight);
    SelectObject(memhdc, oldhpen); // 恢复先前画笔
    DeleteObject(hpen); // 删除创建画笔hpen
    
}
void DrawMap(HDC hdc) {
    for (int i = 0; i < cwidth; i++) {
        for (int j = 30-cheight; j < 30; j++) {
            if (map[i][j] != 0) {
                RECT rc;
                HBRUSH brush = CreateSolidBrush(cube[map[i][j] % 8 - 1].color);
                rc.left = (i -cwidth)* (mapheight/cheight)+mapwidth;
                rc.right = (i-cwidth+1) * (mapheight / cheight)+ mapwidth - 1;
                rc.bottom = (j -30+cheight) * (mapheight / cheight) + (mapheight / cheight)-1;
                rc.top = (j - 30 + cheight) * (mapheight / cheight);
                FillRect(hdc, &rc, brush);
                DeleteObject(brush);
            }
        }
    }

}
void DrawNext(HDC hdc) {
    RECT rc;
    HBRUSH brush = CreateSolidBrush(cube[next - 1].color);
    rc.left = nextcube.c1[0] * 30;
    rc.right = nextcube.c1[0]  * 30 + 29;
    rc.bottom = nextcube.c1[1]  * 30 + 29;
    rc.top = nextcube.c1[1] * 30;
    FillRect(hdc, &rc, brush);

    rc.left = nextcube.c2[0] * 30;
    rc.right = nextcube.c2[0] * 30 + 29;
    rc.bottom = nextcube.c2[1] * 30 + 29;
    rc.top = nextcube.c2[1] * 30;
    FillRect(hdc, &rc, brush);

    rc.left = nextcube.c3[0] * 30;
    rc.right = nextcube.c3[0] * 30 + 29;
    rc.bottom = nextcube.c3[1] * 30 + 29;
    rc.top = nextcube.c3[1] * 30;
    FillRect(hdc, &rc, brush);

    rc.left = nextcube.c4[0] * 30;
    rc.right = nextcube.c4[0] * 30 + 29;
    rc.bottom = nextcube.c4[1] * 30 + 29;
    rc.top = nextcube.c4[1] * 30;
    FillRect(hdc, &rc, brush);

    DeleteObject(brush);
}
void TextGameOver(HDC hdc) {
    HFONT  hFont1;
    hFont1 = CreateFont(30, 0, 0, 0, 1000, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
    HGDIOBJ nOldFont = SelectObject(hdc, hFont1);
    CHAR gameover[11] = "GAME OVER!";
    SetTextColor(hdc, RGB(255, 255, 255));
    TextOut(hdc, 200, 300, gameover, strlen(gameover));
    SelectObject(hdc, nOldFont);
    DeleteObject(nOldFont);
}
void TextButton(HDC hdc, CHAR *text,RECT rect,HWND hWnd,int x,int y,BOOL isHovering) {
    
    HBRUSH bbrush = CreateSolidBrush(RGB(50, 150, 100));
    HBRUSH cbrush = CreateSolidBrush(RGB(10, 60, 20));
   
    HFONT  hFont1;
    hFont1 = CreateFont(60, 0, 0, 0, 1000, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
    //HGDIOBJ nOldFont = 
    SelectObject(hdc, hFont1);
   
    if(isHovering)FillRect(hdc, &rect, cbrush);
    else FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    FrameRect(hdc, &rect, bbrush);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(50, 150, 100));
    
    DrawText(hdc, text, strlen(text), &rect, DT_CENTER);
    
    //SelectObject(hdc, nOldFont);
    DeleteObject(hFont1);
    DeleteObject(bbrush);
    DeleteObject(cbrush);
    
}
void DrawScene(HDC hdc) {
    
    switch (pcs) {
    case 0:
        
        
        break;
    
    default:
        DrawMap(hdc);
        DrawNext(hdc);
        TextInfo(hdc);
        
        break;
    }
}
