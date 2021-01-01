#pragma once


// addRecordDlg 对话框

class addRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(addRecordDlg)

public:
	addRecordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addRecordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString item_name;
	CString money;
	// 下拉框，选择进账出账
	CComboBox m_recordType;
	// 下拉框，物品类别
	CComboBox m_objectType;
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn();
	afx_msg void OnBnClickedBtnAddBack();
};
