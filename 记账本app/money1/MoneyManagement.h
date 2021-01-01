#pragma once


// MoneyManagement 对话框

class MoneyManagement : public CDialogEx
{
	DECLARE_DYNAMIC(MoneyManagement)

public:
	MoneyManagement(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MoneyManagement();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MONEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMainAdd();
	afx_msg void OnBnClickedButton2();
	// 账单列表
	CListCtrl m_mainList;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedBtnClean();
	afx_msg void OnBnClickedBtnCount();
	afx_msg void OnBnClickedBtnUnsubscribe();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();
protected:
	void showList();
public:
	afx_msg void OnBnClickedButton1();
};
