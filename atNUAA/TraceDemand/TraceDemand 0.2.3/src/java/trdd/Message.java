/**
 *
 * @author Roc
 */
package trdd;

public class Message {
	String operationType;
	TitleNode titleNode =new TitleNode();
	ContentNode contentNode = new ContentNode();

	//for edit opetation
	int maxVersion;

	public void setOperationType(String operationType){
		this.operationType=operationType;
	}

	public String getOperationType(){
		return operationType;
	}

	public ContentNode getContentNode() {
		return contentNode;
	}

	public void setContentNode(ContentNode contentNode) {
		this.contentNode = contentNode;
	}

	public TitleNode getTitleNode() {
		return titleNode;
	}

	public void setTitleNode(TitleNode titleNode) {
		this.titleNode = titleNode;
	}

	public int getMaxVersion() {
		return maxVersion;
	}

	public void setMaxVersion(int maxVersion) {
		this.maxVersion = maxVersion;
	}

	

}
