#include "GameApp.h"
//#include "Game32.h"
#include "GameWnd.h"


GameApp myApp;
BOOL GameApp::InitInstance()
{
	m_pMainWnd = new GameWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

GameApp::GameApp()
{

}


GameApp::~GameApp()
{
}
