
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int maxSize = 0;//For Scroll

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, CheckAND(0)
	, CheckOR(0)
	, CheckXOR(0)
	, Radiobutton(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, shiftamount);
	DDX_Control(pDX, IDC_EDIT2, Operand1);
	DDX_Control(pDX, IDC_EDIT3, Operand2);
	DDX_Control(pDX, IDC_CHECK1, CheckShift);
	DDX_Control(pDX, IDC_COMBO1, ShiftType);
	DDX_Control(pDX, IDC_LIST2, list);
	DDX_Control(pDX, IDC_BUTTON1, Compute);
	DDX_Radio(pDX, IDC_RADIO1, Radiobutton);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication1Dlg::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication1Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCApplication1Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFCApplication1Dlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ShiftType.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	CString text;

	int selected;
	if(CheckShift.GetCheck()){ // If Shift button is checked enable others
		ShiftType.EnableWindow(TRUE);
		shiftamount.EnableWindow(TRUE);
	}
	else{ // Else disable others
		ShiftType.EnableWindow(FALSE);
		shiftamount.EnableWindow(FALSE);
	}
}

void CMFCApplication1Dlg::OnEnChangeEdit3(){}

void CMFCApplication1Dlg::OnEnChangeEdit2(){}

void CMFCApplication1Dlg::OnBnClickedRadio1(){}

void CMFCApplication1Dlg::OnBnClickedRadio2(){}

void CMFCApplication1Dlg::OnBnClickedRadio3(){}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CString result,operand1,operand2,text,text2,shift;
	CDC *pDC = GetDC();CFont *pOldFont = pDC->SelectObject(GetFont());CSize cz;//For Scroll
	// get operand 1 and 2
	Operand1.GetWindowTextW(operand1);
	Operand2.GetWindowTextW(operand2);
	unsigned int i1 = _tcstoul(operand1,nullptr,10);
	unsigned int i2 = _tcstoul(operand2,nullptr,10);
	int selected;
	//Check both operand 1 and 2 is given
	if(operand1.GetLength() == 0 || operand2.GetLength() == 0){
		result = "At least 1 operand was not entered";
		list.AddString(result);
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize)
			maxSize = cz.cx;
		list.SetHorizontalExtent(maxSize);
		return;
	}
	// If check button is checked
	if(CheckShift.GetCheck()){
		ShiftType.EnableWindow(TRUE);
		shiftamount.EnableWindow(TRUE);
		//Get Shift type (left,right)
		selected = ShiftType.GetCurSel();
		ShiftType.GetLBText(selected,text2);
		shiftamount.GetWindowTextW(shift);
		if ( shift.GetLength() == 0){// If shift amount is not given
			result = "Specify by how many bits you want to shift";
			list.AddString(result);
			cz = pDC->GetTextExtent(result);//For Scroll
			if(cz.cx > maxSize)
				maxSize = cz.cx;
			list.SetHorizontalExtent(maxSize);
			return;
		}
		unsigned int i3 = _ttoi(shift);
		// make necessary shift operation
		if (text2 == "Left"){
			i1 = i1 << i3; i2 = i2 << i3; 
		}
		else if (text2 == "Right"){
			i1 = i1 >> i3; i2 = i2 >> i3;
		}
	}
	// Since they may be shifted convert them back to Cstring
	operand1.Format(_T("%u"), i1);
	operand2.Format(_T("%u"), i2);

	result = result + operand1;
	UpdateData(TRUE);
	if(Radiobutton == 0){// If operation is and
		text.Format(_T("%u"), i1&i2);
		result = result + _T(" AND ") + operand2 + _T(" = ") + text;
	}
	else if(Radiobutton == 1){// If operation is or
		text.Format(_T("%u"), i1|i2);
		result = result + _T(" OR ")  + operand2 + _T(" = ") + text;
	}
	else if(Radiobutton == 2){// If operation is xor
		text.Format(_T("%u"), i1^i2);
		result = result + _T(" XOR ") + operand2 + _T(" = ") + text;
	}
	list.AddString(result);
	cz = pDC->GetTextExtent(result);//For Scroll
	if(cz.cx > maxSize)
		maxSize = cz.cx;
	list.SetHorizontalExtent(maxSize);
}

void CMFCApplication1Dlg::OnEnChangeEdit1(){}

void CMFCApplication1Dlg::OnLbnSelchangeList2(){}
