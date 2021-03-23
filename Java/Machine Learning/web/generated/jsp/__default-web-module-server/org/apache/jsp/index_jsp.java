package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;

public final class index_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List<String> _jspx_dependants;

  private org.glassfish.jsp.api.ResourceInjector _jspx_resourceInjector;

  public java.util.List<String> getDependants() {
    return _jspx_dependants;
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;

    try {
      response.setContentType("text/html");
      response.setHeader("X-Powered-By", "JSP/2.3");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;
      _jspx_resourceInjector = (org.glassfish.jsp.api.ResourceInjector) application.getAttribute("com.sun.appserv.jsp.resource.injector");

      out.write("<!DOCTYPE html>\r\n");
      out.write("<html charset=UTF-8 dir=ltr encoding=UTF-8 itemtype=http://schema.org/WebPage lang=en-US language=English prefix=og:http://ogp.me/ns>\r\n");
      out.write("    <head prefix=lapys:https://www.lapys.dev/>\r\n");
      out.write("        <!-- Document Metadata -->\r\n");
      out.write("        <meta charset=\"UTF-8\"/>\r\n");
      out.write("        <meta content=chrome=1 http-equiv=\"X-UA-Compatible\"/>\r\n");
      out.write("\r\n");
      out.write("        <!-- Document Stylesheet -->\r\n");
      out.write("        <style media=all type=text/css> </style>\r\n");
      out.write("\r\n");
      out.write("        <!-- Document Title -->\r\n");
      out.write("        <title> Car Fuel Prediction </title>\r\n");
      out.write("    </head>\r\n");
      out.write("\r\n");
      out.write("    <body>\r\n");
      out.write("        <!-- Main -->\r\n");
      out.write("        <div id=main> </div>\r\n");
      out.write("\r\n");
      out.write("        <!-- Document Script -->\r\n");
      out.write("        <script language=javascript type=text/javascript> </script>\r\n");
      out.write("    </body>\r\n");
      out.write("</html>\r\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
        else throw new ServletException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}
