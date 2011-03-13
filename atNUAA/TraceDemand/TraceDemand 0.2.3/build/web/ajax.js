/*
 *有关ajax的操作，算是完成一点点封装
 *使用时：
 * 调用send(operationType,sendContent) 发送数据
 * 实现 handle()进行返回后的操作
 */

var ajax;
function createXMLHttpRequest() //创建XMLHttpRequest对象
{
	try{
		ajax = new ActiveXObject("Msxml2.ajax");
	}catch(_e){
		try{
			ajax = new ActiveXObject("Microsoft.XMLHTTP");
		}catch(_E){
			try{
				ajax = new XMLHttpRequest();
			}catch(e){
				document.write("This browser does't support Ajax!");
			}
		}
	}
}

function send(operationType,sendContent) /* 发送数据 */
{
	createXMLHttpRequest();
	ajax.onreadystatechange = handleStateChange;
	ajax.open("POST","Work",false);
	ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded;");
	ajax.send("operationType="+operationType+"&"+sendContent);
}

function handleStateChange() //返回处理
{
	if(ajax.readyState == 4)
	{
		handle();
	}
}

/******以下是方便报错***********/
function errorHandler(message,url,line)
{
	var errorMessage = "Error: "+message +"\n";
	errorMessage += "URL: " + url + "\n";
	errorMessage += "Line Number: " + line +"\n";
	alert(errorMessage);
	return true;
}
onerror = errorHandler ;
