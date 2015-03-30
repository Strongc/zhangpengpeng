
/**
 *
 * @author yang
 */
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import trdd.*;

public class Add extends Operation{

	public boolean process()
	{
		boolean result=true;
        String stmtDT=null , stmtDC=null;
        ContentNode cn=message.getContentNode();
        TitleNode tn=message.getTitleNode();

        String id = new Double(Math.random()).toString();

        docContent.setUpdateStmtDC("'" + id + "','" + this.role.getUsername() + "', now() ,'"+ cn.content + "'");
        docContent.setUpdateStmtDT(tn.t1 + "," + tn.t2 + "," + tn.t3 + ","+ tn.phase + ","
                + 1 + ","+ 0 + ","+ 1 + ","+ "'" + id + "'");
        try {
            docContent.update();
        } catch (SQLException ex) {
            Logger.getLogger(Add.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Add.class.getName()).log(Level.SEVERE, null, ex);
        }
		return result;
	}
}