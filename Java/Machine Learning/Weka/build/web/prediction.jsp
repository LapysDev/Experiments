<%-- 
    Document   : prediction
    Created on : Mar 24, 2021, 1:09:15 AM
    Author     : Nonso
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.io.BufferedReader" %>
<%@page import="java.io.BufferedWriter" %>
<%@page import="java.io.FileReader" %>
<%@page import="java.io.FileWriter" %>
<%@page import="java.util.Enumeration" %>
<%@page import="weka.classifiers.trees.J48" %>
<%@page import="weka.core.Instances" %>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Prediction</title>
    </head>
    
    <body>
        <%
            String root = "C:/DEV/Java/Weka/web/";
            
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(root + "assets/prediction.arff"));
                
                writer.write(
                    "@relation SalePrediction" + '\n' +
                    '\n' +
                    "@attribute SalesRecord {YES, NO}" + '\n' +
                    "@attribute MonthsSales {YES, NO}" + '\n' +
                    "@attribute Enterpeneur {YES, NO}" + '\n' +
                    "@attribute Marketing {YES, NO}" + '\n' +
                    "@attribute Packaging {YES, NO}" + '\n' +
                    "@attribute Prediction {MAKE-NO-SALES, MAKE-AVERAGE-SALES, MAKE-PLENTY-SALES}" + '\n' +
                    '\n' +
                    "@data"
                ); writer.close();
            } catch (Exception error) { out.write("<div style='color: red'> <b>[1]:</b> " + error + " </div>"); }
            
            try {
                FileWriter fileWriter = new FileWriter(root + "assets/prediction.arff", true);
                String SalesRecord = request.getParameter("SalesRecord").toString();
                String MonthsSales = request.getParameter("MonthsSales").toString();
                String Entrepreneur = request.getParameter("Entrepreneur").toString();
                String Marketing = request.getParameter("Marketing").toString();
                String Packaging = request.getParameter("Packaging").toString();
                String ToPredict = "?";
                
                fileWriter.write('\n');
                fileWriter.write(SalesRecord); fileWriter.write(",");
                fileWriter.write(MonthsSales); fileWriter.write(",");
                fileWriter.write(Entrepreneur); fileWriter.write(",");
                fileWriter.write(Marketing); fileWriter.write(",");
                fileWriter.write(Packaging); fileWriter.write(",");
                fileWriter.write(ToPredict);
                fileWriter.close();
            } catch (Exception error) { out.write("<div style='color: red'> <b>[2]:</b> " + error + " </div>"); }
            
            try {
                BufferedReader reader = null;
                Instances test = null;
                Instances train = null;
                J48 tree = new J48();
                Instances labeled = null;
                
                reader = new BufferedReader(new FileReader(root + "assets/train.arff"));
                train = new Instances(reader);
                train.setClassIndex(train.numAttributes() - 1);
                
                reader = new BufferedReader(new FileReader(root + "assets/prediction.arff"));
                test = new Instances(reader);
                test.setClassIndex(train.numAttributes() - 1);
                reader.close();
                
                tree.buildClassifier(train);
                
                labeled = new Instances(test);
                for (int iterator = 0; iterator < test.numInstances(); ++iterator) {                    
                    labeled.instance(iterator).setClassValue(tree.classifyInstance(test.instance(iterator)));
                    session.setAttribute("Name", labeled.lastInstance().toString().split(",")[5]);
                }
                
                out.write("<div> " + session.getAttribute("Name") + " </div>");
            } catch (Exception error) { out.write("<div style='color: red'> <b>[3]:</b> " + error + " </div>"); }
        %>
    </body>
</html>
