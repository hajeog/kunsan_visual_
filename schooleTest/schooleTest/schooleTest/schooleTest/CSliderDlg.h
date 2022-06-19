#include "MainFrm.h" 
#pragma once
#include "afxdialogex.h"


// CSliderDlg 대화 상자

class CSliderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSliderDlg)

public:
	CSliderDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSliderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_add_slider;
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_add_sliedersa;
};
