/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/

#include "TitleInfo.h"

bool TitleInfo::bookMatch(char *bookname)
{
	int i,j;
	bool bo=false;
	for(i=0;i<51;i++)							//��ʼʱbo=false
	{
		if(title[i]==*bookname)
		{
			bo=true;							//���ֿ��ܶ�ʱ����bo=true
			for(j=1;*(bookname+j)!='\0';j++)
			{
				if((i+j)>50)						//��ֹtitleԽλ
				{
					bo=false;						//һ�����ֲ�����������Ϊfalse,���˳���ѭ��
					break;
				}
				if(title[i+j]!=*(bookname+j))
				{
					bo=false;						//һ�����ֲ�����������Ϊfalse,���˳���ѭ��
					break;
				}
			}
			if(bo==true)							//��ѭ��������bo��Ϊtrue,ȷ�����ϣ��˳���ѭ��
				break;
		}											//��δ������ѭ����bo��Ϊfalse
	}
	return bo;
}
		