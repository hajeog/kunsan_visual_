
// schooleTestDoc.cpp: CschooleTestDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "schooleTest.h"
#endif

#include "schooleTestDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CschooleTestDoc

IMPLEMENT_DYNCREATE(CschooleTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CschooleTestDoc, CDocument)
END_MESSAGE_MAP()

#define PI 3.14159
// CschooleTestDoc 생성/소멸

CschooleTestDoc::CschooleTestDoc() noexcept
{
	// TODO: add one-time construction code here 
	inputImg = NULL;
	inputImg2 = NULL;
	resultImg = NULL;
	gResultImg = NULL;     // 추가되는 코드 

}

CschooleTestDoc::~CschooleTestDoc()
{
}

BOOL CschooleTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CschooleTestDoc serialization

void CschooleTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CschooleTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CschooleTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CschooleTestDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CschooleTestDoc 진단

#ifdef _DEBUG
void CschooleTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CschooleTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CschooleTestDoc 명령


void CschooleTestDoc::PixelAdd()
{
	int value = 0;

	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] + 100;
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}

}


void CschooleTestDoc::PixelDown()
{
	int value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++){
			value = inputImg[x][y] - 100;
			if (value < 0)resultImg[x][y] = 0;
			else resultImg[x][y] = value;
		}

	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::PixeIHistoEq()
{
	int x, y, j,i, k;
	int acc_hist = 0;
	float N = 256 * 256;
	int hist[256], sum[256];

	for (k = 0; k < 256; k++)hist[k] = 0;

	for(y=0;y<256;y++)
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			hist[k] = hist[k] + 1;
		}
	for (i = 0; i < 256; i++){
		acc_hist = acc_hist + hist[i];
		sum[i] = acc_hist;
	}
	for(y=0;y<256;y++)
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			resultImg[y][x] = sum[k] / N * 255;
		}
	
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::PixeITwoImageAdd()
{
	int value = 0;
	LoadTwoImages();
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x] + inputImg2[y][x];
			if (value > 255) resultImg[y][x] = 255;
			else resultImg[y][x] = value;
		}

	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::LoadTwoImages()
{
	CFile file;
	CFileDialog dlg(TRUE);

	AfxMessageBox("첫번째 영상을 선택하시오");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadImageFile(ar);
		file.Close();
	}

	AfxMessageBox("두번째 영상을 선택하시오");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();
	}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	CString type, buf;
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	// 파일의 헤더 읽기 
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 || strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type);
		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);
		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
		strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}
	// 기억장소 할당 
	inputImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImg[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	// 영상 데이터 읽기 
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImg[i], imageWidth * depth);
}


void CschooleTestDoc::LoadSecondImageFile(CArchive &ar)
{
	int i, maxValue;
	CString type, buf;
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();


	// 파일의 헤더 읽기 
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 ||
		strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type);
		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do {
			ar.ReadString(buf);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
		strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}

	// 기억장소 할당
	inputImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		inputImg2[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	// 영상 데이터 읽기 
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImg2[i], imageWidth * depth);
}


