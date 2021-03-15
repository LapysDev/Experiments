<%@page contentType="text/html" pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html charset=UTF-8 dir=ltr encoding=UTF-8 itemtype=http://schema.org/WebPage lang=en-US language=English prefix=og:http://ogp.me/ns>
    <head prefix=lapys:https://www.lapys.dev/>
        <!-- Document Metadata -->
        <meta charset="UTF-8"/>
        <meta content=chrome=1 http-equiv="X-UA-Compatible"/>
        <meta content="text/html; charset=UTF-8" http-equiv="Content-Type"/>

        <link href=favicon.ico rel="shortcut icon"/>

        <!-- Document Stylesheet -->
        <style media=all type=text/css>
            /* DOM Elements > ... */
            * { box-sizing: content-box }
            body { margin: 0 }
            body, html { height: 100%; width: 100% }

            /* Features > Form */
            #form {
                border: 1px solid #CCCCCC;
                border-radius: 3px;
                color: #333333;
                font-family: "Open Sans", Roboto, sans-serif;
                font-size: 20px;
                margin-left: 10%;
                padding: 0 5%;
                position: relative;
                top: 15%;
                width: 70%
            }
                /* <fieldset> */
                #form fieldset {
                    background-color: #F0F0F0;
                    border: none;
                    border-radius: inherit;
                    font-size: 100%;
                    margin: 1% 0;
                    padding: 1% 5%;
                    width: 90%
                }
                    /* <div> */
                    #form fieldset div {
                        margin: 1% 0;
                        width: 100%
                    }
                        /* [All] */
                        #form fieldset div * {
                            display: inline-block;
                            font-size: inherit
                        }

                        /* <input> */
                        #form fieldset div input {
                            color: #666666;
                            padding: 0 1%
                        }

                        /* <label> */
                        #form fieldset div label {
                            width: 20%
                        }

                    /* <input> */
                    #form fieldset input[type=reset],
                    #form fieldset input[type=submit] {
                        border: none;
                        border-radius: 50px;
                        background-color: #6F006F;
                        color: #FFFFFF;
                        cursor: pointer;
                        font-size: 125%;
                        margin: 0 2.5%;
                        padding: 1% 2.5%
                    }

                /* <legend> */
                #form legend {
                    font-size: 200%;
                    margin: 2% 0
                }
        </style>

        <!-- Document Title -->
        <title> Student Biometric Data </title>
    </head>

    <body>
        <form action=student.jsp id=form method=POST name=student-information>
            <legend> Student Information Capture </legend>

            <fieldset>
                <div> <label for=name> Name </label> <input id=name name=name type="text"/> </div>
                <div> <label for=matriculationNumber> Matriculation Number </label> <input id=matriculationNumber name=matriculation-number type="text"/> </div>
                <div> <label for=age> Age </label> <input id=age max=100 min=15 name=age type=number value="20"/> </div>
                <div>
                    <label for=program> Program </label>
                    <select id=program name=program>
                        <option> Accounting </option>
                        <option> Architecture </option>
                        <option> Banking and Finance </option>
                        <option> Biochemistry </option>
                        <option> Biology </option>
                        <option> Building Technology </option>
                        <option> Business Administration </option>
                        <option> Chemical Engineering </option>
                        <option> Civil Engineering </option>
                        <option> Computer Engineering </option>
                        <option selected> Computing Science </option>
                        <option> Demography and Social Statistics </option>
                        <option> Economics </option>
                        <option> Electrical/ Electronics Engineering </option>
                        <option> English Language </option>
                        <option> Entrepreneurship </option>
                        <option> Estate Management </option>
                        <option> French </option>
                        <option> Industrial Chemistry </option>
                        <option> Industrial Mathematics </option>
                        <option> Industrial Physics with Applied Geo-Physics </option>
                        <option> Industrial Physics with Electronics and I.T. Application </option>
                        <option> Industrial Physics with Renewable Energy </option>
                        <option> Industrial Relations </option>
                        <option> Industrial Relations and Human Resources Management </option>
                        <option> Information and Communication Engineering </option>
                        <option> International Relations </option>
                        <option> Management Information System </option>
                        <option> Marketing </option>
                        <option> Mass Communication </option>
                        <option> Mechanical Engineering </option>
                        <option> Microbiology </option>
                        <option> Petroleum Engineering </option>
                        <option> Policy and Strategic Studies </option>
                        <option> Political Science </option>
                        <option> Psychology </option>
                        <option> Sociology </option>
                    </select>
                </div>
                <div>
                    <label for=gender> Gender </label>
                    <select id=gender name=gender>
                        <option> Male </option>
                        <option> Female </option>
                        <option selected> Unspecified </option>
                    </select>
                </div>
            </fieldset>

            <fieldset>
                <input name=clear type=reset value="Clear"/>
                <input name=submit type=submit value="Submit"/>
            </fieldset>
        </form>

        <script language=javascript type=text/javascript>
            // Constant > Form
            var form = document.getElementById("form");

            // Event > Form
            form.addEventListener("submit", function authenticate() {
            })
        </script>
    </body>
</html>
