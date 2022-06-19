// CSliderDlg.cpp: 구현 파일
//


#include "pch.h"
#include "schooleTest.h"
#include "afxdialogex.h"
#include "CSliderDlg.h"
#include "schooleTestDoc.h"




// CSliderDlg 대화 상자

IMPLEMENT_DYNAMIC(CSliderDlg, CDialogEx)

CSliderDlg::CSliderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CSliderDlg::~CSliderDlg()
{
}

void CSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_add_slider);
	DDX_Control(pDX, IDC_SLIDER1, m_add_sliedersa);
}


BEGIN_MESSAGE_MAP(CSliderDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSliderDlg::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// CSliderDlg 메시지 처리기


BOOL CSliderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here 
	m_add_sliedersa.SetRange(0, 255);
	m_add_sliedersa.SetPos(100);
	
	 return TRUE;
}

void CSliderDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// pFrame : 메인 윈도우에 대한 포인터 
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);

	CschooleTestDoc* pDoc;

	// GetActiveFrame()  : 현재 활성화된 윈도우에 대한 포인터를 반환 
	// GetActiveDocument()  : 현재 윈도우의 문서 객체에 대한 포인터를 반환 
	pDoc = (CschooleTestDoc*)pFrame->GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);

	// GetPos() 함수 : 슬라이더의 현재 위치를 0에서 255 사이의 값 반환 
	pDoc->PixelAddValue(m_add_sliedersa.GetPos());
	*pResult = 0;

}
