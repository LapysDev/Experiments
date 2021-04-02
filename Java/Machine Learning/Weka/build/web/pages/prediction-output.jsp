<!-- Metadata > ... -->
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<!-- Import > ... -->
<%@page import="java.io.BufferedReader"%>
<%@page import="java.io.BufferedWriter"%>
<%@page import="java.io.FileReader"%>
<%@page import="java.io.FileWriter"%>
<%@page import="java.util.Enumeration"%>
<%@page import="weka.classifiers.trees.J48"%>
<%@page import="weka.core.Instances"%>

<!-- ... -->
<%
    // Global > (Prediction, Root)
    String prediction = null;
    final String root = "C:/LapysDev/experiments/Java/Machine Learning/Weka/web/";

    // Initialization > (Board Computer, Central Lock, Color, Fuel Type, Metallic (Color, Rim), Powered Windows)
    String boardComputer = request.getParameter("Boardcomputer");
    String centralLock = request.getParameter("CentralLock");
    String color = request.getParameter("Color");
    String metallicColor = request.getParameter("MetColor");
    String metallicRim = request.getParameter("MetallicRim");
    String poweredWindows = request.getParameter("PoweredWindows");

    // Error Handling
    try {
        // Initialization > (Buffered, File) Writer
        final BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(root + "assets/prediction.arff"));
        final FileWriter fileWriter = new FileWriter(root + "assets/prediction.arff", true);

        // Update > ...
        boardComputer = null != boardComputer && boardComputer.equals("on") ? "TRUE" : "FALSE";
        centralLock = null != centralLock && centralLock.equals("on") ? "TRUE" : "FALSE";
        color = null == color ? "BLACK" : color;
        metallicColor = null != metallicColor && metallicColor.equals("on") ? "TRUE" : "FALSE";
        metallicRim = null != metallicRim && metallicRim.equals("on") ? "TRUE" : "FALSE";
        poweredWindows = null != poweredWindows && poweredWindows.equals("on") ? "TRUE" : "FALSE";

        // ...
        bufferedWriter.write(
            "@relation Project3DataPrediction" + '\n' +
            '\n' +
            "@attribute MetColor {TRUE,FALSE}" + '\n' +
            "@attribute Color {Beige,Blue,Silver,Black,White,Grey,Red,Green}" + '\n' +
            "@attribute BoardComputer {TRUE,FALSE}" + '\n' +
            "@attribute CentralLock {TRUE,FALSE}" + '\n' +
            "@attribute PoweredWindows {TRUE,FALSE}" + '\n' +
            "@attribute MetallicRim {TRUE,FALSE}" + '\n' +

            "@attribute FuelType {Diesel,Petrol,CNG}" + '\n' +
            '\n' +
            "@data"
        );

        fileWriter.write('\n');
        fileWriter.write(metallicColor); fileWriter.write(",");
        fileWriter.write(color); fileWriter.write(",");
        fileWriter.write(boardComputer); fileWriter.write(",");
        fileWriter.write(centralLock); fileWriter.write(",");
        fileWriter.write(poweredWindows); fileWriter.write(",");
        fileWriter.write(metallicRim); fileWriter.write(",");
        fileWriter.write('?');

        // Termination
        bufferedWriter.close();
        fileWriter.close();
    } catch (final Exception error) { out.write("<div class=error> " + error + " </div>"); }

    // Error Handling
    try {
        // Initialization > (Buffered Reader, Labeled, Test, Train, Tree)
        BufferedReader bufferedReader = null;
        Instances labeled = null, test = null, train = null;
        final J48 tree = new J48();

        // ... Update > ...
        bufferedReader = new BufferedReader(new FileReader(root + "assets/train.arff")); {
            train = new Instances(bufferedReader);
            train.setClassIndex(train.numAttributes() - 1);
        }

        bufferedReader = new BufferedReader(new FileReader(root + "assets/test.arff")); {
            test = new Instances(bufferedReader);
            test.setClassIndex(test.numAttributes() - 1);
        }

        labeled = new Instances(test);
        tree.buildClassifier(train);

        for (int iterator = 0; iterator != test.numInstances(); ++iterator) {
            labeled.instance(iterator).setClassValue(tree.classifyInstance(test.instance(iterator)));
            session.setAttribute("Name", labeled.lastInstance().toString().split(",")[6]);
        }

        // Update > Prediction
        prediction = (String) session.getAttribute("Name");

        // Termination
        bufferedReader.close();
    } catch (final Exception error) { out.write("<div class=error> " + error + " </div>"); }
%>

