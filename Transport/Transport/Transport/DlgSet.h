/**	@file DlgSet.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 弹出窗口，配置IP
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 目前只设置IP，其他设置可以增加
 */



#pragma once


/**	@class CDlgSet [DlgSet.h, DlgSet.cpp]
 *	@brief 窗口类，用于网络设置。
 *
 * 目前只用来设置IP，其他设置以后可以增加
 */

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
