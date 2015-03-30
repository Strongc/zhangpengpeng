<%--
    Document   : Working
    Created on : 2009-7-14, 19:53:43
    Author     : Roc,chen,wen
--%>

<%@page contentType="text/html" pageEncoding="GB2312"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

	<jsp:useBean id="role" class="trdd.Role" scope="session"/>
	<jsp:useBean id="docTitle" class="trdd.DocTitle" scope="session"/>
	<jsp:useBean id="docContent" class="trdd.DocContent" scope="session"/>
	
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=GB2312">
        <title>需求追踪系统--<jsp:getProperty name="role" property="username" /></title>

	<style type = "text/css">

.sty1
{
	position: absolute;
	left: 300px;
	top:  30px;
}

.sty2
{
	position: absolute;
	left: 70px;
	top:  30px;
}


</style>

<script type="text/javascript" language="javascript">
var array,i,t1,
    t2,t3,phase,
    id,vers,preVers,avail,dataArray,maxVers,dataNum,state=0,trad,listArray,str="",cont,sub_i,ajaxreq;
</script>
	<script type="text/javascript" src="ajax.js"></script>
	<script type="text/javascript" src="handle.js"></script>
	<script type="text/javascript" src="makeList.js"></script>
	<script type="text/javascript" src="send.js"></script>

    </head>
    <body>


<div class = "sty1">
版本号：
<select name="version">
</select>
<input name="ok" type="button" id="ok" value="查看此版本" onclick="query()">
</br>

内容:
</br>


<!--显示章节内容的一个textarea-->
<textarea cols=100 rows=30 id="content" name="content" value="" style="background-color:BFCEDC"></textarea>
<input name="ok" type="button" value="刷新目录" onclick="changeList()"></input>

</br>
<input name="ok" type="button" value="上添加" onclick="addUp()"></input>
<input name="ok" type="button" value="下添加" onclick="addDown()"></input>
<input name="ok" type="button" value="子添加" onclick="addChild()"></input>
&nbsp; &nbsp;
<input name="ok" type="button" value="修改" onclick="edit()"></input>
<input name="ok" type="button" value="删除" onclick="del()"></input>
&nbsp;&nbsp;&nbsp;&nbsp;
<input name="ok" type="button" value="确认添加" onclick="addConfirm()"></input>
</div>

<div id = "mainList" class = "sty2">
	<p></p>
	<p><%=role.getUsername()%> is working now.</p>
	<p>Authority:<%=role.getAuthority()%> </p>
</br>
阶段: 需求分析
</br>
</br>
<div id = "contentList">

</div>

</div>
	    <script type="text/javascript" >
		changeList();
	    </script>
    </body>
</html>
