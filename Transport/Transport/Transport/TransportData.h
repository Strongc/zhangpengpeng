/**	@file TransportData.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief ��װ��CMarkup�������������紫������
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note �����װ��CMarkup��
 *	@note 1�����ܾ���������Ϣ������XML���������ַ��������ڷ���ǰ�İ�װ
 *	@note 2������XML��ʽ���ַ����������󷵻ؾ���������Ϣ�����ڽ��ܺ�ķ���
 */

#pragma once
#include "StdAfx.h"
#include "Markup.h"

/**	@class CTransportData [TransportData.h, TransportData.cpp]
 *	@brief ��װ��CMarkup�������������紫�����ݡ�
 *
 * ��ľ�����;��������ļ�����
 */
class CTransportData
{
private:
	CMarkup m_Xml;			//net data which is transported by xml format
	CString m_strXml;		//xml stream
	CString m_strCmd;		//string format of <command>
	char m_strData[DATASIZEPERTRANS];	//array format of <data>
	int m_DataSize;			//size of data

public:
	CTransportData(void);
	~CTransportData(void);

	BOOL SetXmlData(CString strCmd, char *pData, int iDataSize);	//set all data of xml
	BOOL SetXmlData(CString strCmd, CString strData, int iDataSize);
	BOOL SetXmlString(CString strXml);				//set xml stream to analyze
	BOOL SetXmlString(char *strXml);
	CString GetXmlString();							//get xml stream according 
	char *GetXmlCharArray();						//same as GetXmlString but return char *
	CString GetCmd();								//get <command>
	char *GetData();								//get <data>
	int GetDataSize();								//get size of <data>
	int GetXmlSize();								//get size of xml stream
};


/* xml format used to transport files
<file>
 	<command>COMMAND</command>
	<data>DATA</data>
</file>

description:
COMMAND: 
	filename: DATA is file's name and server should create a file and be ready to write
	filedata: DATA is file's data and continue write those to the opened file
	filevoer: don't mind DATA, close the opened file and finish the transprotion

*/
