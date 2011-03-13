/*
 * 控制整个系统的运行流程
 */


import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import trdd.*;

/**
 *
 * @author Roc
 */
public class Work extends HttpServlet {
   
    /** 
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
     HttpServletRequest request;
     HttpServletResponse response;
     HttpSession session;
     Role role;
     DocTitle docTitle;
     DocContent docContent;
     Message message;
     String operationType;

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException{
        response.setContentType("text/html;charset=GB2312");
	response.setDateHeader("Expires", 0);
	response.setHeader("Cache-Control", "no-cache");
	response.setHeader("Pragma", "no-cache");
	PrintWriter out = response.getWriter();
	this.request = request;
	this.response = response;
	session=request.getSession(false);
	if(session==null)	//判断是否time out
	{
		out.println("已经超时了，我该如何处理才能返回到登录界面呢？");
		out.close();
		return ;
	}


	// <editor-fold defaultstate="collapsed" desc="获得（生成）属性，也即javabean">
	role=(Role)session.getAttribute("role");

	docTitle=(DocTitle)session.getAttribute("docTitle");
	if(docTitle==null)
	{
		docTitle = new DocTitle();
		session.setAttribute("docTitle", docTitle);
	}
	
	docContent=(DocContent)session.getAttribute("docContent");
	if(docContent==null)
	{
		docContent = new DocContent();
		session.setAttribute("docContent", docContent);
	}
	// </editor-fold>

	// <editor-fold  defaultstate="collapsed" desc="生成Message里面的具体内容 需要调用prepareForX()">

	operationType = request.getParameter("operationType");
	message = new Message();
	message.setOperationType(operationType);
	//根据操作类型，做好准备，继续完善Message里的内容
	if(operationType == null)
	{
		request.getRequestDispatcher("/Working.jsp").forward(request, response);//首次进入，直接返回
		return ;
	}
	else
		if(operationType.equals("GetList"))
		{
			request.getRequestDispatcher("/Return").forward(request, response); //处理成功，working.jsp
			return ;
		}
		else
			if(operationType.equals("Query"))
				prepareForQuery();
			else
				if(operationType.equals("Add"))
					prepareForAdd();
				else
					if(operationType.equals("Edit"))
						prepareForEdit();
					else
						if(operationType.equals("Delete"))
							prepareForQuery();
	//</editor-fold>

	// <editor-fold defaultstate="collapsed" desc="处理'操作'">
	Operation operation = null;

		try {
			try {
				operation = (Operation) Class.forName(operationType).newInstance(); //根据操作，创建相应的类
			} catch (InstantiationException ex) {
				Logger.getLogger(Work.class.getName()).log(Level.SEVERE, null, ex);
			} catch (IllegalAccessException ex) {
				Logger.getLogger(Work.class.getName()).log(Level.SEVERE, null, ex);
			}
		} catch (ClassNotFoundException ex) {
			Logger.getLogger(Work.class.getName()).log(Level.SEVERE, null, ex);
		}
	
	if(operation.process(role,message,docTitle,docContent)==true)  //调用operation的具体子类处理操作
		request.getRequestDispatcher("/Return").forward(request, response); //处理成功，working.jsp
	else
	{
		//处理失败，。。。。
	}
	
    // </editor-fold>

	out.close();

    } 

    // <editor-fold defaultstate="collapsed" desc="void prepareForQuery() 为Query操作做准备">
    void prepareForQuery()
    {
	String id = request.getParameter("id");
	message.getTitleNode().id = id;
	message.getContentNode().id = id;
    }
    // </editor-fold>
   
    // <editor-fold defaultstate="collapsed" desc="void prepareForAdd() 为Add操作做准备">
    void prepareForAdd()
    {
	//生成message.titleNode
	message.getTitleNode().t1 = Float.parseFloat(request.getParameter("t1"));
	message.getTitleNode().t2 = Float.parseFloat(request.getParameter("t2"));
	message.getTitleNode().t3 = Float.parseFloat(request.getParameter("t3"));
	message.getTitleNode().phase = Integer.parseInt(request.getParameter("phase"));

	//生成message.contentNode : author由role获得,edittime为插入数据时Now()，id为插入时随机生成的32位数
	message.getContentNode().content = request.getParameter("content");

    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="void prepareForEdit() 为Edit操作做准备">
    void prepareForEdit()
    {
	//生成message.titleNode
	message.getTitleNode().t1 = Float.parseFloat(request.getParameter("t1"));
	message.getTitleNode().t2 = Float.parseFloat(request.getParameter("t2"));
	message.getTitleNode().t3 = Float.parseFloat(request.getParameter("t3"));
	message.getTitleNode().phase = Integer.parseInt(request.getParameter("phase"));
	message.getTitleNode().version = Integer.parseInt(request.getParameter("version"));

	//获得该节点最大的版本号
	message.setMaxVersion(Integer.parseInt(request.getParameter("maxVersion")));

	//生成message.contentNode : author由role获得,edittime为插入数据时Now()，id为插入时随机生成的32位数
	message.getContentNode().content = request.getParameter("content");
   }
    // </editor-fold>
    
    // <editor-fold defaultstate="collapsed" desc="void prepareForDelete() 为Delete操作做准备">
    void prepareForDelete()
    {
	String id = request.getParameter("id");
	message.getTitleNode().id = id;
	message.getContentNode().id = id;
    }
    // </editor-fold>


    // <editor-fold defaultstate="collapsed" desc="HttpServlet 方法。单击左侧的 + 号以编辑代码。">
    /** 
     * Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    } 

    /** 
     * Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    }

    /** 
     * Returns a short description of the servlet.
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
