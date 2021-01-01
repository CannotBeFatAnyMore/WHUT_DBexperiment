#pragma once


// RegisterDlg 对话框

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRegBack();
	afx_msg void OnBnClickedBtnRegRegister();
	// 账户文本框
	CString m_account;
	// 注册账户密码1
	CString m_password1;
	// 确定账户密码
	CString m_password2;
	// 密码控件，用于隐藏密码
	CEdit m_Password1;
	// 密码控件，用于隐藏密码
	CEdit m_Password2;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditRegAccount();
};
