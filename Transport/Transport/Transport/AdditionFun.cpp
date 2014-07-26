/**	@file AdditionFun.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 通用的全局函数。
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 该文件实现了如下全局函数
		int Encode(char *data, char *code, int len);
		int Decode(char *data, char *code);
		bool MyMemMove(char *dest, char *src, int count);
 *	@note 这些函数可以全局使用，并可以用于其他工程
 *
 *	@warning 请在stdafx.h中进行函数声明
 */

#include "stdafx.h"


/**	@fn	int Encode(char *data, char *code, int len)
 *	@brief	用于将二进制数据编码为可以用于传输的文本，参考了BASE64，但高位采用11代替了00
 *	@param data [in]需要进行编码的指针.
 *	@param code [out]用于返回的编码文本的指针.
 *	@param len [in]需要进行编码的数据长度.
 *	@return	编码文本的长度
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
 *	@brief	用于将编码后的文本解码为二进制数据，与上面的Encode函数相对
 *	@param data [out]解码后返回的数据指针.
 *	@param code [in]需要进行解码的文本的指针.
 *	@return	解码后的数据长度
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
 *	@brief	自己定义的一种内存块的移动，移动后清空原内存块
 *	@param dest 目的地址开始指针.
 *	@param src 源地址开头指针.
 *	@param count 需要进行移动的字节长度.
 *	@return	成功与否
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

