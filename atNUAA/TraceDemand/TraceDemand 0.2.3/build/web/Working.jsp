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
        <title>����׷��ϵͳ--<jsp:getProperty name="role" property="username" /></title>

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
�汾�ţ�
<select name="version">
</select>
<input name="ok" type="button" id="ok" value="�鿴�˰汾" onclick="query()">
</br>

����:
</br>


<!--��ʾ�½����ݵ�һ��textarea-->
<textarea cols=100 rows=30 id="content" name="content" value="" style="background-color:BFCEDC"></textarea>
<input name="ok" type="button" value="ˢ��Ŀ¼" onclick="changeList()"></input>

</br>
<input name="ok" type="button" value="�����" onclick="addUp()"></input>
<input name="ok" type="button" value="�����" onclick="addDown()"></input>
<input name="ok" type="button" value="�����" onclick="addChild()"></input>
&nbsp; &nbsp;
<input name="ok" type="button" value="�޸�" onclick="edit()"></input>
<input name="ok" type="button" value="ɾ��" onclick="del()"></input>
&nbsp;&nbsp;&nbsp;&nbsp;
<input name="ok" type="button" value="ȷ�����" onclick="addConfirm()"></input>
</div>

<div id = "mainList" class = "sty2">
	<p></p>
	<p><%=role.getUsername()%> is working now.</p>
	<p>Authority:<%=role.getAuthority()%> </p>
</br>
�׶�: �������
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
