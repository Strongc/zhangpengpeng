<%@ language="javascript" %>
<!--���¸���2008��11��18�գ����ڼ�¼���ԣ�debug���˺ܳ�ʱ�䣬û��ר�ŵ�debug���ߣ�ֻ�øĵ��Ե�----�� rocflyhi@gmail.com--> 

<%Response.Charset="gb2312"%>

<html>
	<head>
		<meta name="author" content="rocflyhi@gmail.com"> 
		<meta name="generator" content="Text Editor: UltraEdit,Notepad++&Notepad"> 
		<meta name="description" content="www.rocflyhi.cn Roc's personal website"> 
		<meta name="keywords" content="rocflyhi,����Ľ���"> 
		<title>лл��ע������Ľ���</title>
		<link rel="stylesheet" type="text/css" href="../style/myfirststyle.css">
		<style type="text/css">
			body{
				background-image:url("image1.jpg");
			} 
			a.back{
				position:absolute;
				top:420px;
				left:40%;
				font-size:120%;
			}
			p.welcome{
				font-weight:bold;
				font-size:130%;
				position:absolute;
				left:30%;
				top:250px;
			}
			div.main2{
				text-indent: 1cm;
				width:500px;
				font-size:120%;
				position:absolute;
				left:28%;
				top:350px;
			}
	</style>
	</head>
	
	<body>
		<img id="author" src="../global_files/image7.jpg">
		<img id="head" src="../global_files/image3.gif">
		<img id="about" src="image4.gif">
		<img id="mywebsite" src="../global_files/image9.gif">
	
		<%
			var str=Request.Form("cmm");
			var fs=Server.CreateObject("Scripting.FileSystemObject")
			var mypath=Server.MapPath("\\about") + "\\cmm.txt";
			fname=fs.OpenTextFile(mypath,8);
			var tm=new Date();
			fname.WriteLine("#**______ IP :"+Request.ServerVariables("remote_addr")+"___Time:"+tm+" ______**#");
			fname.WriteLine(str);
			fname.WriteLine("#*----------------------------------------------------------------------------------------------------*#");
			fname.Close();
		%>
		
		<p class="welcome">
			лл���Ĺ�ע����
		</p>
		
		<div class="main2">
			<span style="font-weight:normal;">
				 ��ϵ�ң��������õ����ʼ�  <a class="small" href="mailto:i@rocflyhi.cn">i@rocflyhi.cn</a><br>
			</span>
		</div>		
		<a class="back" href="/about">����</a>
	</body>
</html>