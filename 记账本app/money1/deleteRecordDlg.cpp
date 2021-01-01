// deleteRecordDlg.cpp: 实现文件
//

#include "pch.h"
#include "money1.h"
#include "deleteRecordDlg.h"
#include "afxdialogex.h"
#include "DBconn.h"
#include "MoneyManagement.h"


// deleteRecordDlg 对话框

IMPLEMENT_DYNAMIC(deleteRecordDlg, CDialogEx)

deleteRecordDlg::deleteRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_DELETE, pParent)
	, del_id(_T(""))
{

}

deleteRecordDlg::~deleteRecordDlg()
{
}

void deleteRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, del_id);
}


BEGIN_MESSAGE_MAP(deleteRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DELETE_OK, &deleteRecordDlg::OnBnClickedBtnDeleteOk)
END_MESSAGE_MAP()


// deleteRecordDlg 消息处理程序


void deleteRecordDlg::OnBnClickedBtnDeleteOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);   //可获取文本值，
	char id[5];
	strcpy_s(id, (LPCTSTR)del_id);
	DBconn conn;
	int res=conn.delete_record(id);
	if (res == -1) {
		MessageBox(TEXT("删除失败！！请检查输入的ID号码是否存在"), TEXT("失败"), MB_ICONSTOP);
	}
	else {
		MessageBox(TEXT("删除成功！"), TEXT("成功"), MB_OK);
	}
	this->EndDialog(0);
	//MoneyManagement dlg;
	//dlg.DoModal();

}
