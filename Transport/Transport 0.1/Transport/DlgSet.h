#pragma once


// CDlgSet dialog

class CDlgSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgSet)

public:
	CDlgSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSet();

// Dialog Data
	enum { IDD = IDD_DLG_SET };

	DWORD m_dwIPOpposite;		//opposite ip address

	afx_msg void OnBnClickedBtnconfirm();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
