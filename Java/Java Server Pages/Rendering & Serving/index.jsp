<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.util.Date"%>

<!DOCTYPE html>
<html>
    <head>
        <!-- Document Metadata -->
        <meta content="text/html; charset=UTF-8" http-equiv=Content-Type>

        <!-- Document Title -->
        <title> Java Server Pages </title>
    </head>

    <!-- Document Scriptlet -->
    <%
        // Initialization > Date
        Date date = new Date();

        // Function > Get Date
        private Date getDate() { return date; }
    %>

    <body>
        <p> Today&rsquo;s date is <%= getDate() %> </p>
    </body>
</html>
