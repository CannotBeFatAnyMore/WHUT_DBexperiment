#pragma once


// changeRecord 对话框

class changeRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(changeRecordDlg)

public:
	changeRecordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~changeRecordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// //账单类型
	CComboBox m_recordType;
	// 物品类型
	CComboBox m_objectType;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChangeOk();
	afx_msg void OnBnClickedBtnChangeBack();
	CString item_ID;
	CString item_Name;
	CString money;
};
