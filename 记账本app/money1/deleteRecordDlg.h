#pragma once


// deleteRecordDlg 对话框

class deleteRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(deleteRecordDlg)

public:
	deleteRecordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~deleteRecordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDeleteOk();
	CString del_id;
};
