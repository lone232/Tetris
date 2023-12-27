#include"Move.h"
#include"Initialize.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

int IsRepeat() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 30; j++) {
            if (map[i][j] == r)
                return 1;
        }
    }
    return 0;
}
int IsGameOver() {
    for (int i = 0; i < cwidth; i++) {
        if (map[i][30 - cheight] != 0 && map[i][30 - cheight] != r) {
            return 1;
        }
    }
    return 0;
}
int IsBumpDown() {
    if (currentcube.c1[1] ==  29 || currentcube.c2[1] == 29 || currentcube.c3[1] == 29 || currentcube.c4[1] == 29)return 1;
    if (map[currentcube.c1[0]][currentcube.c1[1] + 1] != 0 && map[currentcube.c1[0]][currentcube.c1[1] + 1] != r)return 1;
    if (map[currentcube.c2[0]][currentcube.c2[1] + 1] != 0 && map[currentcube.c2[0]][currentcube.c2[1] + 1] != r)return 1;
    if (map[currentcube.c3[0]][currentcube.c3[1] + 1] != 0 && map[currentcube.c3[0]][currentcube.c3[1] + 1] != r)return 1;
    if (map[currentcube.c4[0]][currentcube.c4[1] + 1] != 0 && map[currentcube.c4[0]][currentcube.c4[1] + 1] != r)return 1;
    return 0;

}
int IsBumpLeft() {
    if (currentcube.c1[0] == 0 || currentcube.c2[0] == 0 || currentcube.c3[0] == 0 || currentcube.c4[0] == 0)
        return 1;
    else if ((map[currentcube.c1[0] - 1][currentcube.c1[1]] != 0 && map[currentcube.c1[0] - 1][currentcube.c1[1]] != r) ||
        (map[currentcube.c2[0] - 1][currentcube.c2[1]] != 0 && map[currentcube.c2[0] - 1][currentcube.c2[1]] != r) ||
        (map[currentcube.c3[0] - 1][currentcube.c3[1]] != 0 && map[currentcube.c3[0] - 1][currentcube.c3[1]] != r) ||
        (map[currentcube.c4[0] - 1][currentcube.c4[1]] != 0 && map[currentcube.c4[0] - 1][currentcube.c4[1]] != r))
        return 1;
    else
        return 0;

}
int IsBumpRight() {
    if (currentcube.c1[0] == cwidth - 1 || currentcube.c2[0] == cwidth - 1 || currentcube.c3[0] == cwidth - 1 || currentcube.c4[0] == cwidth - 1)
        return 1;
    else if ((map[currentcube.c1[0] + 1][currentcube.c1[1]] != 0 && map[currentcube.c1[0] + 1][currentcube.c1[1]] != r) ||
        (map[currentcube.c2[0] + 1][currentcube.c2[1]] != 0 && map[currentcube.c2[0] + 1][currentcube.c2[1]] != r) ||
        (map[currentcube.c3[0] + 1][currentcube.c3[1]] != 0 && map[currentcube.c3[0] + 1][currentcube.c3[1]] != r) ||
        (map[currentcube.c4[0] + 1][currentcube.c4[1]] != 0 && map[currentcube.c4[0] + 1][currentcube.c4[1]] != r))
        return 1;
    else
        return 0;

}
int IsOverlap(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if ((map[x1][y1] != 0 && map[x1][y1] != r) ||
        (map[x2][y2] != 0 && map[x2][y2] != r) ||
        (map[x3][y3] != 0 && map[x3][y3] != r) ||
        (map[x4][y4] != 0 && map[x4][y4] != r))
        return 1;
    else
        return 0;
}
int CanRotate(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (currentcube.c2[0] + x1 >= 0 && currentcube.c2[0] + x1 < cwidth && currentcube.c2[1] + y1 >= 0 && currentcube.c2[1] + y1 < 30 &&
        currentcube.c2[0] + x2 >= 0 && currentcube.c2[0] + x2 < cwidth && currentcube.c2[1] + y2 >= 0 && currentcube.c2[1] + y2 < 30 &&
        currentcube.c2[0] + x3 >= 0 && currentcube.c2[0] + x3 < cwidth && currentcube.c2[1] + y3 >= 0 && currentcube.c2[1] + y3 < 30 &&
        !IsOverlap(currentcube.c2[0] + x1, currentcube.c2[1] + y1, currentcube.c2[0], currentcube.c2[1], currentcube.c2[0] + x2, currentcube.c2[1] + y2, currentcube.c2[0] + x3, currentcube.c2[1] + y3))
        return 1;
    else
        return 0;
}
void ShowInMap() {

    map[currentcube.c1[0]][currentcube.c1[1]] = r;
    map[currentcube.c2[0]][currentcube.c2[1]] = r;
    map[currentcube.c3[0]][currentcube.c3[1]] = r;
    map[currentcube.c4[0]][currentcube.c4[1]] = r;


}
void DissappearInMap() {
    map[currentcube.c1[0]][currentcube.c1[1]] = 0;
    map[currentcube.c2[0]][currentcube.c2[1]] = 0;
    map[currentcube.c3[0]][currentcube.c3[1]] = 0;
    map[currentcube.c4[0]][currentcube.c4[1]] = 0;
}
void Rotate() {
    int d[3][2];
    int mid;
    d[0][0] = currentcube.c1[0] - currentcube.c2[0];
    d[0][1] = currentcube.c1[1] - currentcube.c2[1];
    mid = d[0][0];
    d[0][0] = d[0][1];
    d[0][1] = -mid;

    d[1][0] = currentcube.c3[0] - currentcube.c2[0];
    d[1][1] = currentcube.c3[1] - currentcube.c2[1];
    mid = d[1][0];
    d[1][0] = d[1][1];
    d[1][1] = -mid;

    d[2][0] = currentcube.c4[0] - currentcube.c2[0];
    d[2][1] = currentcube.c4[1] - currentcube.c2[1];
    mid = d[2][0];
    d[2][0] = d[2][1];
    d[2][1] = -mid;
    if (CanRotate(d[0][0], d[0][1], d[1][0], d[1][1], d[2][0], d[2][1]) && r % 8 != 7) {
        currentcube.c1[0] = currentcube.c2[0] + d[0][0];
        currentcube.c1[1] = currentcube.c2[1] + d[0][1];
        currentcube.c3[0] = currentcube.c2[0] + d[1][0];
        currentcube.c3[1] = currentcube.c2[1] + d[1][1];
        currentcube.c4[0] = currentcube.c2[0] + d[2][0];
        currentcube.c4[1] = currentcube.c2[1] + d[2][1];
    }
}
void Down(int v) {
    if (!IsBumpDown()) {
        currentcube.c1[1] += v;
        currentcube.c2[1] += v;
        currentcube.c3[1] += v;
        currentcube.c4[1] += v;

        //WriteConsole(debug, "time", 8, NULL, NULL);
    }
}
void Match() {
    int p = 0;
    int add = 1;
    for (int j = 29 ; j >= 0; j--) {
        int i;
        for (i = 0; i < cwidth; i++) {
            if (map[i][j] == 0)
                break;
        }
        if (i == cwidth) {
            for (int p = 0; p < cwidth; p++) {
                for (int n = j; n > 0; n--)
                    map[p][n] = map[p][n - 1];
            }
            j++;
            p++;
            //PlaySound(MAKEINTRESOURCEA(IDR_WAVE12), NULL, SND_RESOURCE | SND_ASYNC|SND_NOSTOP);
            //Sleep(500);
            //mciSendString("open Electric Zap Somewhere Far 006.wav", NULL, 0, NULL);
            //mciSendString("play Electric Zap Somewhere Far 006.wav", NULL, 0, NULL);
        }
    }
    if (p > 0) {
        for (int n = 1; n <= p; n++) {
            add *= 10;
        }
        score += add;
    }
}
void PressKey(WPARAM key) {
    switch (key) {
    case VK_LEFT:
        if (!IsBumpLeft() && !IsGameOver() && !CannotGenerate()) {

            DissappearInMap();
            currentcube.c1[0] -= 1;
            currentcube.c2[0] -= 1;
            currentcube.c3[0] -= 1;
            currentcube.c4[0] -= 1;
            ShowInMap();
        }
        break;
    case VK_RIGHT:
        if (!IsBumpRight() && !IsGameOver() && !CannotGenerate()) {
            DissappearInMap();
            currentcube.c1[0] += 1;
            currentcube.c2[0] += 1;
            currentcube.c3[0] += 1;
            currentcube.c4[0] += 1;
            ShowInMap();
        }
        break;
    case VK_DOWN:
        if (!IsGameOver() && !CannotGenerate()) {
            DissappearInMap();
            Down(v);
            ShowInMap();
        }
        break;
    case VK_UP:
        if (!IsGameOver() && !CannotGenerate()) {
            DissappearInMap();
            Rotate();
            ShowInMap();
        }
        break;
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    default:
        break;

    }
}