// Tetris.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Tetris.h"
#include "Draw.h"
#include "Move.h"
#include"Initialize.h"
#include<time.h>
#include<stdio.h>
#include<windowsx.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")


#define MAX_LOADSTRING 100
#define ID_START 1
#define ID_END 2
#define ID_EASY 3
#define ID_HARD 4
#define ID_HELL 5
#define ID_RETURN 6
#define ID_RESTART 7
#define ID_CHANGE 8
#define ID_CONTINUE 9


BOOL pause = FALSE;
BOOL isStart = FALSE;
BOOL isEnd = FALSE;
BOOL isEasy = FALSE;
BOOL isHard = FALSE;
BOOL isHell = FALSE;
BOOL isReturn = FALSE;
BOOL isRestart = FALSE;
BOOL isChange = FALSE;
BOOL isContinue = FALSE;
//BOOL isRestart = FALSE;

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING]={L"TETRIS"};                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
WCHAR title[10] = { LoadStringW(hInst, IDC_TETRIS, szTitle, 10) };

WCHAR szChildClass[MAX_LOADSTRING] = { L"START"};
//wcscpy_s(szChildClass, "123456");






Cube cube[7] = {
    {{3,0},{4,0},{5,0},{6,0},RGB(100,20,100)},// |
    {{4,0},{4,1},{4,2},{5,2},RGB(60,100,80)},// L
    {{5,0},{5,1},{5,2},{4,2},RGB(60,100,80)},// J
    {{4,0},{4,1},{5,1},{5,2},RGB(170,60,50)},// right s
    {{5,0},{5,1},{4,1},{4,2},RGB(170,60,50)},// left s
    {{4,0},{4,1},{4,2},{5,1},RGB(10,80,150)},// 山
    {{5,0},{5,1},{4,0},{4,1},RGB(90,10,50)}// 田
};

Cube currentcube;
Cube nextcube;

UINT timestep; //= 700;
UINT timestep2; //= 300;
UINT timestep3 = 150;
UINT timerb = 10;
//UINT timerpause = 10;
int direction;
CHAR symbol[] = { '-','/','|','\\'};
int v = 1;
int map[10][30] ;//1个单位为一个格子
int r;//随机产生的方块类型
int next;
int repeat = 1;//区分重复方块
int score = 0;
int best;
int pcs=0;//0-开始界面，1-难度1，2-难度2，3-难度3

int wndwidth = 800;// cube board
int wndheight = 1000;

int cwidth;
int cheight ;
int mapwidth = 500;// cube board
int mapheight = 800;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);







