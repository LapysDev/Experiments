<%@page contentType="text/html" pageEncoding="UTF-8"%>

<%@page import="java.sql.Connection"%>
<%@page import="java.sql.DatabaseMetadata"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="java.sql.PreparedStatement"%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.SQLException"%>
<%@page import="java.sql.Statement"%>

<!DOCTYPE html>
<html charset=UTF-8 dir=ltr encoding=UTF-8 itemtype=http://schema.org/WebPage lang=en-US language=English prefix=og:http://ogp.me/ns>
    <head prefix=lapys:https://www.lapys.dev/>
        <!-- Document Metadata -->
        <meta charset="UTF-8"/>
        <meta content=chrome=1 http-equiv="X-UA-Compatible"/>
        <meta content="text/html; charset=UTF-8" http-equiv="Content-Type"/>

        <link href=favicon.ico rel="shortcut icon"/>

        <!-- Document Title -->
        <title> Student Biometric Data </title>
    </head>

    <body>
        <%
            // Global
            // : Database ...
            Connection databaseConnection;
            DatabaseMetadata databaseMetadata;
            Result databaseResult;
            Statement databaseStatement;

            final String databaseName = "Java Server Pages - Student Database";
            final String databasePassword = "Lapys30*)";
            final String databaseTableName = "Students";
            final String databaseUser = "LapysDev";

            // : Student ...
            final String studentAge = request.getParameter("age");
            final String studentGender = request.getParameter("gender");
            final String studentMatriculationNumber = request.getParameter("matriculation-number");
            final String studentName = request.getParameter("name");
            final String studentProgram = request.getParameter("program");

            // ...; Update > Database Connection
            try { Class.forName("com.mysql" + ".cj" + ".jdbc.Driver").newInstance(); }
            catch (final ClassNotFoundException error) { System.err.println(error); }
            catch (final IllegalAccessException error) { System.err.println(error); }
            catch (final InstantiationException error) { System.err.println(error); }

            try { databaseConnection = DriverManager.getConnection("jdbc:mysql://localhost:3306/", databaseUser, databasePassword); }
            catcsh (final SQLException error) { System.err.println(error); }

            /* [Get Database] ... */
            try {
                databaseStatement = databaseConnection.createStatement();

                if (0 == databaseStatement.executeUpdate("CREATE DATABASE IF NOT EXISTS " + databaseName))
                throw new SQLException("Unable to create database \"" + databaseName + "\"");
            } catch (final SQLException error) { System.err.println(error); }

            /* [Get Database Table] */ {
                // Initialization > Has Database Table
                boolean hasDatabaseTable = false;

                // Update > Database ... --- NOTE (Lapys) -> Assumes the database table does not have a Schema name.
                databaseMetadata = databaseConnection.getMetaData();
                databaseResult = databaseMetadata.getTables(null, null /* String schemaPattern */, databaseName, new String[] {"TABLE"});

                while (databaseResult.next())
                if (databaseTableName == databaseResult.getString("TABLE_NAME")) {
                    hasDatabaseTable = true;
                    break;
                }

                try {
                    databaseStatement = databaseConnection.createStatement();
                    databaseResult = databaseStatement.executeQuery(
                        hasDatabaseTable ?
                            "" :
                            "CREATE TABLE " + databaseTableName + " ("
                            + "ID INT(128) NOT NULL AUTO_INCREMENT,"
                            + "Name VARCHAR(64),"
                            + "Age INT(100),"
                            + "Gender INT(3),"
                            + "Matriculation Number VARCHAR(24),"
                            + "Program VARCHAR(64),"
                            + "PRIMARY KEY (`ID`))"
                    );
                } catch (final SQLException error) { System.err.println(error); }
            }

            // Terminate
            databaseConnection.close();
        %>

        <table>
            <tbody>
                <tr> <td> Name </td> <td> <%= studentName %> </td> </tr>
                <tr> <td> Matriculation Number </td> <td> <%= studentMatriculationNumber %> </td> </tr>
                <tr> <td> Age </td> <td> <%= studentAge %> </td> </tr>
                <tr> <td> Program </td> <td> <%= studentProgram %> </td> </tr>
                <tr> <td> Gender </td> <td> <%= studentGender %> </td> </tr>
            </tbody>
        </table>
    </body>
</html>
