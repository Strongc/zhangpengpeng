/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author yang
 */
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import trdd.*;
public class Edit extends Operation {

	public boolean process()
	{
		boolean result=true;
        ContentNode cn=message.getContentNode();
        TitleNode tn=message.getTitleNode();
        
        String id = new Double(Math.random()).toString();

        docContent.setUpdateStmtDC("'" + id + "','" + this.role.getUsername() + "', now() ,'"+ cn.content + "'");
        /*docContent.setUpdateStmtDT(tn.t1 + "," + tn.t2 + "," + tn.t3 + ","+ tn.phase + ","
        + tn.version + ","+ tn.preversion + ","+ tn.available + ","+ "'" + id + "'");*/
        docContent.setUpdateStmtDT(tn.t1 + "," + tn.t2 + "," + tn.t3 + ","+ tn.phase + ","
                + (message.getMaxVersion() + 1) + ","+ tn.version + ","+ 1 + ","+ "'" + id + "'");

        try {
            docContent.update();
        } catch (SQLException ex) {
            Logger.getLogger(Edit.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Edit.class.getName()).log(Level.SEVERE, null, ex);
        }
        return result;
	}
}
