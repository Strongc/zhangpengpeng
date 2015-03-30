
/**
 *
 * @author yang
 */
import trdd.*;
public class Query extends Operation {

	public boolean process()
	{
		boolean result=true;
        ContentNode cn=message.getContentNode();

        docContent.setQueryStmt("id=" + cn.id);
		
		return result;
	}
}
