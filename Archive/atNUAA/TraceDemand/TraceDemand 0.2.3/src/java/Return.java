/*
 * 返回给客户端信息
 */


import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import trdd.*;

/**
 *
 * @author XuWenping
 */
public class Return extends HttpServlet {
   
    /** 
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
     Role role;
     DocTitle docTitle;
     DocContent docContent;
     String operationType;

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/xml;charset=UTF-8");
        PrintWriter out = response.getWriter();
	HttpSession session=request.getSession(false);

	// <editor-fold defaultstate="collapsed" desc="获得（生成）属性，也即javabean 以及operation">
	role=(Role)session.getAttribute("role");
	docTitle=(DocTitle)session.getAttribute("docTitle"); 
	docContent=(DocContent)session.getAttribute("docContent");
	operationType = request.getParameter("operationType");
	// </editor-fold>

        try { 

		if(operationType.equals("Query"))
	    {
		out.println("<?xml version=\"1.0\" encoding=\"GB2312\" ?>");
		out.println("<docContent>");
		out.println("	"+"<contentNode>");
		out.println("	    "+"<id>"+docContent.getContentNode().id +"</id>");
		out.println("	    "+"<author>"+docContent.getContentNode().author+"</author>");
		out.println("	    "+"<edittime>"+docContent.getContentNode().edittime+"</edittime>");
		out.println("	    "+"<content>"+docContent.getContentNode().content+"</content>");
		out.println("	"+"</contentNode>");
		out.println("</docContent>");
	    }

	    else
	    {
		    	docTitle.refresh();	    //保证title每次显示最新的数据

			out.println("<?xml version=\"1.0\" encoding=\"GB2312\" ?>");
			out.println("<docTitle>");
		 for( int i = 0 ; i < docTitle.getNum() ; i++ )
		 {
			TitleNode titleNode = (TitleNode)docTitle.nodes.get(i);

			
			out.println("	"+"<titleNode>");
			out.println("	    "+"<t1>"+titleNode.t1+"</t1>");
			out.println("	    "+"<t2>"+titleNode.t2+"</t2>");
			out.println("	    "+"<t3>"+titleNode.t3+"</t3>");
			out.println("	    "+"<phase>"+titleNode.phase+"</phase>");
			out.println("	    "+"<version>"+titleNode.version+"</version>");
			out.println("	    "+"<preversion>"+titleNode.preversion+"</preversion>");
			out.println("	    "+"<available>"+titleNode.available+"</available>");
			out.println("	    "+"<id>"+titleNode.id+"</id>");
			out.println("	"+"</titleNode>");

			
		 }
			out.println("</docTitle>");

	    }

        }catch(SQLException e ){
		//处理异常
	}catch(ClassNotFoundException e){
		//处理异常
	}finally {
            out.close();
        }
    } 

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
