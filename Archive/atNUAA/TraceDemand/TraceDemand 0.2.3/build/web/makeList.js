/********************************************************
	此js文件主要定义了：
	用于交互的数据；
	生成目录函数 beList（），makeList（）；
	获取所选目录值函数 evaluate()；
*********************************************************/
/*

var i,                  //记录数组下标
    t1,				    //记录标题中的第一个数据
	t2,					//记录标题中的第二个数据				  
	t3,					//记录标题中的第三个数据
	phase,				//记录文档阶段
	id,					//记录查找数据库内容的关键字
	dataArray,			//记录从数据库查询的各章节内容
	dataNum,			//记录从数据库查询的数据个数
	ajaxreq,			//表示一个ajax请求
	array,				//用于记录对dataArray转变后的数据存储
	sub_i,				//sub_i表示array数组中同种标题不同版本的第一个数据位置
	nameNum,			//用于记录子目录的号码
	listArray;          //用于记录二级目录的个数
	str = "";	

*/
function evaluate(t1,t2,t3,temp_id,i,tempTrad)			//temp_id用于记录id，i表示array数组中同种标题不同版本的第一个数据位置
{
	var temp,temp_len;
	id = temp_id;
	trad = tempTrad;
	temp_len = version.length;
	if(temp_len!=0)
	{
		for(temp = 0;temp < temp_len;temp++)
		{
			version.remove(0);
		}
	}
	temp = i;
	sub_i = i;
	do
	{
		var y=document.createElement('option');
		y.text = array[temp][4];
		version.add(y);
		temp++;
	}while(temp<dataNum&&array[temp][5]);
}

function flex2List(tempNum)
{
	var valu = "grandson" + tempNum;
	if(document.getElementById(valu))
	{
		var tempName = eval("grandson"+tempNum);
		tempName.style.display = (tempName.style.display == 'none')?'':'none';
	}
}

