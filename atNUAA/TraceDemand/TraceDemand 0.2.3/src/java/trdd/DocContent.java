/**
 *
 * @author 许文平
 * time  2009-9-1
 */
package trdd;
import java.sql.*;


public class DocContent {

	Connection conn; //用来连接数据库
	Statement stmt = null;
	ResultSet rSet = null;
        ContentNode contentNode;
	String queryStmt=null;
        String updateStmtDT=null;
        String updateStmtDC=null;
	String deleteStmt=null;

        public DocContent()
        {
             contentNode = new ContentNode();
        }

	public String getDeleteStmt() {
		return deleteStmt;
	}

	public void setDeleteStmt(String deleteStmt) {
		this.deleteStmt = deleteStmt;		
	}

	public String getQueryStmt() {
		return queryStmt;
	}

	public void setQueryStmt(String queryStmt) {
		this.queryStmt = queryStmt;	
	}

	public String getUpdateStmtDC() {
		return updateStmtDC;
	}

	public void setUpdateStmtDC(String updateStmtDC) {
		this.updateStmtDC = updateStmtDC;
	}

	public String getUpdateStmtDT() {
		return updateStmtDT;
	}

	public void setUpdateStmtDT(String updateStmtDT) {
		this.updateStmtDT = updateStmtDT;
	}

	private void conDataBase() throws ClassNotFoundException, SQLException
	{
	    Class.forName("com.mysql.jdbc.Driver");   //数据库连接
	    conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/trdd", "root", "123456");
	    //System.out.println("数据库连接成功！");
	}

	private void closeDataBase() throws SQLException
	{
	         //数据库关闭
		stmt.close();
		conn.close();
	}

	public ContentNode getContentNode() throws SQLException, ClassNotFoundException   //根据queryStmt用于查询后返回内容
	{
            int   i ;
            byte  tempByte[] ;
            long  tempLength ;
            Blob  tempBlob ;
		
	      conDataBase();
	      try
              {
		  stmt = conn.createStatement();
                  queryStmt="select * from doccontent where "+ queryStmt ;  
		  rSet = stmt.executeQuery( queryStmt );
		  
              }catch( SQLException e )
              {
                   //异常处理
              }


		if(rSet.next())
		{
			    contentNode.id = rSet.getString("id");
			    contentNode.author = rSet.getString("author");
			    contentNode.edittime = rSet.getString("edittime");

                            tempBlob = rSet.getBlob("content");//将Blob格式转化成String类型。
                            tempLength = tempBlob.length();		    
                            tempByte = tempBlob.getBytes(1 ,(int)tempLength) ;
  
			    contentNode.content = new String( tempByte) ;
		
		}

	        queryStmt = null ;
		rSet.close();   
                closeDataBase();    //数据库关闭
		
		return contentNode;
	}




        public void update()  throws SQLException, ClassNotFoundException //根据updateStmtDT,updateStmtDC执行 add & edit 操作
        {
             conDataBase();

	      try
              {
		  stmt = conn.createStatement();

                  updateStmtDC = "insert into doccontent values(" + updateStmtDC + ")" ;
                  updateStmtDT = "insert into doctitle   values(" + updateStmtDT + ")" ;
		  stmt.executeUpdate( updateStmtDC  );
                  stmt.executeUpdate( updateStmtDT );

              }catch( SQLException e )
              {
                  //捕捉异常
              }


                closeDataBase();    //数据库关闭
		
        }


	public void delete() throws SQLException, ClassNotFoundException //根据deleteStmt执行delete操作(其实并未删除数据，只是将doccontent属性的修改)
	{
              
               conDataBase();

	      try
              {
		      stmt = conn.createStatement();
		      deleteStmt = " update doctitle set available = 0 where " + deleteStmt;	       
		      stmt.executeUpdate(deleteStmt);
		   
              }catch( SQLException e )
              {
                  //
              }

                closeDataBase();    //数据库关闭
		
	}


}



