/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Administrator
 */
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import trdd.*;
public class Delete extends Operation {

	public boolean process()
	{
		boolean result=true;
        ContentNode cn=message.getContentNode();

        docContent.setDeleteStmt("id=" + cn.id);

            try {
                docContent.delete();
            } catch (SQLException ex) {
                Logger.getLogger(Delete.class.getName()).log(Level.SEVERE, null, ex);
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(Delete.class.getName()).log(Level.SEVERE, null, ex);
            }

		return result;
	}
}
