<%@page import="java.io.BufferedReader"%>
<%@page import="java.io.BufferedWriter"%>
<%@page import="java.io.FileReader"%>
<%@page import="java.io.FileWriter"%>
<%@page import="java.util.Enumeration"%>
<%@page import="weka.classifiers.trees.J48"%>
<%@page import="weka.core.Instances"%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<%
    try {
        Object selectedItem1 = request.getParameter("SalesRecord");
        String SalesRecord = selectedItem1.toString();
        
        Object selectedItem2 = request.getParameter("MonthsSales");
        String MonthsSales = selectedItem2.toString();
        
        Object selectedItem3 = request.getParameter("Entrepreneur");
        String Entrepreneur = selectedItem3.toString();
        
        Object selectedItem4 = request.getParameter("Marketing");
        String Marketing = selectedItem4.toString();
        
        Object selectedItem5 = request.getParameter("Packaging");
        String Packaging = selectedItem5.toString();
        
        String ToPredict = "?";
        
        BufferedWriter writer = new BufferedWriter(new FileWriter("assets/prediction.arff"));
        writer.write(
            "@relation SalePrediction\n" +
            "\n" +
            "@attribute SalesRecord {YES, NO}\n" +
            "@attribute MonthsSales {YES, NO}\n" +
            "@attribute Entrepreneur {YES, NO}\n" +
            "@attribute Marketing {YES, NO}\n" +
            "@attribute Packaging {YES, NO}\n" +
            "@attribute Prediction {MAKE-NO-SALES, MAKE-AVERAGE-SALES, MAKE-PLENTY-SALES}\n" +
            "\n" +
            "@data"
        );
        writer.close();
        
        String filename = "assets/prediction.arff";
        FileWriter fw = new FileWriter(filename, rue);
        
        fw.write("\n");
        fw.write(SalesRecord);
        fw.write(",");
        fw.write(MonthsSales);
        fw.write(",");
        fw.write(Entrepreneur);
        fw.write(",");
        fw.write(Marketing);
        fw.write(",");
        fw.write(Packaging);
        fw.write(",");
        fw.write(ToPredict);
        fw.write(",");
        
        fw.close();
        
        BufferedReader breader = null;
        breader = new BufferedReader(new FileReader("assets/train.arff"));
        Instances train = new Instances(breader);
        train.setClassIndex(train.numAttributes() - 1);
        
        breader = new BufferedReader(new FileReader("assets/prediction.arff"));
        Instances test = new Instances(breader);
        test.setClassIndex(train.numAttributes() - 1);
        
        breader.close();
        
        J48 tree = new J48();
        tree.buildClassifier(train);
        Instances labeled = new Instances(test);
        
        for (int i = 0; i < test.numInstances(); i++) {
            double clsLabel = tree.classifyInstance(test.instance(i));
            
            labeled.instance(i).setClassValue(clsLabel);
            
            String output = labeled.lastInstance().toString();
            String[] arr = output.split(",");
            String result = arr[5];
            
            session.setAttribute("Name", result);
        }
    } catch (Exception error) {}
%>