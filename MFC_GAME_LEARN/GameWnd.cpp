// GameWnd.cpp : 实现文件
//

//#include "stdafx.h"
#include "Game32.h"
#include "GameWnd.h"
#include <iostream>
using namespace std;

int i, x, y, width, height;
int dir,index;
// GameWnd

IMPLEMENT_DYNCREATE(GameWnd, CFrameWnd)

GameWnd::GameWnd()
	//: bitmap(NULL)
	//, mdc(NULL)
{
	Create(NULL, "创建窗口");
	char ch[8];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprintf(ch, "%d.%d.bmp", i + 1,j + 1);
			bitmap[i][j] = new CBitmap;
			bitmap[i][j]->m_hObject = LoadImage(NULL, ch, IMAGE_BITMAP, 64, 96, LR_LOADFROMFILE);
		}
	}
	
	//bitmap = new CBitmap;
	//bitmap->m_hObject = LoadImage(NULL, "1.bmp", IMAGE_BITMAP, 64, 96, LR_LOADFROMFILE);
	mdc = new CDC;
	RECT rc;
	CClientDC dc(this);
	GetClientRect(&rc);
	mdc->CreateCompatibleDC(&dc);
	mdc->SelectObject(bitmap[0][0]);
	i = 0;
	dir = 0;
	index = 0;
	width = rc.right;
	height = rc.bottom;
	x = width/2 - 32;
	y = height /2 - 48;
	dc.BitBlt(x, y, 64, 96, mdc, 0, 0, SRCCOPY);
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
	
	//SetTimer(1, 500, NULL);
	return 0;
}


void GameWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	if (dir >= 4)
	{
		dir = 0;
	}
	if (index<4)
	{
		mdc->SelectObject(bitmap[dir][index]); //[0][0]-1.1.bmp [0][1]-1.2.bmp	[1][3]-2.4.bmp
		index++;
	}
	else
	{
		index = 0;
		dir++;
		mdc->SelectObject(bitmap[dir][index]);
	}
	dc.BitBlt(0, 0, 64, 96, mdc, 0, 0, SRCCOPY);
	CFrameWnd::OnTimer(nIDEvent);
}


void GameWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	dc.BitBlt(x, y, 64, 96, mdc, 0, 0, WHITENESS);
	if (nChar == VK_DOWN)
	{
		if (y > height-96)
		{
			;
		}
		else
		{
			y += 20;
			if (y > height - 96)
			{
				y == height - 96;
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
	if (nChar == VK_LEFT)
	{
		x -= 20;
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
	if (nChar == VK_RIGHT)
	{
		x += 20;
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
	if (nChar == VK_UP)
	{
		y -= 20;
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

	mdc->SelectObject(bitmap[dir][index]);
	dc.BitBlt(x, y, 64, 96, mdc, 0, 0, SRCCOPY);
	cout << dir + 1 << endl;
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
