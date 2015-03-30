<%-- 
    Document   : index
    Created on : 2009-7-14, 18:17:59
    Author     : Roc
--%>

<%@page contentType="text/html" pageEncoding="GB2312"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=GB2312">
        <title>需求追踪系统</title>
    </head>
    <body>
        <h1>Welcome to 需求追踪系统</h1>
		<p> 请登录 </p>
		<form action="do" method="post">
			用户名：<input type="text" name="username" value="${param.username}" /><br/>
			密  码：<input type="password" name="password" /><br/>
			<input type="submit" value="登录"/><br/>
			${param.loginError}
		</form>
    </body>
</html>