<!-- Document -->
<!DOCTYPE html>
<html charset=UTF-8 dir=ltr encoding=UTF-8 itemtype=http://schema.org/WebPage lang=en-US language=English prefix=og:http://ogp.me/ns>
    <head prefix=lapys:https://www.lapys.dev/>
        <!-- Document Metadata -->
        <meta charset="UTF-8"/>
        <meta content=chrome=1 http-equiv="X-UA-Compatible"/>

        <!-- Document Stylesheet -->
        <style media=all type=text/css>
            @font-face {
                font-family: "Open Sans";
                src: url(../fonts/open-sans.ttf)
            }

            * { user-select: none }
                :selected { background-color: transparent }

            body { display: table; margin: 0 }
            body, html, main { height: 100%; width: 100% }

            h1 {
                color: #333333;
                margin: 0;
                margin-top: 1%
            }
                h1 span {
                    background-color: #99FF99;
                    border: 1px solid #00CC00;
                    border-radius: 3px;
                    color: #003300;
                    display: inline-block;
                    padding: 0 10px
                }

                h1 span[state=error], .error {
                    background-color: #FF9999;
                    border: 1px solid #AA0000;
                    color: #330000
                }

            h2 {
                border-bottom: 1px solid #CCCCCC;
                margin: 1% auto;
                padding-bottom: 5px;
                transform: skewX(-5deg);
                width: 80%
            }

            input {
                background-color: #F9F9F9;
                border: 1px solid #CCCCCC;
                border-radius: 3px;
                color: #333333;
                cursor: inherit;
                font-size: 90%;
                text-align: center;
                text-indent: 5%;
                width: 30%
            }

            input[role=color][value=Beige] { background-color: beige; color: rgba(0, 0, 0, 0.5); opacity: 0.75 }
            input[role=color][value=Black] { background-color: black; color: rgba(255, 255, 255, 1); opacity: 0.75 }
            input[role=color][value=Blue] { background-color: blue; color: rgba(255, 255, 255, 1); opacity: 0.75 }
            input[role=color][value=Gray] { background-color: gray; color: rgba(0, 0, 0, 0.5); opacity: 0.75 }
            input[role=color][value=Green] { background-color: green; color: rgba(0, 0, 0, 0.5); opacity: 0.75 }
            input[role=color][value=Red] { background-color: red; color: rgba(255, 255, 255, 1); opacity: 0.75 }
            input[role=color][value=Silver] { background-color: gray; color: rgba(0, 0, 0, 0.5); opacity: 0.75 }
            input[role=color][value=White] { background-color: white; color: rgba(0, 0, 0, 0.5); opacity: 0.75 }

            label {
                display: inline-block;
                text-align: left;
                width: 200px
            }

            li {
                animation: fadeIn 300ms ease-in 300s;
                animation-fill-mode: forwards;
                font-size: 20px;
                margin: 5px auto;
                opacity: 0;
                padding: 0;
                position: relative;
                width: 75%
            }
            li + li { animation-delay: 450ms }
            li + li + li { animation-delay: 600ms }
            li + li + li + li { animation-delay: 750ms }
            li + li + li + li + li { animation-delay: 900ms }
            li + li + li + li + li + li { animation-delay: 1050ms }
                @keyframes fadeIn {
                    from { left: 10%; opacity: 0 }
                    to { left: 0; opacity: 1 }
                }

            main {
                background: #7F00FF;
                background: #7F00FF linear-gradient(135deg, #7F00FF, #0000FF, #7F00FF);
                color: #3F3F3F;
                display: table-cell;
                text-align: center;
                vertical-align: middle
            }

            section {
                background-color: #FAFAFA;
                border: 1px solid #CCCCCC;
                border-radius: 5px;
                box-sizing: border-box;
                font-family: "Open Sans";
                height: 75%;
                margin: auto;
                padding: 5px 15px;
                overflow-x: hidden;
                width: 90%
            }

            ul {
                list-style: none;
                margin: 0;
                padding: 0;
                width: 100%
            }

            .error {
                border-radius: 3px;
                display: block;
                margin: 0 auto;
                padding: 15px 10px;
                width: 200px
            }
        </style>

        <!-- Document Title -->
        <title> Predicting Car Fuel Type (Done) </title>
    </head>

    <body>
        <!-- Main -->
        <main>
            <section>
                <h1> &#9981; The <em>type of car fuel</em> used is <% out.write((null == prediction ? "<span state=error>" : "<span>") + prediction + "</span>"); %> </h1>
                <h2> based on these variables: </h2>
                <ul>
                    <li> <label> Board Computer </label> <% out.write("<input readonly value=\"" + (boardComputer.equals("TRUE") ? "Available" : "None") + "\"/>"); %> </li>
                    <li> <label> Central Lock </label> <% out.write("<input readonly value=\"" + (centralLock.equals("TRUE") ? "Available" : "None") + "\"/>"); %> </li>
                    <li> <label> Color </label> <% out.write("<input readonly role=color value=\"" + color.charAt(0) + color.substring(1, color.length()).toLowerCase() + "\"/>"); %> </li>
                    <li> <label> Metallic Color </label> <% out.write("<input readonly value=\"" + (metallicColor.equals("TRUE") ? "Available" : "None") + "\"/>"); %> </li>
                    <li> <label> Metallic Rim </label> <% out.write("<input readonly value=\"" + (metallicRim.equals("TRUE") ? "Available" : "None") + "\"/>"); %> </li>
                    <li> <label> Powered Windows </label> <% out.write("<input readonly value=\"" + (poweredWindows.equals("TRUE") ? "Available" : "None") + "\"/>"); %> </li>
                </ul>
            </section>
        </main>
    </body>
</html>
