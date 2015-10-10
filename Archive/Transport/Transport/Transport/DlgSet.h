/**	@file DlgSet.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief �������ڣ�����IP
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note Ŀǰֻ����IP���������ÿ�������
 */



#pragma once


/**	@class CDlgSet [DlgSet.h, DlgSet.cpp]
 *	@brief �����࣬�����������á�
 *
 * Ŀǰֻ��������IP�����������Ժ��������
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
