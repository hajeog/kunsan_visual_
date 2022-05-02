
// schooleTestDoc.h: CschooleTestDoc 클래스의 인터페이스
//


#pragma once


class CschooleTestDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CschooleTestDoc() noexcept;
	DECLARE_DYNCREATE(CschooleTestDoc)

// 특성입니다.
public:
	unsigned char** inputImg;   // 입력 영상의 기억 장소에 대한 포인터 변수 
	unsigned char** inputImg2;   // 입력 영상의 기억 장소에 대한 포인터 변수 
	unsigned char** resultImg;   // 출력 영상의 기억 장소에 대한 포인터 변수 
	int imageWidth;      // 영상의 가로 크기 
	int imageHeight;      // 영상의 세로 크기 
	int depth;         // 1 = 흑백 영상, 3 = 컬러 영상 

	// 결과 영상의 크기가 변화되는 기하학적 처리를 위해 새로이 추가되는 코드 
	int gImageWidth;           // 크기가 변한 결과 영상의 가로 크기 
	int gImageHeight;           // 크기가 변한 결과 영상의 세로 크기 
	unsigned char** gResultImg;  // 크기가 변한 결과 영상에 대한 포인터 변수 

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CschooleTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void PixelAdd();
	void PixelDown();
	void PixeIHistoEq();
	void PixeITwoImageAdd();
	void LoadTwoImages();
	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
	void RegionSharpening();
	void Convolve(unsigned char** inputImg, unsigned char** resultImg, int cols, int rows, float mask[][3], int bias, int depth);
	void RegionMeaning();
	void RegionSobel();
	void FiendDirke();
	void IMEGAERESEVE();
	void IMEGAMBOSING();
	void GeometryZoominPixelCopy();
	void GeometryZoominInterpolation();
	void GeometryZoomoutSubsampling();
	void GeometryZoomoutAvg();
	void GeometryRotate();
};
