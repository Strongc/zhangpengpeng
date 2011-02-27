<%@ Language="JavaScript" %>
<html>
<body>

<%Response.Charset="UTF-8"%>

<p>
<b>您正在通过这款浏览器访问我们的站点：</b>
<%Response.Write(Request.ServerVariables("http_user_agent"))%>
</p>
<p>
<b>您的 IP 地址是：</b>
<%Response.Write(Request.ServerVariables("remote_addr"))%>
</p>
<p>
<b>IP 地址的 DNS 查询是：</b>
<%Response.Write(Request.ServerVariables("remote_host"))%>
</p>
<p>
<b>调用该页面所用的方法是：</b>
<%Response.Write(Request.ServerVariables("request_method"))%>
</p>
<p>
<b>服务器的域名：</b>
<%Response.Write(Request.ServerVariables("server_name"))%>
</p>
<p>
<b>服务器的端口：</b>
<%Response.Write(Request.ServerVariables("server_port"))%>
</p>
<p>
<b>服务器的软件：</b>
<%Response.Write(Request.ServerVariables("server_software"))%>
</p>
<a href="/">返回首页</a>
<h2>____________________________________________________________</h2>
<h3>具体浏览器信息</h3>
<Script>
	with(document)
	{
		title="测试浏览器信息";
		with(navigator)
		{
			write("代码：",appCodeName);
			write("<br>名称：",appName);
			write("<br>版本：",appVersion);
			write("<br>平台：",platform);
			write("<br>用户表头：",userAgent);
		}
	}
</Script> 
</body>
</html>