void CschooleTestDoc::RegionSharpening()
{
	float kernel[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };

	Convolve(inputImg, resultImg, imageWidth, imageHeight, kernel, 0, depth);

	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::Convolve(unsigned char** inputImg,unsigned char** resultImg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int i, j, x, y;
	int red, green, blue;
	int sum;
	unsigned char** tmpImg;
	// 기억장소 할당 
	tmpImg = (unsigned char**)malloc((imageHeight + 2) * sizeof(unsigned char*));

	for (i = 0; i < imageHeight + 2; i++)
		tmpImg[i] = (unsigned char*)malloc((imageWidth + 2) * depth);
	// 0-삽입을 위해 0으로 초기화 
	for (y = 0; y < imageHeight + 2; y++)
		for (x = 0; x < (imageWidth + 2) * depth; x++)
			tmpImg[y][x] = 0;

	// 영상 복사 
	for (y = 1; y < imageHeight + 1; y++)
		for (x = 1; x < imageWidth + 1; x++)
			if (depth == 1) tmpImg[y][x] = inputImg[y - 1][x - 1];
			else if (depth == 3) {
				tmpImg[y][3 * x] = inputImg[y - 1][3 * (x - 1)];
				tmpImg[y][3 * x + 1] = inputImg[y - 1][3 * (x - 1) + 1];
				tmpImg[y][3 * x + 2] = inputImg[y - 1][3 * (x - 1) + 2];
			}
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						sum += (int)(tmpImg[y + i][x + j] * mask[i][j]);

				sum = sum + bias;

				if (sum > 255) sum = 255;
				if (sum < 0) sum = 0;
				resultImg[y][x] = (unsigned char)sum;
			}
			else if (depth == 3) {
				red = 0;
				green = 0;
				blue = 0;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++) {
						red += (int)(tmpImg[y + i][3 * (x + j)] * mask[i][j]);
						green += (int)(tmpImg[y + i][3 * (x + j) + 1] * mask[i][j]);
						blue += (int)(tmpImg[y + i][3 * (x + j) + 2] * mask[i][j]);
					}
				red = red + bias;
				green = green + bias;
				blue = blue + bias;

				if (red > 255) red = 255;
				if (red < 0) red = 0;
				if (green > 255) green = 255;
				if (green < 0) green = 0;
				if (blue > 255) blue = 255;
				if (blue < 0) blue = 0;
				resultImg[y][3 * x] = (unsigned char)red;
				resultImg[y][3 * x + 1] = (unsigned char)green;
				resultImg[y][3 * x + 2] = (unsigned char)blue;
			}
		}

	// 기억장소 반환 
	for (i = 0; i < imageHeight + 2; i++) free(tmpImg[i]);
	free(tmpImg);
}


void CschooleTestDoc::RegionMeaning() // 영상 흐리게 만들기
{
	float mask[3][3] = { {1 / 9.0f,1 / 9.0f,1 / 9.0f},
						 {1 / 9.0f,1 / 9.0f,1 / 9.0f},
					   	 {1 / 9.0f,1 / 9.0f,1 / 9.0f} };
	Convolve(inputImg, resultImg, imageWidth, imageHeight, mask, 0, depth);
}


void CschooleTestDoc::RegionSobel() // 컨블루션
{
	int i, x, y, sum;
	float mask1[3][3] = { 1,0,-1,
						  2,0,-2,
						  1,0,-1 };
	float mask2[3][3] = {-1, -2, -1, 
						  0, 0, 0, 
						  1, 2, 1};
	
	unsigned char** Er, ** Ec;

	Er = (unsigned char **)malloc((imageHeight) * sizeof(unsigned char *));
	Ec = (unsigned char **)malloc((imageHeight) * sizeof(unsigned char *));

	for (i = 0; i < imageHeight; i++) {
		Er[i] = (unsigned char *)malloc(imageWidth * depth);
		Ec[i] = (unsigned char *)malloc(imageWidth * depth);
	}
	Convolve(inputImg, Er, imageWidth, imageHeight, mask1, 0, depth);
	Convolve(inputImg, Ec, imageWidth, imageHeight, mask2, 0, depth);
	
	for(y=0;y<imageHeight;y++)
		for (x = 0; x < imageWidth * depth; x++) {
			sum = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (sum > 255)sum = 255;
			if (sum < 0)sum = 0;
			resultImg[y][x] = (unsigned)sum;
		}
}


