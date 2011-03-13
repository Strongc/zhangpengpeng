

package trdd;

import java.sql.*;
import java.util.Vector;


/**
 *
 * @author Roc
 */
public class DocTitle {
    TitleNode titleNode;
    public Vector nodes = new Vector();
    
    public void refresh() throws ClassNotFoundException, SQLException
    {
		Class.forName("com.mysql.jdbc.Driver");
		Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/trdd", "root", "123456");
		Statement stmt = conn.createStatement();
		ResultSet rSet = stmt.executeQuery("select * from doctitle;"); //executeUpdate();
		nodes.removeAllElements(); //将原来的东西清除掉，以便写入最新的目录节点
		while (rSet.next())
		{
		    titleNode = new TitleNode();

		    titleNode.t1 = rSet.getFloat("t1");
		    titleNode.t2 = rSet.getFloat("t2");
		    titleNode.t3 = rSet.getFloat("t3");
		    titleNode.phase = rSet.getInt("phase");
		    titleNode.version = rSet.getInt("version");
		    titleNode.preversion = rSet.getInt("preversion");
		    titleNode.available = rSet.getInt("available");
		    titleNode.id = rSet.getString("id");

		    nodes.add(titleNode); // 将目录节点放入vector nodes;
		}
		rSet.close();
		stmt.close();
		conn.close();

    }

    public int getNum()
    {
	return nodes.size();
    }

}
