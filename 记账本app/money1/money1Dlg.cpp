
// money1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "money1.h"
#include "money1Dlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "MoneyManagement.h"
#include "RegisterDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DBconn.h"
#include "global.h"





// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmoney1Dlg 对话框



Cmoney1Dlg::Cmoney1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MONEY1_DIALOG, pParent)
	, m_account(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmoney1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Welcome, m_static_welcome);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_static_account);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_account);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
}

BEGIN_MESSAGE_MAP(Cmoney1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &Cmoney1Dlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_REGISTER, &Cmoney1Dlg::OnBnClickedBtnRegister)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Cmoney1Dlg 消息处理程序

BOOL Cmoney1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//背景随窗口大小改变
	CRect rect;
	GetClientRect(&rect);
	m_oldWidth = rect.Width();    //将初始的宽和高保存起来，当窗口大小改变的时候用得上
	m_oldHeight = -rect.Height();


	// TODO: 在此添加额外的初始化代码
	CFont* font;
	font = m_static_welcome.GetFont();//获取CFont对象
	LOGFONT lf_welcome;
	font->GetLogFont(&lf_welcome);                //获取LOGFONT结构体
	lf_welcome.lfHeight = -60;                    //修改字体大小
	lf_welcome.lfItalic = TRUE;                   //倾斜
	lf_welcome.lfWeight = 900;                    //修改字体的粗细
	lstrcpy(lf_welcome.lfFaceName, _T("Arial"));  //修改字体名
	//staticFont.CreateFontIndirectW(&lf_welcome);  //创建一个新的字体
	m_static_welcome.SetFont(&staticFont);

	m_Password.SetPasswordChar('*');
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmoney1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmoney1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		//加载背景图片
		CPaintDC   dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_LOGIN_BAC);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cmoney1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void Cmoney1Dlg::OnBnClickedBtnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//登录
	DBconn conn;
	char usrname[10];
	char pwd[20];
	strcpy_s(usrname,10, (LPCTSTR)m_account);
	strcpy_s(pwd,20, (LPCTSTR)m_password);
	int res = LOGIN(usrname, pwd);
	//UID = res;
	if (res!=-1)
	{
		this->ShowWindow(SW_HIDE);   //隐藏登录窗口
		//进入主界面  进入主界面之前要获得userid
		MoneyManagement dlg;
		dlg.DoModal();
	}
	else
	{
		//提示错误
		MessageBox(TEXT("账号密码错误"), TEXT("警告"), MB_ICONQUESTION);
	}
}


void Cmoney1Dlg::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	//注册
	this->ShowWindow(SW_HIDE);   //隐藏登录窗口
	//进入注册界面
	RegisterDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);   //显示登录窗口
}

void Cmoney1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码


	//当窗口大小改变的时候，使客户区无效，刷新背景图片
	Invalidate(FALSE);

}
