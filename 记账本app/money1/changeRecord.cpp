// changeRecord.cpp: 实现文件
//

#include "pch.h"
#include "money1.h"
#include "changeRecord.h"
#include "afxdialogex.h"
#include "DBconn.h"
#include "MoneyManagement.h"
#include "global.h"


// changeRecord 对话框

IMPLEMENT_DYNAMIC(changeRecordDlg, CDialogEx)

changeRecordDlg::changeRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CHANGE, pParent)
	, item_Name(_T(""))
	, money(_T(""))
	, item_ID(_T(""))
{

}

changeRecordDlg::~changeRecordDlg()
{
}

void changeRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COB_RECORDTYPE1, m_recordType);
	DDX_Control(pDX, IDC_COB_OBJECTTYPE1, m_objectType);
	DDX_Text(pDX, IDC_EDIT1, item_ID);
	DDX_Text(pDX, IDC_EDIT2, item_Name);
	DDX_Text(pDX, IDC_EDIT6, money);

}


BEGIN_MESSAGE_MAP(changeRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CHANGE_OK, &changeRecordDlg::OnBnClickedBtnChangeOk)
	ON_BN_CLICKED(IDC_BTN_CHANGE_BACK, &changeRecordDlg::OnBnClickedBtnChangeBack)
END_MESSAGE_MAP()


// changeRecord 消息处理程序


BOOL changeRecordDlg::OnInitDialog()
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




void changeRecordDlg::OnBnClickedBtnChangeOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改按钮 此处添加接口
	UpdateData(TRUE);
	DBconn conn;
	char item_name[20];
	char amount[20];
	char id[5];
	strcpy_s(id, (LPCTSTR)item_ID);
	strcpy_s(item_name, (LPCTSTR)item_Name);
	strcpy_s(amount,(LPCTSTR)money);
	CString Type;
	int type;
	//进出账 combobox选中内容
	int index1 = m_recordType.GetCurSel();
	m_recordType.GetLBText(index1, Type);
	if (Type == "进账") {
		type = 1;
	}
	else type = -1;
	char kind[10];
	//消费类型
	CString Kind;
	int index2 = m_objectType.GetCurSel();
	m_objectType.GetLBText(index2, Kind);
	strcpy_s(kind, (LPCTSTR)Kind);
	//参数列表： kind账单类型 type 进出账 item_ID 
	int res= conn.modify_record(_USERID, type, item_name, kind, amount, id);
	if (res==0)
	{
		MessageBox(TEXT("修改账单成功"), TEXT("成功"), MB_OK);
	}
	else
	{
		MessageBox(TEXT("修改账单失败"), TEXT("失败"), MB_ICONWARNING);
	}
}


void changeRecordDlg::OnBnClickedBtnChangeBack()
{
	// TODO: 在此添加控件通知处理程序代码
	//返回按钮
	EndDialog(0);  //关闭界面
	//MoneyManagement dlg;
	//dlg.DoModal();
}
