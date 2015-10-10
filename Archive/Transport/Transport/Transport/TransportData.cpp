/**	@file TransportData.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CTransportData���ʵ���ļ�
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note ʵ����CTransportData��ĸ����
 */

#include "StdAfx.h"
#include "TransportData.h"

CTransportData::CTransportData(void)
{
}

CTransportData::~CTransportData(void)
{
}


/**	@fn	BOOL CTransportData::SetXmlString(CString strXml)
 *	@brief	���������XML��ʽ�ַ������������ݷ����������ڲ�����
 *	@param strXml �����XML��ʽ�ַ���, ΪCString��.
 *	@return	�����Ƿ�ɹ�
 */
BOOL CTransportData::SetXmlString(CString strXml)
{
	m_Xml.SetDoc(strXml);	//update XML

	//update other member variables
	m_strXml = strXml;
	m_Xml.ResetMainPos();
	m_Xml.FindElem("file");
	m_Xml.IntoElem();
	m_Xml.FindElem("command");
	m_strCmd = m_Xml.GetData();
	m_Xml.FindElem("data");
	CString strCode = m_Xml.GetData();

	//decoding
	memset(m_strData, 0, DATASIZEPERTRANS);
	m_DataSize = Decode(m_strData, strCode.GetBuffer(strCode.GetLength()));
	strCode.ReleaseBuffer();

	return TRUE;
}

/**	@fn	BOOL CTransportData::SetXmlString(char *strXml)
 *	@brief	�Ժ���BOOL CTransportData::SetXmlString(CString strXml)�����أ��ṩ��һ�ַ��ʷ�ʽ
 *	@param strXml �����XML��ʽ�ַ���, Ϊchar���ַ���.
 *	@return	�����ɹ����
 */
BOOL CTransportData::SetXmlString(char *strXml)
{
	CString csXml;
	csXml.Format("%s", strXml);
	return SetXmlString(csXml);
}
	
/**	@fn	BOOL CTransportData::SetXmlData(CString strCmd, char *pData, int iDataSize)
 *	@brief	ͨ��������������XML��ʽ�ַ���
 *	@param strCmd ������ͷ�ļ��е�xml��ʽ����.
 *	@param pData ���ݣ����ͷ�ļ��е�xml��ʽ������Ϊchar���ַ���.
 *	@param iDataSize ����ʵ�ʳ��ȣ���������β��'\0'.
 *	@return	����ɹ����
 */
BOOL CTransportData::SetXmlData(CString strCmd, char *pData, int iDataSize)	//iDataSize is the real size of data not include the last '\0'
{
	//remove all
	m_Xml.ResetPos();
	m_Xml.FindElem();
	m_Xml.RemoveElem();

	//encoding
	char code[DATASIZEPERTRANS / 2 * 3 + 10];
	memset(code, 0, DATASIZEPERTRANS / 2 * 3 + 10);
	Encode(pData, code, iDataSize);

	// add new data
	m_Xml.ResetPos();
	m_Xml.AddElem("file");
	m_Xml.IntoElem();
	m_Xml.AddElem("command", strCmd.GetBuffer(strCmd.GetLength()));
	strCmd.ReleaseBuffer();
	m_Xml.AddElem("data", code);
	m_Xml.OutOfElem();

	//update other member variables
	m_strXml = m_Xml.GetDoc();
	m_strCmd = strCmd;
	m_DataSize = iDataSize;
	if (m_strData != pData)
		memcpy(m_strData, pData, iDataSize);

	return TRUE;
}

/**	@fn	BOOL CTransportData::SetXmlData(CString strCmd, CString strData, int iDataSize)
 *	@brief	�Ժ���BOOL CTransportData::SetXmlData(CString strCmd, char *pData, int iDataSize)�����أ��ṩ��һ�ַ��ʷ�ʽ
 *	@param strCmd ������ͷ�ļ��е�xml��ʽ����.
 *	@param pData ���ݣ����ͷ�ļ��е�xml��ʽ����ΪCString��.
 *	@param iDataSize ����ʵ�ʳ��ȣ���������β��'\0'.
 *	@return	����ɹ����
 */
BOOL CTransportData::SetXmlData(CString strCmd, CString strData, int iDataSize)
{
	memcpy(m_strData, strData.GetBuffer(strData.GetLength()), strData.GetLength() + 1);
	strData.ReleaseBuffer();
	return SetXmlData(strCmd, m_strData, iDataSize);
}

/**	@fn	int CTransportData::GetDataSize()
 *	@brief	������ݳ���
 *	@return	���ݳ���
 */
int CTransportData::GetDataSize()
{
	return m_DataSize;
}

/**	@fn	int CTransportData::GetXmlSize()
 *	@brief	���XML��ʽ�ַ�������
 *	@return	XML��ʽ�ַ�������
 */
int CTransportData::GetXmlSize()
{
	return m_strXml.GetLength();
}

/**	@fn	CString CTransportData::GetCmd()
 *	@brief	�������
 *	@return	����
 */
CString CTransportData::GetCmd()
{
	return m_strCmd;
}

/**	@fn	char *CTransportData::GetData()
 *	@brief	�������
 *	@return	����
 */
char *CTransportData::GetData()
{
	return m_strData;
}

/**	@fn	CString CTransportData::GetXmlString()
 *	@brief	���XML��ʽ�ַ���
 *	@return	XML��ʽ�ַ�����CString��
 */
CString CTransportData::GetXmlString()
{
	return m_strXml;
}

/**	@fn	char *CTransportData::GetXmlCharArray()
 *	@brief	���XML��ʽ�ַ���
 *	@return	XML��ʽ�ַ�����char���ַ���
 */
char *CTransportData::GetXmlCharArray()
{
	return  m_strXml.GetBuffer(m_strXml.GetLength());
}
