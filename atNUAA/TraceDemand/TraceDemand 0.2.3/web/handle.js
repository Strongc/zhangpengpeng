/************************************************************
	获取服务器返回xml数据并处理handle()；
*************************************************************/

function handle()
{
	if(state==0)                                           //state=0表示刷新目录
		{
			var temp_node,j;
			var xmlDoc = ajax.responseXML;
			var father_node = xmlDoc.getElementsByTagName("docTitle")[0];
			var content_list = father_node.getElementsByTagName("titleNode");
			dataNum = content_list.length;
			dataArray = null;
			dataArray = new Array(dataNum);
			for( j = 0 ;j < content_list.length; j++)
			{
				dataArray[j] = new Array(5)
				temp_node = content_list[j];
				dataArray[j][0] = temp_node.getElementsByTagName("t1")[0].childNodes[0].nodeValue;
				dataArray[j][1] = temp_node.getElementsByTagName("t2")[0].childNodes[0].nodeValue;
				dataArray[j][2] = temp_node.getElementsByTagName("t3")[0].childNodes[0].nodeValue;
				dataArray[j][3] = temp_node.getElementsByTagName("id")[0].childNodes[0].nodeValue;
				dataArray[j][4] = temp_node.getElementsByTagName("version")[0].childNodes[0].nodeValue;
			}
		}
	else	if(state == 1)				//state=1表示获取章节内容
		{
			var xmlDoc = ajax.responseXML;
			var Node = xmlDoc.getElementsByTagName("docContent")[0];
			var nodeList = Node.getElementsByTagName("contentNode")[0];
			var val1 = nodeList.getElementsByTagName("content")[0];
			var temp = val1.childNodes[0].nodeValue;
			var responseDiv = document.getElementById("content");
			responseDiv.value = temp;
		}
}