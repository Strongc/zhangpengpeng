/**	@file AdditionFun.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief ͨ�õ�ȫ�ֺ�����
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note ���ļ�ʵ��������ȫ�ֺ���
		int Encode(char *data, char *code, int len);
		int Decode(char *data, char *code);
		bool MyMemMove(char *dest, char *src, int count);
 *	@note ��Щ��������ȫ��ʹ�ã�������������������
 *
 *	@warning ����stdafx.h�н��к�������
 */

#include "stdafx.h"


/**	@fn	int Encode(char *data, char *code, int len)
 *	@brief	���ڽ����������ݱ���Ϊ�������ڴ�����ı����ο���BASE64������λ����11������00
 *	@param data [in]��Ҫ���б����ָ��.
 *	@param code [out]���ڷ��صı����ı���ָ��.
 *	@param len [in]��Ҫ���б�������ݳ���.
 *	@return	�����ı��ĳ���
 */
int Encode(char *data, char *code, int len)
{
	char d3, d2, d1;		//three bytes of data
	char c4, c3, c2, c1;	//four bytes of code 
	int iComplement = 0;		//count of complement

	int i;	//index for data;
	int j;	//index for code;
	for (i = 0, j = 0; i < len; i += 3)
	{
		d1 = *(data + i);
		if ((i + 1) < len)
		{
			d2 = *(data + i + 1);
		}
		else 
		{
			iComplement++;
			d2 = '\0';
		}
		if ((i + 2) < len)
		{
			d3 = *(data + i + 2);
		}
		else
		{
			iComplement++;
			d3 = '\0';
		}

		//encode per there data bytes
		c1 = (d1 & 0x3F) | 0xC0;
		c2 = ((d1 >> 6) & 0x03) | (d2 << 2) | 0xC0;
		c3 = ((d2 >> 4) & 0x0F) | (d3 << 4) | 0xC0;
		c4 = ((d3 >> 2) & 0x3F) | 0xC0;

		*(code + j) = c1;
		j++;
		*(code + j) = c2;
		j++;
		*(code + j) = c3;
		j++;
		*(code + j) = c4;
		j++;
	}
	
	*(code + j) = (char)iComplement | 0x80;
	return j;
}


/**	@fn	int Decode(char *data, char *code)
 *	@brief	���ڽ��������ı�����Ϊ���������ݣ��������Encode�������
 *	@param data [out]����󷵻ص�����ָ��.
 *	@param code [in]��Ҫ���н�����ı���ָ��.
 *	@return	���������ݳ���
 */
int Decode(char *data, char *code)
{
	char d3, d2, d1;				//three bytes of data
	char c4, c3, c2, c1;			//four bytes of code 

	int i = 0;	//index for data;
	int j = 0;	//index for code;
	while((*(code + j) & 0xC0) == 0xC0)
	{
		c1 = *(code + j);
		j++;
		c2 = *(code + j);
		j++;
		c3 = *(code + j);
		j++;
		c4 = *(code + j);
		j++;

		//decode per four code byts
		d1 = (c1 & 0x3F) | (c2 << 6);
		d2 = ((c2 >> 2) & 0x0F) | (c3 << 4);
		d3 = ((c3 >> 4) & 0x03) | (c4 << 2);

		*(data + i) = d1;
		i++;
		*(data + i) = d2;
		i++;
		*(data + i) = d3;
		i++;
	}

	int iComplement = *(code + j) & 0x3F;	//count of complement
	return i - iComplement;
}

/**	@fn	bool MyMemMove(char *dest, char *src, int count)
 *	@brief	�Լ������һ���ڴ����ƶ����ƶ������ԭ�ڴ��
 *	@param dest Ŀ�ĵ�ַ��ʼָ��.
 *	@param src Դ��ַ��ͷָ��.
 *	@param count ��Ҫ�����ƶ����ֽڳ���.
 *	@return	�ɹ����
 */
bool MyMemMove(char *dest, char *src, int count)
{
	for (int i = 0; i < count; i++)
	{
		*(dest + i) = *(src + i);
		*(src + i) = '\0';
	}

	return true;
}

