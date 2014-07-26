/**	@file DlgSet.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CDlgSet���ʵ���ļ�
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note ���г�ʼ���͵��ȷ��������ݷ���
 */

#include "stdafx.h"
#include "Transport.h"
#include "DlgSet.h"


// CDlgSet dialog

IMPLEMENT_DYNAMIC(CDlgSet, CDialog)

CDlgSet::CDlgSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSet::IDD, pParent)
	, m_dwIPOpposite(0)
{

}

CDlgSet::~CDlgSet()
{
}

void CDlgSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwIPOpposite);
}


BEGIN_MESSAGE_MAP(CDlgSet, CDialog)
	ON_BN_CLICKED(IDC_BTNCONFIRM, &CDlgSet::OnBnClickedBtnconfirm)
END_MESSAGE_MAP()


// CDlgSet message handlers

/**	@fn	void CDlgSet::OnBnClickedBtnconfirm()
 *	@brief	����ȷ����ť���������ݸ��²�����
 */
void CDlgSet::OnBnClickedBtnconfirm()
{
	UpdateData();
	OnOK();
}

/**	@fn	BOOL CDlgSet::OnInitDialog()
 *	@brief	��ʼ�����ڣ�����Ĭ��ֵ
 */
BOOL CDlgSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_dwIPOpposite = 2886160900;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
