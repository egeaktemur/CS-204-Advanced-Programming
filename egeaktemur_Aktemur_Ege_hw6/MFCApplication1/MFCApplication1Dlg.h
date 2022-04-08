
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	CEdit shiftamount;
	CEdit Operand1;
	CEdit Operand2;
	afx_msg void OnBnClickedRadio2();
	CButton CheckShift;
	afx_msg void OnEnChangeEdit3();
	CComboBox ShiftType;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio1();
	int CheckAND;
	int CheckOR;
	int CheckXOR;
	CListBox list;
	CButton Compute;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLbnSelchangeList2();
	int Radiobutton;
};
