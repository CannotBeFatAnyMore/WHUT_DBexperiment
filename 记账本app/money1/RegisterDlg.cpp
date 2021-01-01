// RegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "money1.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "DBconn.h"
#include <string>
using namespace std;



// RegisterDlg 对话框

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_account(_T(""))
	, m_password1(_T(""))
	, m_password2(_T(""))
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REG_ACCOUNT, m_account);
	DDX_Text(pDX, IDC_EDIT_REG_PASSWORD1, m_password1);
	DDX_Text(pDX, IDC_EDIT_REG_PASSWORD2, m_password2);
	DDX_Control(pDX, IDC_EDIT_REG_PASSWORD1, m_Password1);
	DDX_Control(pDX, IDC_EDIT_REG_PASSWORD2, m_Password2);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_REG_BACK, &RegisterDlg::OnBnClickedBtnRegBack)
	ON_BN_CLICKED(IDC_BTN_REG_REGISTER, &RegisterDlg::OnBnClickedBtnRegRegister)
	ON_EN_CHANGE(IDC_EDIT_REG_ACCOUNT, &RegisterDlg::OnEnChangeEditRegAccount)
END_MESSAGE_MAP()


// RegisterDlg 消息处理程序


void RegisterDlg::OnBnClickedBtnRegBack()
{
	// TODO: 在此添加控件通知处理程序代码
	//返回登录界面按钮
	EndDialog(0);
}


void RegisterDlg::OnBnClickedBtnRegRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	//注册
	//获取控件账号密码值
	UpdateData(TRUE);   //可获取文本值，
	if (m_password1 != m_password2) {
		MessageBox(TEXT("请检查密码是否输入一致！"), TEXT("重新输入"), MB_ICONSTOP);
	}
	DBconn conn;
	char usrname[20];
	char pwd[20];
	strcpy_s(usrname,(LPCTSTR)m_account);
	strcpy_s(pwd, (LPCTSTR)m_password1);
	int res = conn.add_users(usrname, pwd);

	if (res==0)
	{
		//提示注册成功！
		MessageBox(TEXT("账号注册成功"), TEXT("成功"), MB_OK);
		EndDialog(0);  //关闭注册界面

	}
	else 
	{
		//提示错误信息
		MessageBox(TEXT("已有相同用户名！"), TEXT("失败"), MB_ICONSTOP);
	}



}


BOOL RegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Password1.SetPasswordChar('*');
	m_Password2.SetPasswordChar('*');


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void RegisterDlg::OnEnChangeEditRegAccount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
