/**	@file TransportData.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 封装了CMarkup，用来处理网络传输数据
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 该类封装了CMarkup类
 *	@note 1，接受具体数据信息，生成XML，返回其字符串，用于发送前的包装
 *	@note 2，接受XML格式的字符串，解析后返回具体数据信息，用于接受后的分析
 */

#pragma once
#include "StdAfx.h"
#include "Markup.h"

/**	@class CTransportData [TransportData.h, TransportData.cpp]
 *	@brief 封装了CMarkup，用来处理网络传输数据。
 *
 * 类的具体用途看上面的文件描述
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
