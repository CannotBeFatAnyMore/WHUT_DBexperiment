
// money1Dlg.h: 头文件
//

#pragma once


// Cmoney1Dlg 对话框
class Cmoney1Dlg : public CDialogEx
{
// 构造
public:
	Cmoney1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONEY1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont staticFont;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//  欢迎语
	CStatic m_static_welcome;
	// 账户Account
	CStatic m_static_account;
	//用于改变背景图片
	int m_oldWidth;   //窗口的宽
	int m_oldHeight;  //窗口的高

	//相应函数
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 用于隐藏显示密码
	CEdit m_Password;
	// 账号值
	CString m_account;
	// 账号密码
	CString m_password;
};
