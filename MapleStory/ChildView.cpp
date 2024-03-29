﻿
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MapleStory.h"
#include "ChildView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	Gdiplus::Graphics MainG(dc);
	MainG.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighSpeed);

	CRect rc;
	GetClientRect(rc);
	Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());

	Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Graphics MemG(&BackBuffer);
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 51, 102, 204));
	MemG.FillRectangle(&whiteBrush, 0, 0, rc.Width(), rc.Height());
	// Scene 렌더

	BATCHRENDER->Draw(&MemG);


	ROAD->Render(&MemG);

	SceneManager::GetInstance().RenderScene(&MemG);
	//CachedBitmap cB(&BackBuffer, &MainG);

	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());
	//MainG.DrawCachedBitmap(&cB, 0, 0);

	BATCHRENDER->DrawEnd();

	CMapleStoryApp::bRender = true;
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	srand((unsigned int)time(NULL));
	SoundManager->InitSound();
	SoundManager->LoadSound();
	SceneManager::GetInstance().LoadScene("GameScene");
	AfxBeginThread(&CMapleStoryApp::funcThread, NULL);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}
