#pragma once


// GameWnd 框架

class GameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(GameWnd)
public:
	GameWnd();           // 动态创建所使用的受保护的构造函数
	virtual ~GameWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// Bitmap
	CBitmap* bitmap[4][4];
	//CBitmap* bitmap;
	CDC* mdc;
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


