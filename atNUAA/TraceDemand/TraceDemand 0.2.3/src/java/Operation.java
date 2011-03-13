/**
 *
 * @author Roc
 */
import trdd.DocContent;
import trdd.Message;
import trdd.Role;
import trdd.DocTitle;

public abstract class Operation {
	Message message;
	Role role;
	DocTitle docTitle;
	DocContent docContent;
	String operationType;

	public boolean process(Role role,Message message,DocTitle docTitle,DocContent docContent) //处理给定的角色+输入输出，给外界调用
	{
		this.role=role;
		this.message=message;
		this.docTitle=docTitle;
		this.docContent=docContent;
		this.operationType=getClass().getName();
		return process();
	}

	public abstract boolean process();	//process operation.

	//public abstract boolean inform();	//inform other cooperator what is modified.
	//同时也要记录日志


	public Message getMessage()
	{
		return message;
	}
	public Role getRole()
	{
		return role;
	}
	public DocContent getDocContent()
	{
		return docContent;
	}
	public String getOperationType()
	{
		return operationType;
	}

}