void CschooleTestDoc::FiendDirke() // 영상 이진화
{
	int value = 0;
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			value = inputImg[y][x];
			if (value > 128) resultImg[y][x] = 255;
			else if (value < 127) resultImg[y][x] = 0;
			else resultImg[y][x] = value;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::IMEGAERESEVE() // 영상 역변화
{
	int value = 255;
	int Resive = 0;
	for (int y = 0; y < imageHeight; y++)
		for (int x = 0; x < imageWidth * depth; x++) {
			Resive = value-inputImg[y][x];
			if (Resive < 0)resultImg[y][x] = 0;
			else resultImg[y][x] = Resive;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::IMEGAMBOSING() // 엠보싱 마스크
{
	
	//Convolve(inputImg, resultImg, imageWidth, imageHeight, mask, 0, depth);

	//
	int i, x, y, sum;
	float mask1[3][3] = { {-1,0,0},
						  {0,0,0},
						  {0,0,1} };
	float mask2[3][3] = { {-1,0,0},
						  {0,0,0},
						  {0,0,1} };

	unsigned char** Er, ** Ec;

	Er = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(imageWidth * depth);
		Ec[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	Convolve(inputImg, Er, imageWidth, imageHeight, mask1, 0, depth);
	Convolve(inputImg, Ec, imageWidth, imageHeight, mask2, 0, depth);

	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth * depth; x++) {
			sum = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (sum > 255)sum = 255;
			if (sum < 0)sum = 0;
			resultImg[y][x] = (unsigned)sum;
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::GeometryZoominPixelCopy()
{// 확대
	int i, j, k,y;
	gImageWidth = imageWidth * 3;
	gImageHeight = imageHeight * 3;
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}
	for (y = 0; y < gImageHeight; y++) {
		for (int x = 0; x < gImageWidth; x++) {
			gResultImg[y][x] = inputImg[y / 3][x / 3];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::GeometryZoominInterpolation()
{// 양선형 보간법
	int i, y, x;
	float src_x, src_y;      // 원시 화소 위치  
	float alpha, beta;
	int scale_x, scale_y;       // float  scale_x, scale_y; 
	int E, F;              // x 방향으로 보간된 결과 값 
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy; // 보간에 사용될 4개 픽셀의 좌표 
	scale_x = 3;
	scale_y = 3;

	// 결과 영상의 크기 설정 
	gImageWidth = imageWidth * scale_x;
	gImageHeight = imageHeight * scale_y;
	// 결과 영상을 저장할 기억장소 공간 할당 
	gResultImg = (unsigned char**)malloc(gImageHeight *
		sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	for (y = 0; y < gImageHeight; y++)
		for (x = 0; x < gImageWidth; x++) {
			// 원시 영상에서의 픽셀 좌표 계산 
			src_x = x / (float)scale_x;        // src_x = x / scale_x; 
			src_y = y / (float)scale_y;        // src_y = y / scale_y; 
			alpha = src_x - x / scale_x;      // alpha = src_x – (int) src_x; 
			beta = src_y - y / scale_y;       // beta = src_y – (int) src_y; 
			 // 보간에 사용된 4 픽셀의 좌표 계산 
			Ax = x / scale_x;
			Ay = y / scale_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			// 픽셀 위치가 영상의 경계를 벗어나는지 검사 
			if (Bx > imageWidth - 1) Bx = imageWidth - 1;
			if (Dx > imageWidth - 1) Dx = imageWidth - 1;
			if (Cy > imageHeight - 1) Cy = imageHeight - 1;
			if (Dy > imageHeight - 1) Dy = imageHeight - 1;
			// x 방향으로 보간 
			E = (int)(inputImg[Ay][Ax] * (1 - alpha) + inputImg[By][Bx] * alpha);
			F = (int)(inputImg[Cy][Cx] * (1 - alpha) + inputImg[Dy][Dx] * alpha);
			// y 방향으로 보간 
			gResultImg[y][x] = (unsigned char)(E * (1 - beta) + F * beta);
		}
	// TODO: 여기에 구현 코드 추가.
}

void CschooleTestDoc::GeometryZoomoutSubsampling()
{
	int i, y, x;
	int src_x, src_y;
	int scale_x = 3, scale_y = 3;

	// 결과 영상의 크기 계산 
	gImageWidth = (imageWidth % scale_x == 0) ? imageWidth / scale_x : imageWidth / scale_x + 1;
	gImageHeight = (imageHeight % scale_y == 0) ? imageHeight / scale_y : imageHeight / scale_y + 1;

	// 결과 영상 저장을 위한 기억장소 할당 
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}
	for (y = 0; y < gImageHeight; y++)
		for (x = 0; x < gImageWidth; x++) {
			src_y = y * scale_y;
			src_x = x * scale_x;

			gResultImg[y][x] = inputImg[src_y][src_x];
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::GeometryZoomoutAvg()
{
	int i, j, x, y;
	int sum;
	int src_x, src_y;
	int scale_x = 3, scale_y = 3;

	// 결과 영상의 크기 계산 
	gImageWidth = (imageWidth % scale_x == 0) ? imageWidth / scale_x : imageWidth / scale_x + 1;
	gImageHeight = (imageHeight % scale_y == 0) ? imageHeight / scale_y : imageHeight / scale_y + 1;
	// 결과 영상을 저장할 기억장소 할당 
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}
	for (y = 0; y < imageHeight; y = y + scale_y)
		for (x = 0; x < imageWidth; x = x + scale_x) {
			// 필터 윈도우 내의 픽셀값 합계 계산 
			sum = 0;
			for (i = 0; i < scale_y; i++)
				for (j = 0; j < scale_x; j++) {
					src_x = x + j;
					src_y = y + i;
					if (src_x > imageWidth - 1) src_x = imageWidth - 1;    // 영상의 경계  검사 
					if (src_y > imageHeight - 1) src_y = imageHeight - 1;
					sum += inputImg[src_y][src_x];
				}
			sum = sum / (scale_x * scale_y);  // 평균값 계산 

			gResultImg[y / scale_y][x / scale_x] = (unsigned char)sum; // 결과 값 저장 
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::GeometryRotate()
{
	int y, x, x_source, y_source, Cx, Cy;
	float angle;
	int Oy;
	int i, xdiff, ydiff;

	Oy = imageHeight - 1;

	angle = PI / 180.0 * 30.0;   // 30도를 라디안 값의 각도로 변환 !만약 회전각을 조절하고 싶으면 해당 부분 수정하면 된다.

	Cx = imageWidth / 2;   // 회전 중심의 x좌표 
	Cy = imageHeight / 2;   // 회전 중심의 y좌표 
	  // 결과 영상 크기 계산 
	gImageWidth = (int)(imageHeight * cos(PI / 2.0 - angle) + imageWidth * cos(angle));
	gImageHeight = (int)(imageHeight * cos(angle) + imageWidth * cos(PI / 2.0 - angle));

	// 결과 영상을 저장할 기억장소 할당 
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	// 결과 영상의 x 좌표 범위 : -xdiff ~ gImageWidth - xdiff - 1 
// 결과 영상의 y 좌표 범위 : -ydiff ~ gImageHeight - ydiff - 1 
	xdiff = (gImageWidth - imageWidth) / 2;
	ydiff = (gImageHeight - imageHeight) / 2;

	for (y = -ydiff; y < gImageHeight - ydiff; y++)
		for (x = -xdiff; x < gImageWidth - xdiff; x++)
		{
			// 변환 단계 
			//     1 단계 : 원점이 영상의 좌측 하단에 오도록 y 좌표 변환 
			//     2 단계 : 회전 중심이 원점에 오도록 이동 
			//     3 단계 : 각도 angle 만큼 회전 
			//     4 단계 : 회전 중심이 원래 위치로 돌아가도록 이동 
			x_source = (int)(((Oy - y) - Cy) * sin(angle) + (x - Cx) * cos(angle) + Cx);
			y_source = (int)(((Oy - y) - Cy) * cos(angle) - (x - Cx) * sin(angle) + Cy);

			//     5 단계 : 원점이 영상의 좌측 상단에 오도록 y 좌표 변환 
			y_source = Oy - y_source;
			if (x_source < 0 || x_source > imageWidth - 1 ||
				y_source < 0 || y_source > imageHeight - 1)
				gResultImg[y + ydiff][x + xdiff] = 255;
			else
				gResultImg[y + ydiff][x + xdiff] = inputImg[y_source][x_source];
		}
	// TODO: 여기에 구현 코드 추가.
}



void CschooleTestDoc::Erosion() // 침식 연산 부분 입니다.
{
	int x, y, min, i, j;

	for (y = 1; y < imageHeight - 1; y++) {
		for (x = 1; x < imageWidth - 1; x++) {
			min = 255;
			if (inputImg[y - 1][x - 1] < min) min = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] < min) min = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] < min) min = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] < min) min = inputImg[y][x - 1];
			if (inputImg[y][x] < min) min = inputImg[y][x];
			if (inputImg[y][x + 1] < min) min = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] < min) min = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] < min) min = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] < min) min = inputImg[y + 1][x + 1];
			resultImg[y][x] = min;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::Dilation() // 팽창 연산 부분 입니다.
{
	int x, y, max, i, j;
	for (y = 1; y < imageHeight - 1; y++)
		for (x = 1; x < imageWidth - 1; x++) {
			max = 0;
			if (inputImg[y - 1][x - 1] > max) max = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] > max) max = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] > max) max = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] > max) max = inputImg[y][x - 1];
			if (inputImg[y][x] > max) max = inputImg[y][x];
			if (inputImg[y][x + 1] > max) max = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] > max) max = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] > max) max = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] > max) max = inputImg[y + 1][x + 1];

			resultImg[y][x] = max;   // 최대값을 결과 영상에 저장 
		}
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::Opening() // 열림 연산 부분 입니다
{
	Erosion();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Erosion();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Dilation();
	CopyResultToInput();
	Dilation();
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::CopyResultToInput()
{
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg[y][x] = resultImg[y][x];
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::RollImage()
{
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			resultImg[imageHeight - 1 - y][x] = inputImg[y][x];
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::ROLLUPDOWN()
{
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			resultImg[y][x] = inputImg[y][imageWidth - 1 - x];
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::SMALLINGROOL(int height, int width, float zoominfactor)
{
	BYTE *pZoomIng;
	BYTE newValue;
	int new_height = (int)(height * zoominfactor);
	int new_withe = (int)(width * zoominfactor);
	int heightml = height - 1;
	int widthml = width - 1;
	int where, org_where;
	int r, c;// img 좌표
	float r_orgr,r_orgc;
	int i_orgr, i_orgc;
	float sr, sc;
	float I1, I2, I3, I4;

	// ZoomImange 의 동적 할당
	pZoomIng = new BYTE[new_height * new_withe];

	for(r = 0 ; r<new_height;r++)
		for (c = 0; c < new_withe; c++) {
			r_orgr = r / zoominfactor;
			r_orgc = c / zoominfactor;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;

			if (i_orgr<0 || i_orgr>heightml || i_orgc<0 || i_orgc>widthml) {
				where = r * new_withe + c;
				pZoomIng[where] = 0;
			}
			else {
				I1 = (float)inputImg[i_orgr][i_orgc];
				I2 = (float)inputImg[i_orgr][i_orgc + 1];
				I3 = (float)inputImg[i_orgr + 1][i_orgc + 1];
				I4 = (float)inputImg[i_orgr + 1][i_orgc];

				newValue = (BYTE)(I1 * (1 - sc) * (1 - sr) + I2 * sc * (1 - sr) + I3 * sc * sr + I4 * (1 - sc) * sr);
				where = r * new_withe + c;
				pZoomIng[where] = newValue;
			}
		}
	for(r = 0;r<height;r++)
		for (c = 0; c < width; c++) {
			resultImg[r][c] = pZoomIng[r * new_withe + c];
		}

	delete[] pZoomIng;
	// TODO: 여기에 구현 코드 추가.
}


void CschooleTestDoc::SMMALSUBBOOK(int height, int width, float zoomoutfacttor)
{
	BYTE* pZoomIng;
	BYTE newValue;
	int new_height = (int)(height * zoomoutfacttor);
	int new_withe = (int)(width * zoomoutfacttor);
	int heightml = height - 1;
	int widthml = width - 1;
	int where, org_where;
	int r, c;// img 좌표
	float r_orgr, r_orgc;
	int i_orgr, i_orgc;
	float sr, sc;
	float I1, I2, I3, I4;

	// ZoomImange 의 동적 할당
	pZoomIng = new BYTE[new_height * new_withe];

	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_withe; c++) {
			r_orgr = r / zoomoutfacttor;
			r_orgc = c / zoomoutfacttor;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;

			if (i_orgr<0 || i_orgr>heightml || i_orgc<0 || i_orgc>widthml) {
				where = r * new_withe + c;
				pZoomIng[where] = 0;
			}
			else {
				I1 = (float)inputImg[i_orgr][i_orgc];
				I2 = (float)inputImg[i_orgr][i_orgc + 1];
				I3 = (float)inputImg[i_orgr + 1][i_orgc + 1];
				I4 = (float)inputImg[i_orgr + 1][i_orgc];

				newValue = (BYTE)(I1 * (1 - sc) * (1 - sr) + I2 * sc * (1 - sr) + I3 * sc * sr + I4 * (1 - sc) * sr);
				where = r * new_withe + c;
				pZoomIng[where] = newValue;
			}
		}
	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_withe; c++) {
			resultImg[r][c] = pZoomIng[r * new_withe + c];
		}

	delete[] pZoomIng;
	// TODO: 여기에 구현 코드 추가.
}