/*void Debug() {
    char info[10];
    sprintf_s(info, "cube:%d", r);
    WriteConsole(debug,info,strlen(info), NULL, NULL);
}*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    ReadInit();
    
    srand(time(NULL));
    
    
    

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
   
    

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

    MSG msg;

   
    //ReadInit();
   

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //AllocConsole();
    //debug = GetStdHandle(STD_OUTPUT_HANDLE);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
    wcex.hCursor        = LoadCursorA(hInst, (char*)IDC_CURSOR1);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_TETRIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);


}





//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowExW( WS_EX_COMPOSITED,szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU ,
     500, 0, 800, 1000, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndstart;
    static HWND hwndend;
    static HWND hwndeasy;
    static HWND hwndhard;
    static HWND hwndhell;
    static HWND hwndreturn;
    static HWND hwndrestart;
    static HWND hwndchange;
    static HWND hwndcontinue;

    static HWND hwndchild;
    static POINT pnt;

    static CHAR start[10] = "START";
    static CHAR easy[10] = "EASY";
    static CHAR hard[10] = "HARD";
    static CHAR hell[10] = "HELL";
    static CHAR end[10] = "END";
    static CHAR restart[10] = "RESTART";
    static CHAR change[10] = "CHANGE";
    static CHAR retun[10] = "RETURN";
    static CHAR Continue[10] = "CONTINUE";


    static HCURSOR hcur0 = LoadCursorA(hInst, (char*)IDC_CURSOR1);
    static HCURSOR hcur1 = LoadCursorA(hInst, (char*)IDC_CURSOR2);
    static LPDRAWITEMSTRUCT pdis;
    static HBRUSH bbrush = CreateSolidBrush(RGB(50, 150, 100));

    static RECT rect;
    

    

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_START:
            //SetCursor(hcur1);
            
            //system("pause");
            //Sleep(3000);
            //PlaySoundA(NULL, NULL, SND_FILENAME);
            
            //mciSendStringA("open D:\\VScpp\\Tetris\\Tetris\\resource\\Voice Announce 001.wav alias bkmusic", NULL, 0, NULL);
            //mciSendStringA("play bkmusic repeat", NULL, 0, NULL);
            //Sleep(500);

            EnableWindow(hwndstart, FALSE);
            ShowWindow(hwndstart, SW_HIDE);
            EnableWindow(hwndend, FALSE);
            ShowWindow(hwndend, SW_HIDE);

            EnableWindow(hwndeasy, TRUE);
            ShowWindow(hwndeasy, SW_SHOW);
            EnableWindow(hwndhard, TRUE);
            ShowWindow(hwndhard, SW_SHOW);
            EnableWindow(hwndhell, TRUE);
            ShowWindow(hwndhell, SW_SHOW);
            EnableWindow(hwndreturn, TRUE);
            ShowWindow(hwndreturn, SW_SHOW);
            //InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);

            PlaySound(MAKEINTRESOURCEA(IDR_WAVE4), NULL, SND_RESOURCE | SND_ASYNC);
            Sleep(2000);
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE5), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

            //DestroyWindow(hwndstart);
            //DestroyWindow(hwndend);

            //hwndeasy = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 100, 200, 100, hWnd, (HMENU)ID_EASY, hInst, nullptr);
            //hwndhard = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 300, 200, 100, hWnd, (HMENU)ID_HARD, hInst, nullptr);
            //hwndhell = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 500, 200, 100, hWnd, (HMENU)ID_HELL, hInst, nullptr);
            //hwndreturn = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 700, 200, 100, hWnd, (HMENU)ID_RETURN, hInst, nullptr);
            break;
        case ID_END:
            KillTimer(hWnd, 1);
            KillTimer(hWnd, 2);
            KillTimer(hWnd, 3);
            KillTimer(hWnd, 4);
            KillTimer(hWnd, 5);
            DeleteObject(bbrush);
            PostQuitMessage(0);
            break;
        case ID_EASY:
            pcs = 1;
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE9), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

            EnableWindow(hwndeasy, FALSE);
            ShowWindow(hwndeasy, SW_HIDE);
            EnableWindow(hwndhard, FALSE);
            ShowWindow(hwndhard, SW_HIDE);
            EnableWindow(hwndhell, FALSE);
            ShowWindow(hwndhell, SW_HIDE);
            EnableWindow(hwndreturn, FALSE);
            ShowWindow(hwndreturn, SW_HIDE);

            SetFocus(hWnd);
            //DestroyWindow(hwndeasy);
            //DestroyWindow(hwndhard);
            //DestroyWindow(hwndhell);
            //DestroyWindow(hwndreturn);
            ReadInit();
            memset(map, 0, sizeof(map));
            score = 0;
            repeat = 0;
            r = rand() % 7 + 1;
            next = rand() % 7 + 1;
            //Debug();
            GenerateRandCube();
            GenerateNextCube();
            ShowInMap();
            SetTimer(hWnd, 1, timestep, NULL);
            SetTimer(hWnd, 2, timestep2, NULL);

            break;
        case ID_HARD:
            pcs = 2;
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE8), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

            EnableWindow(hwndeasy, FALSE);
            ShowWindow(hwndeasy, SW_HIDE);
            EnableWindow(hwndhard, FALSE);
            ShowWindow(hwndhard, SW_HIDE);
            EnableWindow(hwndhell, FALSE);
            ShowWindow(hwndhell, SW_HIDE);
            EnableWindow(hwndreturn, FALSE);
            ShowWindow(hwndreturn, SW_HIDE);

            SetFocus(hWnd);
            //DestroyWindow(hwndeasy);
            //DestroyWindow(hwndhard);
            //DestroyWindow(hwndhell);
            //DestroyWindow(hwndreturn);
            ReadInit();
            memset(map, 0, sizeof(map));
            score = 0;
            repeat = 0;
            r = rand() % 7 + 1;
            next = rand() % 7 + 1;
            //Debug();
            GenerateRandCube();
            GenerateNextCube();
            ShowInMap();
            SetTimer(hWnd, 1, timestep, NULL);
            SetTimer(hWnd, 2, timestep2, NULL);

            break;
        case ID_HELL:
            pcs = 3;
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

            EnableWindow(hwndeasy, FALSE);
            ShowWindow(hwndeasy, SW_HIDE);
            EnableWindow(hwndhard, FALSE);
            ShowWindow(hwndhard, SW_HIDE);
            EnableWindow(hwndhell, FALSE);
            ShowWindow(hwndhell, SW_HIDE);
            EnableWindow(hwndreturn, FALSE);
            ShowWindow(hwndreturn, SW_HIDE);

            SetFocus(hWnd);
            //DestroyWindow(hwndeasy);
            //DestroyWindow(hwndhard);
            //DestroyWindow(hwndhell);
            //DestroyWindow(hwndreturn);
            ReadInit();
            memset(map, 0, sizeof(map));
            score = 0;
            repeat = 0;
            r = rand() % 7 + 1;
            next = rand() % 7 + 1;
            //Debug();
            GenerateRandCube();
            GenerateNextCube();
            ShowInMap();
            SetTimer(hWnd, 1, timestep, NULL);
            SetTimer(hWnd, 2, timestep2, NULL);

            break;
        case ID_RETURN:

            EnableWindow(hwndeasy, FALSE);
            ShowWindow(hwndeasy, SW_HIDE);
            EnableWindow(hwndhard, FALSE);
            ShowWindow(hwndhard, SW_HIDE);
            EnableWindow(hwndhell, FALSE);
            ShowWindow(hwndhell, SW_HIDE);
            EnableWindow(hwndreturn, FALSE);
            ShowWindow(hwndreturn, SW_HIDE);
            //DestroyWindow(hwndeasy);
            //DestroyWindow(hwndhard);
            //DestroyWindow(hwndhell);
            //DestroyWindow(hwndreturn);
            EnableWindow(hwndstart, TRUE);
            ShowWindow(hwndstart, SW_SHOW);
            EnableWindow(hwndend, TRUE);
            ShowWindow(hwndend, SW_SHOW);
            MoveWindow(hwndend, 280, 500, 200, 100, TRUE);
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);//loop

            //hwndstart = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 300, 200, 100, hWnd, (HMENU)ID_START, hInst, nullptr);
            //hwndend = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW |WS_CLIPSIBLINGS, 280, 500, 200, 100, hWnd, (HMENU)ID_END, hInst, nullptr);
            break;
        case ID_RESTART:
            pause = FALSE;
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC );
            Sleep(3000);
            switch(pcs){
            case 1:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE9), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
                break;
            case 2:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE8), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
                break;
            case 3:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
                break;
            default:
                break;


            }
            EnableWindow(hwndrestart, FALSE);
            ShowWindow(hwndrestart, SW_HIDE);
            EnableWindow(hwndchange, FALSE);
            ShowWindow(hwndchange, SW_HIDE);
            EnableWindow(hwndend, FALSE);
            ShowWindow(hwndend, SW_HIDE);
            EnableWindow(hwndcontinue, FALSE);
            ShowWindow(hwndcontinue, SW_HIDE);
            MoveWindow(hwndchange, 300, 500, 200, 100, FALSE);

            SetFocus(hWnd);

            //DestroyWindow(hwndrestart);
            //DestroyWindow(hwndchange);
            //DestroyWindow(hwndend);
            ReadInit();
            memset(map, 0, sizeof(map));
            score = 0;
            repeat = 0;
            r = rand() % 7 + 1;
            next = rand() % 7 + 1;
            //Debug();
            GenerateRandCube();
            GenerateNextCube();
            ShowInMap();
            SetTimer(hWnd, 1, timestep, NULL);
            SetTimer(hWnd, 2, timestep2, NULL);


            break;
        case ID_CHANGE:
            pause = FALSE;
            PlaySound(MAKEINTRESOURCEA(IDR_WAVE5), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

            EnableWindow(hwndrestart, FALSE);
            ShowWindow(hwndrestart, SW_HIDE);
            EnableWindow(hwndchange, FALSE);
            ShowWindow(hwndchange, SW_HIDE);
            EnableWindow(hwndend, FALSE);
            ShowWindow(hwndend, SW_HIDE);
            EnableWindow(hwndcontinue, FALSE);
            ShowWindow(hwndcontinue, SW_HIDE);
           
            pcs = 0;
            memset(map, 0, sizeof(map));

            EnableWindow(hwndeasy, TRUE);
            ShowWindow(hwndeasy, SW_SHOW);
            EnableWindow(hwndhard, TRUE);
            ShowWindow(hwndhard, SW_SHOW);
            EnableWindow(hwndhell, TRUE);
            ShowWindow(hwndhell, SW_SHOW);
            EnableWindow(hwndreturn, TRUE);
            ShowWindow(hwndreturn, SW_SHOW);
            MoveWindow(hwndchange, 300, 500, 200, 100, FALSE);
           
            //InvalidateRect(hWnd, NULL, TRUE);
            score = 0;

            break;
        case ID_CONTINUE:
            pause = FALSE;
            SetTimer(hWnd, 1, timestep, NULL);
            SetTimer(hWnd, 2, timestep2, NULL);
            switch (pcs) {
            case 1:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE9), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                break;
            case 2:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE8), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                break;
            case 3:
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                break;
            default:
                break;
            }
            //Writeinini();
            //PlaySound(MAKEINTRESOURCEA(IDR_WAVE10), NULL, SND_RESOURCE | SND_ASYNC);
            //Sleep(4000);
            //PlaySound(MAKEINTRESOURCEA(IDR_WAVE11), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
            EnableWindow(hwndrestart, FALSE);
            ShowWindow(hwndrestart, SW_HIDE);
            EnableWindow(hwndcontinue, FALSE);
            ShowWindow(hwndcontinue, SW_HIDE);
            EnableWindow(hwndchange, FALSE);
            ShowWindow(hwndchange, SW_HIDE);

            EnableWindow(hwndchange, FALSE);
            ShowWindow(hwndchange, SW_HIDE);
            MoveWindow(hwndchange, 300, 500, 200, 100, TRUE);

            EnableWindow(hwndend, FALSE);
            ShowWindow(hwndend, SW_HIDE);
            MoveWindow(hwndend, 280, 500, 200, 100, TRUE);
            //InvalidateRect(hWnd, NULL, TRUE);
            SetFocus(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CREATE:
    {
        SetTimer(hWnd, 3, timestep3, NULL);
        SetTimer(hWnd, 4, timerb, NULL);
        //SetTimer(hWnd, 5, timerpause, NULL);
        //SetCursor(hcur0);
        hwndstart = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 300, 200, 100, hWnd, (HMENU)ID_START, hInst, nullptr);
        hwndend = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 500, 200, 100, hWnd, (HMENU)ID_END, hInst, nullptr);
        hwndeasy = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 100, 200, 100, hWnd, (HMENU)ID_EASY, hInst, nullptr);
        hwndhard = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 300, 200, 100, hWnd, (HMENU)ID_HARD, hInst, nullptr);
        hwndhell = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 500, 200, 100, hWnd, (HMENU)ID_HELL, hInst, nullptr);
        hwndreturn = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 700, 210, 100, hWnd, (HMENU)ID_RETURN, hInst, nullptr);
        hwndrestart = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 50, 500, 220, 100, hWnd, (HMENU)ID_RESTART, hInst, nullptr);
        hwndchange = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 300, 500, 200, 100, hWnd, (HMENU)ID_CHANGE, hInst, nullptr);
        hwndcontinue = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_CLIPSIBLINGS, 280, 500, 250, 100, hWnd, (HMENU)ID_CONTINUE, hInst, nullptr);
        
        //GetWindowRect(hwndstart, &rect);

        EnableWindow(hwndeasy, FALSE);
        ShowWindow(hwndeasy, SW_HIDE);
        EnableWindow(hwndhard, FALSE);
        ShowWindow(hwndhard, SW_HIDE);
        EnableWindow(hwndhell, FALSE);
        ShowWindow(hwndhell, SW_HIDE);
        EnableWindow(hwndreturn, FALSE);
        ShowWindow(hwndreturn, SW_HIDE);
        EnableWindow(hwndrestart, FALSE);
        ShowWindow(hwndrestart, SW_HIDE);
        EnableWindow(hwndchange, FALSE);
        ShowWindow(hwndchange, SW_HIDE);
        EnableWindow(hwndcontinue, FALSE);
        ShowWindow(hwndcontinue, SW_HIDE);

        PlaySound(MAKEINTRESOURCEA(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);//attention
        Sleep(1500);
        PlaySound(MAKEINTRESOURCEA(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);//loop
        //EnableWindow(hwndeasy, FALSE);
        //ShowWindow(hwndeasy, SW_HIDE);
        memset(map, 0, sizeof(map));
    }
        break;
    
    
   
    case WM_DRAWITEM:
        pdis = (LPDRAWITEMSTRUCT)lParam;
        

        switch (pdis->CtlID)
        {
        case ID_START:

           
     
            TextButton(pdis->hDC, start, pdis->rcItem, hwndstart, 200, 100, isStart);
            
            break;
        case ID_END:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, end, pdis->rcItem, hwndend, 200, 100, isEnd);
            //SetCursor(hcur0);
            break;
        case ID_EASY:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, easy, pdis->rcItem, hwndeasy, 200, 100, isEasy);
            break;
        case ID_HARD:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, hard, pdis->rcItem, hwndhard, 200, 100, isHard);
            break;
        case ID_HELL:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, hell, pdis->rcItem, hwndhell, 200, 100, isHell);
            break;
        case ID_RESTART:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, restart, pdis->rcItem, hwndrestart, 200, 100, isRestart);
            break;
        case ID_CHANGE:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, change, pdis->rcItem, hwndchange, 200, 100, isChange);
            break;
        case ID_RETURN:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, retun, pdis->rcItem, hwndreturn, 200, 100, isReturn);
            break;
        case ID_CONTINUE:
            //SetCursor(hcur1);
            TextButton(pdis->hDC, Continue, pdis->rcItem, hwndcontinue, 200, 100, isContinue);
            break;
        default:
            break;
        }

        break;
   


    case WM_SETCURSOR:
        //InvalidateRect(hWnd, NULL, TRUE);
        switch (pcs) {
        case 0:
            if (HIWORD(lParam) == WM_LBUTTONDOWN) {
                SetCursor(hcur1);
                SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur1);
            }
            else {
                SetCursor(hcur0);
                SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur0);
            }
            break;
        default:
            if (IsGameOver() || CannotGenerate()||pause) {
                if (HIWORD(lParam) == WM_LBUTTONDOWN) {
                    SetCursor(hcur1);
                    SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur1);
                }
                else {
                    SetCursor(hcur0);
                    SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur0);
                }
            }
            else {
                if (LOWORD(lParam) == HTCLIENT)
                    SetCursor(NULL);
                else if (LOWORD(lParam) == HTCAPTION) {
                    if (HIWORD(lParam) == WM_LBUTTONDOWN) {
                        SetCursor(hcur1);
                        SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur1);
                    }
                    else {
                        SetCursor(hcur0);
                        SetClassLongPtrA(hwndstart, GCLP_HCURSOR, (LONG)hcur0);
                    }

                }
                    
            }
            break;
            }
        
        break;
    case WM_TIMER:
        //timer = wParam == 1 ? 1 : 2;
        //direction = direction < 3 ? direction + 1 : 0;
        switch (wParam)
        {
        case 1:
            if (!IsGameOver() && !CannotGenerate()) {
                DissappearInMap();
                Down(v);
                ShowInMap();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        case 2:
            if (IsGameOver() || CannotGenerate()) {
                KillTimer(hWnd, 1);
                KillTimer(hWnd, 2);
                Writeinini();
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE10), NULL, SND_RESOURCE | SND_ASYNC);
                Sleep(4000);
                PlaySound(MAKEINTRESOURCEA(IDR_WAVE11), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                EnableWindow(hwndrestart, TRUE);
                ShowWindow(hwndrestart, SW_SHOW);
                EnableWindow(hwndchange, TRUE);
                ShowWindow(hwndchange, SW_SHOW);
                
                

                EnableWindow(hwndend, TRUE);
                ShowWindow(hwndend, SW_SHOW);
                MoveWindow(hwndend, 540, 500, 200, 100, TRUE);
                
            }
            else if (IsBumpDown()) {
                Match();
                r = next;
                if (IsRepeat()) {
                        repeat++;
                        r += repeat * 8;

                        if (repeat > 20)repeat = 0;
                }
                    
                        //r = next;
                  next = rand() % 7 + 1;

                  GenerateRandCube();
                  GenerateNextCube();
                  ShowInMap();
                  InvalidateRect(hWnd, NULL, TRUE);
                    
                        
                
            }
            break;
        case 3:
            direction = direction < 3 ? direction + 1 : 0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 4:
            GetCursorPos(&pnt);
            ScreenToClient(hWnd, &pnt);
            hwndchild = ChildWindowFromPointEx(hWnd, pnt, CWP_SKIPDISABLED);
            if (hwndchild == hwndstart)isStart = TRUE;
            else isStart = FALSE;
            if (hwndchild == hwndend)isEnd = TRUE;
            else isEnd = FALSE;
            if (hwndchild == hwndeasy)isEasy = TRUE;
            else isEasy = FALSE;
            if (hwndchild == hwndhard)isHard = TRUE;
            else isHard = FALSE;
            if (hwndchild == hwndhell)isHell = TRUE;
            else isHell = FALSE;
            if (hwndchild == hwndreturn)isReturn = TRUE;
            else isReturn = FALSE;
            if (hwndchild == hwndrestart)isRestart = TRUE;
            else isRestart = FALSE;
            if (hwndchild == hwndchange)isChange = TRUE;
            else isChange = FALSE;
            if (hwndchild == hwndcontinue)isContinue = TRUE;
            else isContinue = FALSE;
            //InvalidateRect(hWnd, NULL, TRUE);
            break;
        
        default:
            break;
        }

        break;

    case WM_KEYDOWN:
        InvalidateRect(hWnd, NULL, TRUE);
        switch (wParam) {
        case VK_SPACE:
            if (pcs != 0) {
                pause=!pause;
                if (pause) {
                    KillTimer(hWnd, 1);
                    KillTimer(hWnd, 2);
                    //Writeinini();
                    PlaySound(NULL, NULL, SND_FILENAME);
                    //Sleep(4000);
                    //PlaySound(MAKEINTRESOURCEA(IDR_WAVE11), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
                    EnableWindow(hwndrestart, TRUE);
                    ShowWindow(hwndrestart, SW_SHOW);
                    EnableWindow(hwndcontinue, TRUE);
                    ShowWindow(hwndcontinue, SW_SHOW);

                    EnableWindow(hwndchange, TRUE);
                    ShowWindow(hwndchange, SW_SHOW);
                    MoveWindow(hwndchange, 300, 350, 200, 100, TRUE);

                    EnableWindow(hwndend, TRUE);
                    ShowWindow(hwndend, SW_SHOW);
                    MoveWindow(hwndend, 540, 500, 200, 100, TRUE);
                }
                else {
                    SetTimer(hWnd, 1, timestep, NULL);
                    SetTimer(hWnd, 2, timestep2, NULL);
                    //Writeinini();
                    switch (pcs) {
                    case 1:
                        PlaySound(MAKEINTRESOURCEA(IDR_WAVE9), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                        break;
                    case 2:
                        PlaySound(MAKEINTRESOURCEA(IDR_WAVE8), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                        break;
                    case 3:
                        PlaySound(MAKEINTRESOURCEA(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC|SND_LOOP);
                        break;
                    default:
                        break;
                    }
                    //Sleep(4000);
                    //PlaySound(MAKEINTRESOURCEA(IDR_WAVE11), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
                    EnableWindow(hwndrestart, FALSE);
                    ShowWindow(hwndrestart, SW_HIDE);
                    EnableWindow(hwndcontinue, FALSE);
                    ShowWindow(hwndcontinue, SW_HIDE);

                    EnableWindow(hwndchange, FALSE);
                    ShowWindow(hwndchange, SW_HIDE);
                    MoveWindow(hwndchange, 300, 500, 200, 100, FALSE);

                    EnableWindow(hwndend, FALSE);
                    ShowWindow(hwndend, SW_HIDE);
                    MoveWindow(hwndend, 280, 500, 200, 100, FALSE);
                }
            }
            break;
        default:
            if (!pause) {
                PressKey(wParam);
            }
            break;
        }
        break;

    case WM_SIZE:
        wndwidth = LOWORD(lParam);
        wndheight = HIWORD(lParam);
        break;
    case WM_ERASEBKGND:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...

        HDC memhdc = CreateCompatibleDC(hdc);

        RECT rectclient;
        GetClientRect(hWnd, &rectclient);


        HBITMAP bmpbuff = CreateCompatibleBitmap(hdc, wndwidth, wndheight);
        HBITMAP poldbmp = (HBITMAP)SelectObject(memhdc, bmpbuff);
        PatBlt(memhdc, 500, 0, wndwidth, wndheight, BLACKNESS);
        //InvalidateRect(hWnd, NULL, TRUE);
        DrawScene(memhdc);




        if (IsGameOver() || CannotGenerate()) {

            TextGameOver(memhdc);

        }
        //DeleteObject(hFont1);

        BOOL tt = BitBlt(hdc, rectclient.left, rectclient.top, wndwidth, wndheight, memhdc, rectclient.left, rectclient.top, SRCCOPY);

        SelectObject(memhdc, poldbmp);
        DeleteObject(bmpbuff);
        DeleteDC(memhdc);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        KillTimer(hWnd, 3);
        KillTimer(hWnd, 4);
        KillTimer(hWnd, 5);
        //KillTimer(hWnd, 3);
        DeleteObject(bbrush);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


