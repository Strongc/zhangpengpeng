/**	@file DlgSet.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CDlgSet类的实现文件
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 进行初始化和点击确定后的数据返回
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
 *	@brief	按下确定按钮，进行数据更新并返回
 */
void CDlgSet::OnBnClickedBtnconfirm()
{
	UpdateData();
	OnOK();
}

/**	@fn	BOOL CDlgSet::OnInitDialog()
 *	@brief	初始化窗口，设置默认值
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
