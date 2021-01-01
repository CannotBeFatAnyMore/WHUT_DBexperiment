// MoneyManagement.cpp: 实现文件
//

#include "pch.h"
#include "money1.h"
#include "MoneyManagement.h"
#include "afxdialogex.h"
#include "addRecordDlg.h"
#include "changeRecord.h"
#include "deleteRecordDlg.h"
#include "global.h"
#include "DBconn.h"
#include "money1Dlg.h"



// MoneyManagement 对话框

IMPLEMENT_DYNAMIC(MoneyManagement, CDialogEx)

MoneyManagement::MoneyManagement(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MONEY, pParent)
{

}

MoneyManagement::~MoneyManagement()
{
}

void MoneyManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIN, m_mainList);
}


BEGIN_MESSAGE_MAP(MoneyManagement, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MAIN_ADD, &MoneyManagement::OnBnClickedBtnMainAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &MoneyManagement::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MoneyManagement::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BTN_CLEAN, &MoneyManagement::OnBnClickedBtnClean)
	ON_BN_CLICKED(IDC_BTN_COUNT, &MoneyManagement::OnBnClickedBtnCount)
	ON_BN_CLICKED(IDC_BTN_UNSUBSCRIBE, &MoneyManagement::OnBnClickedBtnUnsubscribe)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &MoneyManagement::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &MoneyManagement::OnBnClickedBtnExport)
	ON_BN_CLICKED(IDC_BUTTON1, &MoneyManagement::OnBnClickedButton1)
END_MESSAGE_MAP()


// MoneyManagement 消息处理程序


BOOL MoneyManagement::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		// TODO:  在此添加额外的初始化
	CRect rectL;
	m_mainList.GetWindowRect(&rectL);
	int widL = rectL.right - rectL.left;
	m_mainList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  // 整行选择、网格线
	m_mainList.SetTextBkColor(RGB(224, 238, 238));  //设置文本颜色
	m_mainList.InsertColumn(0, _T("账单名称"), LVCFMT_CENTER, 3 * widL / 12);
	m_mainList.InsertColumn(1, _T("账单类型"), LVCFMT_CENTER, widL / 12);
	m_mainList.InsertColumn(2, _T("物品类型"), LVCFMT_CENTER, 2 * widL / 12);
	m_mainList.InsertColumn(3, _T("消费金额"), LVCFMT_CENTER, 2 * widL / 12);
	m_mainList.InsertColumn(4, _T("账单ID"), LVCFMT_CENTER, widL / 12);
	m_mainList.InsertColumn(5, _T("创建时间"), LVCFMT_CENTER, 3 * widL / 12);
	this->showList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MoneyManagement::OnBnClickedBtnMainAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加账单
	this->EndDialog(0);
	addRecordDlg dlg;
	dlg.DoModal();
	//this->OnInitDialog();
//	this->ShowWindow(SW_HIDE);
//	this->ShowWindow(SW_SHOW);
}


void MoneyManagement::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改账单

	changeRecordDlg dlg;
	dlg.DoModal();
	this->EndDialog(0);
}


void MoneyManagement::OnBnClickedButton3()
{//删除账单
	// TODO: 在此添加控件通知处理程序代码
	//this->EndDialog(0);
	deleteRecordDlg dlg;
	dlg.DoModal();
	m_mainList.DeleteAllItems();
	this->showList();
}


void MoneyManagement::OnBnClickedBtnClean()
{
	//清空账单
	// TODO: 在此添加控件通知处理程序代码
	DBconn conn;
	int res = conn.delete_all_record(_USERID);
	if (res == -1) {
		MessageBox(TEXT("删除失败！"), TEXT("失败"), MB_ICONWARNING);
	}
	else MessageBox(TEXT("删除成功！"), TEXT("成功"), MB_OK);
	m_mainList.DeleteAllItems();
}


void MoneyManagement::OnBnClickedBtnCount()
{
	// TODO: 在此添加控件通知处理程序代码
	DBconn conn;
	double income = conn.income_sum(_USERID);
	CString res;
	res.Format("收入总额为：%.3f元", income);
	double spend = conn.spend_sum(_USERID);
	res.Format("支出总额为：%.3f元,\n收入总额为：%.3f元", income, spend);
	MessageBox(TEXT(res), TEXT("查询成功！"), MB_OK);
}


void MoneyManagement::OnBnClickedBtnUnsubscribe()
{
	// TODO: 在此添加控件通知处理程序代码
	DBconn conn;
	int res = conn.delete_user(_USERID);
	if (res == -1) {
		MessageBox(TEXT("注销失败！"), TEXT("失败"), MB_ICONWARNING);
	}
	else MessageBox(TEXT("注销成功！"), TEXT("成功"), MB_OK);
	this->EndDialog(0);
}



void MoneyManagement::OnBnClickedBtnImport()
{//恢复账单
		DBconn conn;
		int res = conn.recover_DB(_USERID);
		if (res == -1) {
			MessageBox(TEXT("导入失败！请询问管理员"), TEXT("失败"), MB_ICONWARNING);
		}
		else
		{
			MessageBox(TEXT("您的信息已经导入数据库！"), TEXT("成功"), MB_OK);
			this->showList();
		}


}


void MoneyManagement::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
	DBconn conn;
	int res = conn.back_upDB(_USERID);
	if (res == -1) {
		MessageBox(TEXT("备份失败！请询问管理员"), TEXT("失败"), MB_ICONWARNING);
	}
	else MessageBox(TEXT("您的信息已经备份成功！"), TEXT("成功"), MB_OK);

}


void MoneyManagement::showList()
{
	// TODO: 在此处添加实现代码.
	DBconn conn;
	RESULT res;
	res = conn.check_record(_USERID);
	m_mainList.DeleteAllItems();
	for (int i = 0; i < res.row; i++)
	{
		// 1. 先插入一行，i是行号，第二个参数是第0列的内容；可以不填为空
		//m_List.InsertItem(i, id[i]);
		m_mainList.InsertItem(i, _T(""));

		// 2.设置该行每一列的内容
		m_mainList.SetItemText(i, 0, _T(res.data[i][0]));
		char* type;
		if (!strcmp(res.data[i][1],"-1")) {
			type = "支出";
		}
		else type = "收入";
		m_mainList.SetItemText(i, 1, _T(type));
		m_mainList.SetItemText(i, 2, _T(res.data[i][2]));
		m_mainList.SetItemText(i, 3, _T(res.data[i][3]));
		m_mainList.SetItemText(i, 4, _T(res.data[i][4]));
		m_mainList.SetItemText(i, 5, _T(res.data[i][5]));
	}
}





void MoneyManagement::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->showList();
}