function flex1List(flexNum)              //flexNum存储一级目录的号码
{
	for(i=listArray[flexNum-1]+1;i<=listArray[flexNum];i++)
	{
		var valu = "child" + i;
		if(document.getElementById(valu))
		{
			tempName = eval("child"+i);
			if(tempName.style.display == 'none')
			{
				tempName.style.display = ''
			}
			else
			{
				tempName.style.display = 'none';
				valu = "grandson" + i;
				if(document.getElementById(valu))
				{
					tempName = eval("grandson"+i);
					tempName.style.display = 'none';
				}
			}
		}
	}
}
function makeList()
{
	if(!array[i][5])
	{
		if(array[i][1] == 0)
		{
			//document.write("<dl> <div id=\"main1\" style=\"color:blue\" onclick=\"flex1List("+array[i][0]+")\" ><dt>"+"<a href=\"javascript: evaluate("+array[i][0]+",0,0,"+array[i][3]+","+i+")\">"+array[i][0]+".  </a> </dt></div>");
			str += "<dl> <div id=\"main1\" style=\"color:blue\" onclick=\"flex1List("+array[i][0]+")\" ><dt>"+"<a href=\"javascript: evaluate("+array[i][0]+",0,0,"+array[i][3]+","+i+",1)\">"+array[i][0]+".  </a> </dt></div>";
			var j;
			for(j=i+1;j<dataNum;j++)
			{
			    if(array[j][5]==0)
				break;
			}
			i = j;
			if(i<dataNum&&(array[i][1]!=0))
				makeList();
			str += "</dl>";
			//document.write("</dl>");
			if(i<dataNum)
				makeList();
		}
		else if(array[i][2] == 0)
		{
			nameNum++;
			//document.write("<dd> <dl><div id=\"child"+nameNum+"\" style=\"display:none\" onclick=\"javascript: flex2List("+nameNum+")\" > <dt>"+"<a href=\"javascript: evaluate("+array[i][0]+","+array[i][1]+",0,"+array[i][3]+","+i+")\">"+array[i][0]+"."+array[i][1]+".</a></dt></div>");
			str += "<dd> <dl><div id=\"child"+nameNum+"\" style=\"display:none\" onclick=\"javascript: flex2List("+nameNum+")\" > <dt>"+"<a href=\"javascript: evaluate("+array[i][0]+","+array[i][1]+",0,"+array[i][3]+","+i+",2)\">"+array[i][0]+"."+array[i][1]+".</a></dt></div>";
			var j;
			for(j=i+1;j<dataNum;j++)
			{
			    if(array[j][5]==0)
				break;
			}
			i = j;
			if(i<dataNum&&(array[i][2]!=0))
				makeList();
			str += "</dl> </dd>";
			//document.write("</dl> </dd>");
			if(i<dataNum&&array[i][1]!=0)
				makeList();
		}
		else
		{
			//document.write("<div id=\"grandson"+nameNum+"\" style=\"display:none\">");
			str += "<div id=\"grandson"+nameNum+"\" style=\"display:none\">"
			
			while(i<dataNum&&array[i][2]!=0)
			{
				//document.write(" <dd>"+"<a href=\"javascript: evaluate("+array[i][0]+","+array[i][1]+","+array[i][2]+","+array[i][3]+","+i+")\">"+array[i][0]+"."+array[i][1]+"."+array[i][2]+".</a></dd>");
				if(!array[i][5])
				    str += " <dd>"+"<a href=\"javascript: evaluate("+array[i][0]+","+array[i][1]+","+array[i][2]+","+array[i][3]+","+i+",3)\">"+array[i][0]+"."+array[i][1]+"."+array[i][2]+".</a></dd>";

				i=i+1;
			}
			//document.write("</div>");
			str += "</div>";
		}
	}
	else
	{
		i++;
		if(i<dataNum)
			makeList();
	}
}
function beList()
{
	array = null;
	array = new Array(dataNum);
	var tempT1 = 1,tempT2 = 0, tempT3 = 0,flag = 0;     //tempT1表示标题第一个数据
	                                                    //tempT2表示标题第二个数据
														//tempT3表示标题第三个数据
														//flag表示此数据与上一个标题是否相等，如果相等为1，不相等为0
	var temp=1; 										//用于统计一级目录的个数
	for(i=0;i<dataNum;i++)
		array[i]=new Array(6);
	array[0][0] = tempT1;
	array[0][1] = tempT2;
	array[0][2] = tempT3;
	array[0][3] = dataArray[0][3];         // id号码
	array[0][4] = dataArray[0][4];  		// 版本号
	array[0][5] = flag;

	for( i= 1; i < dataNum; i++)
	{

 		if( (dataArray[i][0] == dataArray[i-1][0]) && (dataArray[i][1] == dataArray[i-1][1]) && (dataArray[i][2] != dataArray[i-1][2]) )
		{
			tempT3++;
			flag = 0;
		}

		else if( (dataArray[i][0] == dataArray[i-1][0]) && (dataArray[i][1] != dataArray[i-1][1]) )
		{
			tempT2++;
			tempT3 = 0;
			flag = 0;
		}
		else if( dataArray[i][0] != dataArray[i-1][0] )
		{
			tempT1++;
			tempT2 = 0;
			tempT3 = 0;
			flag = 0;
		}
		else
		{
			flag = 1;
		}

		array[i][0] = tempT1;
		array[i][1] = tempT2;
		array[i][2] = tempT3;
		array[i][3] = dataArray[i][3];
		array[i][4] = dataArray[i][4];
		array[i][5] = flag;
		if(tempT2==0&&flag==0)
			temp++;

		//alert(array[i][0]+"."+array[i][1]+"."+array[i][2]+".flag="+array[i][5]);
 	}
	lisstArray = null;
	listArray = new Array(temp+1);   //统计一级目录个数
	for(i=0;i<temp+1;i++)
	{
		listArray[i]=0;
	}
	var j = 0;                       //对应listArray下标
	for(i=0;i<dataNum;i++)
	{
		if(array[i][1]==0&&array[i][5]==0)
		{
			j++;
			listArray[j]=listArray[j-1];
		}
		
		if(array[i][1]!=0&&array[i][2]==0&&array[i][5]==0)
		{	
			listArray[j]++;
		}
	}

	i=0;
	nameNum=0;
	makeList();
}
