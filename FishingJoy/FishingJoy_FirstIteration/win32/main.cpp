#include "main.h"
#include "../Classes/AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;   //相当于： #include功能

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(580, 360);
	return CCApplication::sharedApplication()->run();
}
