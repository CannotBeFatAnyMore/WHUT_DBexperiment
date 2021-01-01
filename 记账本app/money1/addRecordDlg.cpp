// addRecordDlg.cpp: 实现文件
//

#include "pch.h"
#include "money1.h"
#include "addRecordDlg.h"
#include "afxdialogex.h"
#include "DBconn.h"
#include "global.h"
#include "MoneyManagement.h"


// addRecordDlg 对话框

IMPLEMENT_DYNAMIC(addRecordDlg, CDialogEx)

addRecordDlg::addRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_ADD, pParent)
	, item_name(_T(""))
	, money(_T(""))
{

}

addRecordDlg::~addRecordDlg()
{
}

void addRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COB_RECORDTYPE, m_recordType);
	DDX_Control(pDX, IDC_COB_OBJECTTYPE, m_objectType);
	DDX_Text(pDX, IDC_EDIT1, item_name);
	DDX_Text(pDX, IDC_EDIT4, money);
}





// addRecordDlg 消息处理程序


BOOL addRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_recordType.AddString(_T("进账"));
	m_recordType.AddString(_T("出账"));
	m_objectType.AddString(_T("通讯物流"));
	m_objectType.AddString(_T("图书教育"));
	m_objectType.AddString(_T("餐饮美食"));
	m_objectType.AddString(_T("生活日用"));
	m_objectType.AddString(_T("交通出行"));
	m_objectType.AddString(_T("运动户外"));
	m_objectType.AddString(_T("休闲生活"));
	m_objectType.AddString(_T("游戏氪金"));
	m_objectType.AddString(_T("其他"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}






BEGIN_MESSAGE_MAP(addRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN__ADD_OK, &addRecordDlg::OnBnClickedBtn)
	ON_BN_CLICKED(IDC_BTN_ADD_BACK, &addRecordDlg::OnBnClickedBtnAddBack)
END_MESSAGE_MAP()


void addRecordDlg::OnBnClickedBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加按钮 此处添加接口
	UpdateData(TRUE);
	char item[20];
	char amount[20];
	strcpy_s(item, (LPCTSTR)item_name);
	strcpy_s(amount, (LPCTSTR)money);
	// CString strCom;
	// GetDlgItemText(IDC_COMBO2,strCom);
	//m_cbExample.GetLBText( nIndex, strCBText);
	//	strcpy_s(usrname,(LPCTSTR)m_account);
	CString Type;
	int type;
	//进出账 combobox选中内容
	int index1=m_recordType.GetCurSel();
	m_recordType.GetLBText(index1, Type);
	if (Type == "进账") {
		type = 1;
	}
	else type = -1;
	char kind[10];
	//消费类型
	CString Kind;
	int index2 = m_objectType.GetCurSel();
	m_objectType.GetLBText(index2,Kind);
	strcpy_s(kind, (LPCTSTR)Kind);
	DBconn conn;

	int res=conn.add_record(_USERID, type, item, kind, amount);

	if (res==0)
	{
		MessageBox(TEXT("添加账单成功"), TEXT("成功"), MB_OK);
	}
	else
	{
		MessageBox(TEXT("添加账单失败"), TEXT("失败"), MB_ICONWARNING);
	}
}


void addRecordDlg::OnBnClickedBtnAddBack()
{
	// TODO: 在此添加控件通知处理程序代码
	//返回按钮
	EndDialog(0);  //关闭界面
	MoneyManagement dlg;
	dlg.DoModal();
}



