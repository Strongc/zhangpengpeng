package trdd;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Role {
	String username;
	String password;
	int authority;  //0表示登录失败


	public boolean login(String username,String password) throws ClassNotFoundException, SQLException	//判断是否登录成功
	{
		boolean result=false;
		this.username = username;
		this.authority=0;

		Class.forName("com.mysql.jdbc.Driver");
		Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/trdd", "root", "123456");
		Statement stmt = conn.createStatement();
		ResultSet rSet = stmt.executeQuery("select * from role where username='" + username + "';");
		if (rSet.next())
		{
			if (rSet.getString(2).equals(password))
			{
				this.authority = Integer.parseInt(rSet.getString(3));	//登录成功同时更改权限值
				result=true;
			} 
		}
		rSet.close();
		stmt.close();
		conn.close();

		return result;

	}
	
	
	//记录到日志

	public String getUsername()
	{
		return username;
	}
	public int getAuthority()
	{
		return authority;
	}

/*
	public void setId(String id)
	{
		this.id=id;
	}
	public String getId()
	{
		return id;
	}
	public void setName(String name)
	{
		this.name=name;
	}
	public String getName()
	{
		return name;
	}
*/

}
