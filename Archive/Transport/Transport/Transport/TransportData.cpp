/**	@file TransportData.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CTransportData类的实现文件
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 实现了CTransportData类的各项功能
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
 *	@brief	根据输入的XML格式字符串，进行数据分析，更新内部变量
 *	@param strXml 输入的XML格式字符串, 为CString型.
 *	@return	解析是否成功
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
 *	@brief	对函数BOOL CTransportData::SetXmlString(CString strXml)的重载，提供另一种访问方式
 *	@param strXml 输入的XML格式字符串, 为char型字符串.
 *	@return	解析成功与否
 */
BOOL CTransportData::SetXmlString(char *strXml)
{
	CString csXml;
	csXml.Format("%s", strXml);
	return SetXmlString(csXml);
}
	
/**	@fn	BOOL CTransportData::SetXmlData(CString strCmd, char *pData, int iDataSize)
 *	@brief	通过具体数据生成XML格式字符串
 *	@param strCmd 命令，详见头文件中的xml格式描述.
 *	@param pData 数据，详见头文件中的xml格式描述，为char型字符串.
 *	@param iDataSize 数据实际长度，不包括结尾的'\0'.
 *	@return	编码成功与否
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
 *	@brief	对函数BOOL CTransportData::SetXmlData(CString strCmd, char *pData, int iDataSize)的重载，提供另一种访问方式
 *	@param strCmd 命令，详见头文件中的xml格式描述.
 *	@param pData 数据，详见头文件中的xml格式描述为CString型.
 *	@param iDataSize 数据实际长度，不包括结尾的'\0'.
 *	@return	编码成功与否
 */
BOOL CTransportData::SetXmlData(CString strCmd, CString strData, int iDataSize)
{
	memcpy(m_strData, strData.GetBuffer(strData.GetLength()), strData.GetLength() + 1);
	strData.ReleaseBuffer();
	return SetXmlData(strCmd, m_strData, iDataSize);
}

/**	@fn	int CTransportData::GetDataSize()
 *	@brief	获得数据长度
 *	@return	数据长度
 */
int CTransportData::GetDataSize()
{
	return m_DataSize;
}

/**	@fn	int CTransportData::GetXmlSize()
 *	@brief	获得XML格式字符串长度
 *	@return	XML格式字符串长度
 */
int CTransportData::GetXmlSize()
{
	return m_strXml.GetLength();
}

/**	@fn	CString CTransportData::GetCmd()
 *	@brief	获得命令
 *	@return	命令
 */
CString CTransportData::GetCmd()
{
	return m_strCmd;
}

/**	@fn	char *CTransportData::GetData()
 *	@brief	获得数据
 *	@return	数据
 */
char *CTransportData::GetData()
{
	return m_strData;
}

/**	@fn	CString CTransportData::GetXmlString()
 *	@brief	获得XML格式字符串
 *	@return	XML格式字符串，CString型
 */
CString CTransportData::GetXmlString()
{
	return m_strXml;
}

/**	@fn	char *CTransportData::GetXmlCharArray()
 *	@brief	获得XML格式字符串
 *	@return	XML格式字符串，char型字符串
 */
char *CTransportData::GetXmlCharArray()
{
	return  m_strXml.GetBuffer(m_strXml.GetLength());
}
