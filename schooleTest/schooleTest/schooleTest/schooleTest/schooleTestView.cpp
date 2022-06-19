
// schooleTestView.cpp: CschooleTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "schooleTest.h"
#endif

#include "schooleTestDoc.h"
#include "schooleTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES 1
#define THREE_IMAGES 2
#define TWO_IMAGES_SCALED   4 
#define MORPHING           8 

// CschooleTestView

IMPLEMENT_DYNCREATE(CschooleTestView, CScrollView)

BEGIN_MESSAGE_MAP(CschooleTestView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CschooleTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PRINT_HELLO, &CschooleTestView::OnPrintHello)
	ON_COMMAND(ID_PIXEL_ADD, &CschooleTestView::OnPixelAdd)
	ON_COMMAND(ID_PIXSEL_DOWN, &CschooleTestView::OnPixselDown)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CschooleTestView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_IMAGE_ADD, &CschooleTestView::OnPixelImageAdd)
	ON_COMMAND(ID_REGION_SHAPENING, &CschooleTestView::OnRegionShapening)
	ON_COMMAND(ID_REGION_MEANING, &CschooleTestView::OnRegionMeaning)
	ON_COMMAND(ID_REGION_SOBEL, &CschooleTestView::OnRegionSobel)
	ON_COMMAND(ID_PINEND_DIERK, &CschooleTestView::OnPinendDierk)
	ON_COMMAND(ID_RESIVE_EMEGES, &CschooleTestView::OnResiveEmeges)
	ON_COMMAND(ID_AMBOSING_MASK, &CschooleTestView::OnAmbosingMask)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CschooleTestView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CschooleTestView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CschooleTestView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CschooleTestView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CschooleTestView::OnGeometryRotate)
	ON_COMMAND(ID_EROSION, &CschooleTestView::OnErosion)
	ON_COMMAND(ID_DILATION, &CschooleTestView::OnDilation)
	ON_COMMAND(ID_OPENING, &CschooleTestView::OnOpening)
	ON_COMMAND(ID_IMAGEROLL, &CschooleTestView::OnImageroll)
	ON_COMMAND(ID_IMAGEUPSIDEDOWN, &CschooleTestView::OnImageupsidedown)
	ON_COMMAND(ID_IMG_SMALLING_ROLL, &CschooleTestView::OnImgSmallingRoll)
	ON_COMMAND(ID_SUBEBOOK_SMALLING, &CschooleTestView::OnSubebookSmalling)
	ON_COMMAND(IDM_FOLOING_ODERS, &CschooleTestView::OnFoloingOders)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CschooleTestView::OnGeometryWarping)
	ON_COMMAND(ID_GEOMETRY_MORPHING, &CschooleTestView::OnGeometryMorphing)
END_MESSAGE_MAP()

// CschooleTestView 생성/소멸

CschooleTestView::CschooleTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CschooleTestView::~CschooleTestView()
{
}

BOOL CschooleTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CschooleTestView 그리기

void CschooleTestView::OnDraw(CDC* pDC)
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	if (pDoc->inputImg == NULL) return;

	if (pDoc->depth == 1) {
		for (int y = 0; y < pDoc->imageHeight; y++)       // 입력 영상 출력 
			for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
					pDoc->inputImg[y][x],
					pDoc->inputImg[y][x]));
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}
		else if (viewMode == MORPHING) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
			for (int i = 0; i < 10; i++)
				for (int y = 0; y < pDoc->imageHeight; y++)       // 모핑 결과 출력 
					for (int x = 0; x < pDoc->imageWidth; x++)
						pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
							RGB(pDoc->morphedImg[i][y][x],
								pDoc->morphedImg[i][y][x],
								pDoc->morphedImg[i][y][x]));
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}
	}
	else if (pDoc->depth == 3) {
		for (int y = 0; y < pDoc->imageHeight; y++)       // 입력 영상 출력 
			for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x],
					pDoc->inputImg[y][3 * x + 1],
					pDoc->inputImg[y][3 * x + 2]));
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째 입력 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][3 * x],
							pDoc->inputImg2[y][3 * x + 1],
							pDoc->inputImg2[y][3 * x + 2]));
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][3 * x],
							pDoc->resultImg[y][3 * x + 1],
							pDoc->resultImg[y][3 * x + 2]));
		}
		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight; y++)   // 크기가 변한 결과 영상 출력 
				for (int x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->gResultImg[y][3 * x],
							pDoc->gResultImg[y][3 * x + 1],
							pDoc->gResultImg[y][3 * x + 2]));
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 결과 영상 출력 
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->resultImg[y][3 * x],
							pDoc->resultImg[y][3 * x + 1],
							pDoc->resultImg[y][3 * x + 2]));
		}
	}
}


void CschooleTestView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CschooleTestView 인쇄


void CschooleTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CschooleTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CschooleTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CschooleTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CschooleTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CschooleTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CschooleTestView 진단

#ifdef _DEBUG
void CschooleTestView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CschooleTestView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CschooleTestDoc* CschooleTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CschooleTestDoc)));
	return (CschooleTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CschooleTestView 메시지 처리기


void CschooleTestView::OnPrintHello()
{
	AfxMessageBox("안녕하세요");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnPixelAdd()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return; // 추가된 문장: 입력 영상이 있는지 검사 

	pDoc->PixelAdd();

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnPixselDown()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelDown();

	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnPixelHistoEq()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixeIHistoEq();

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnPixelImageAdd()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixeITwoImageAdd();
	viewMode = THREE_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnRegionShapening()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	pDoc->RegionSharpening();

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnRegionMeaning()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->RegionMeaning();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnRegionSobel()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;

	pDoc->RegionSobel();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnPinendDierk()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;

	pDoc->FiendDirke();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnResiveEmeges()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;

	pDoc->IMEGAERESEVE();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnAmbosingMask() // 엠보싱 마스크
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;

	pDoc->IMEGAMBOSING();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryZoominPixelCopy()
{// 확대(픽셀 복제)
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->GeometryZoominPixelCopy();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryZoominInterpolation()
{//양선형 보간법
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->GeometryZoominInterpolation();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryZoomoutSubsampling()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutSubsampling();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryZoomoutAvg()
{// 평균값 필터링
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutAvg();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryRotate()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryRotate();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}



void CschooleTestView::OnErosion() // 침식 연산 부분 입니다.
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->Erosion();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnDilation() // 팽창 연산 부분 입니다.
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->Dilation();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnOpening() // 열림 연산 부분 입니다.
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->Opening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnImageroll() // 상하 대칭
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->RollImage();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnImageupsidedown()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->ROLLUPDOWN();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnImgSmallingRoll()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->SMALLINGROOL(256,256,1.3);
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnSubebookSmalling()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->SMMALSUBBOOK(256, 256, 0.7);
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnFoloingOders()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->m_BorderFollow();
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryWarping()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->GeometryWarping();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CschooleTestView::OnGeometryMorphing()
{
	CschooleTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->GeometryMorphing();
	viewMode = MORPHING;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
