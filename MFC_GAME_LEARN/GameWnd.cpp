// GameWnd.cpp : 实现文件
//

//#include "stdafx.h"
#include "Game32.h"
#include "GameWnd.h"
#include <iostream>
using namespace std;

int i, x, y, width, height;
int dir,index;
int t1;
int fps1;
CString st;
// GameWnd

IMPLEMENT_DYNCREATE(GameWnd, CFrameWnd)

GameWnd::GameWnd()
	//: player(NULL)
	//, mdc(NULL)
{
	Create(NULL, "草泥马逼得");
	char ch[8];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprintf(ch, "%d.%d.bmp", i + 1,j + 1);
			player[i][j] = new CBitmap;
			player[i][j]->m_hObject = LoadImage(NULL, ch, IMAGE_BITMAP, 64, 96, LR_LOADFROMFILE);
		}
	}
	
	mdc = new CDC;
	RECT rc;
	CClientDC dc(this);
	GetClientRect(&rc);
	mdc->CreateCompatibleDC(&dc);
	//mdc->SelectObject(player[0][0]);
	i = 0;
	dir = 0;
	index = 0;
	width = rc.right;
	height = rc.bottom;
	x = width/2 - 32;
	y = height /2 - 48;
	int t1 = 0;
	int fps1 = 1;
	CString st = "";
	ground = new CBitmap;
	ground->m_hObject = LoadImage(NULL, "groud1.bmp", IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	//dc.BitBlt(x, y, 64, 96, mdc, 0, 0, SRCCOPY);
}

GameWnd::~GameWnd()
{
}


BEGIN_MESSAGE_MAP(GameWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// GameWnd 消息处理程序


void GameWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//if (i>0)
	//{
	mdc->SelectObject(ground);
	dc.BitBlt(0, 0, width, height, mdc, 0, 0, SRCCOPY);
	mdc->SelectObject(player[0][0]);
	dc.BitBlt(x , y, 64, 96, mdc, 0, 0, SRCCOPY);

	//}
	//else
	//{
	//	i = 0;
	//}
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
}


int GameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	SetTimer(1, 20, NULL);
	return 0;
}


void GameWnd::OnTimer(UINT_PTR nIDEvent)
{

	//st = "fps:" + fps1;
	
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	fps1++;
	if (fps1 * 20 >= 1000)
	{
		fps1 = 1;
		t1++;
	}
	st.Format(_T("FPS:%.2d  TIME:%2d"), fps1, t1);
	dc.TextOut(width/2, 10, st);
	//OnKeyDown();
	CFrameWnd::OnTimer(nIDEvent);
}

//测试原地播放各方向动画的
//void GameWnd::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CClientDC dc(this);
//	if (dir >= 4)
//	{
//		dir = 0;
//	}
//	if (index<4)
//	{
//		mdc->SelectObject(player[dir][index]); //[0][0]-1.1.bmp [0][1]-1.2.bmp	[1][3]-2.4.bmp
//		index++;
//	}
//	else
//	{
//		index = 0;
//		dir++;
//		mdc->SelectObject(player[dir][index]);
//	}
//	dc.BitBlt(0, 0, 64, 96, mdc, 0, 0, SRCCOPY);
//	CFrameWnd::OnTimer(nIDEvent);
//}


void GameWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	dc.BitBlt(x, y, 64, 96, mdc, 0, 0, WHITENESS);
	if (nChar == VK_DOWN || nChar == VK_S)
	{
		if (y > height-96)
		{
			;
		}
		else
		{
			y += 20;
			if (y >= height - 96)
			{
				y = height - 96 - 20;
			}
		}
		if (dir == 0)
		{
			index++;
			if (index == 4)
			{
				index = 0;
			}
		}
		else
		{
			dir = 0;
			index = 0;
		}
	}
	if (nChar == VK_LEFT || nChar == VK_A)
	{
		if (x < 0)
		{
			;
		}
		else
		{
			x -= 20;
			if (x <= 0)
			{
				x = 0 + 20;
			}
		}
		if (dir == 1)
		{
			index++;
			if (index == 4)
			{
				index = 0;
			}
		}
		else
		{
			dir = 1;
			index = 0;
		}
	}
	if (nChar == VK_RIGHT || nChar == VK_D)
	{
		if (x > width - 64)
		{
			;
		}
		else
		{
			x += 20;
			if (x >= width - 64)
			{
				x = width - 64 - 20;
			}
		}
		if (dir == 2)
		{
			index++;
			if (index == 4)
			{
				index = 0;
			}
		}
		else
		{
			dir = 2;
			index = 0;
		}
	}
	if (nChar == VK_UP || nChar == VK_W)
	{
		if (y < 0)
		{
			;
		}
		else
		{
			y -= 20;
			if (y <= 0)
			{
				y = 0+20;
			}
		}
		if (dir == 3)
		{
			index++;
			if (index == 4)
			{
				index = 0;
			}
		}
		else
		{
			dir = 3;
			index = 0;
		}
	}

	mdc->SelectObject(player[dir][index]);
	dc.BitBlt(x, y, 64, 96, mdc, 0, 0, SRCCOPY);
	cout << dir + 1 << endl;
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
