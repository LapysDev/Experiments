<!DOCTYPE html>
<html>
    <head>
        <!-- Document Script -->
        <?php include "../scripts/base.php"; ?>

        <!-- Document Stylesheet -->
        <style media=all type=text/css>
            body { display: table }
            main {
                display: table-cell;
                vertical-align: middle
            }

            [role=header] {
                height: 40px;
                margin: 0 auto;
                margin-bottom: 2.5%;
                overflow: hidden;
                text-align: center;
                text-overflow: ellipsis;
                width: 90%;
                word-break: keep-all
            }

            [role=layout] {
                display: table;
                height: 75%;
                margin: 0 auto;
                margin-top: 2.5%;
                overflow: hidden;
                width: 75%
            }

            #form, #tab { border-radius: 5px }

            #form {
                border: 1px solid #CCCCCC;
                border-top: none;
                border-top-left-radius: 0;
                border-top-right-radius: 0;
                box-shadow: 0 0 3px 0 rgba(0, 0, 0, 0.1);
                box-sizing: border-box;
                height: 80%;
                width: 100%
            }

            #form div {
                display: inline-block;
                font-size: 20px;
                margin: 0 auto;
                margin-top: 30px;
                width: 65%
            }

            #form div[role=toggle] {
                background-color: #F0F0F0;
                border-radius: 30px;
                box-shadow: inset 0 0 5px 0 rgba(0, 0, 0, 0.1);
                cursor: pointer;
                display: inline-block;
                float: right;
                height: 25px;
                margin: 0;
                overflow: hidden;
                text-align: left;
                transition: background-color 100ms ease-in 0s;
                width: 50px
            }

            #form div[role=toggle][state=on] {
                background-color: #9F99FF;
                transition: background-color 200ms ease-in 0s
            }
                #form div[role=toggle] div {
                    background-color: #9F00FF;
                    border-radius: inherit;
                    box-shadow: 0 0 10px 0 rgba(0, 0, 0, 0.5);
                    clear: both;
                    height: inherit;
                    left: 0;
                    margin: 0;
                    position: relative;
                    transition: left 150ms ease-in 0s;
                    width: 25px
                }

                #form div[role=toggle][state=on] div { left: 50% }

            #form div[state=tabbed] { width: 25% }

            #form fieldset {
                border: none;
                display: table-cell;
                margin: auto;
                padding: 0;
                width: 100%
            }

            #form fieldset[role=input] {
                height: 77.5%;
                text-align: center
            }

            #form fieldset[role=output] { text-align: right }

            #form form {
                display: table;
                font-size: 18px;
                height: 100%;
                margin: auto;
                width: 100%
            }

            [state=login] #form form[role=signin],
            [state=signin] #form form[role=login] {
                display: none;
                opacity: 0;
                z-index: -1
            }

            [state=login] #form form[role=signin] *,
            [state=signin] #form form[role=login] * {
                pointer-events: none;
                touch-action: none;
                user-drag: none;
                user-select: none
            }

            #form input,
            #form select {
                color: #666666;
                font-size: inherit;
                margin: auto;
                padding: 3px 2.5%;
                transition: border-color 300ms ease-in 0s;
                width: 65%
            }

            #form [state=tabbed] input { width: 100% }

            #form input[type=submit] {
                background-color: #9F00FF;
                color: #FFFFFF;
                border: none;
                border-radius: 3px;
                box-shadow: 0 2px 2px 0 rgba(0, 0, 0, 0.3);
                font-size: 20px;
                margin: 0 5%;
                padding: 10px 5%;
                width: auto
            }

            #form label {
                color: #999999;
                cursor: text;
                font-size: 95%;
                line-height: 1.75;
                margin-left: 1%;
                position: absolute;
                text-align: left;
                transition: 150ms ease-in 0s;
                transition-property: font-size, margin-left, margin-top, opacity
            }

            #form label[state=label] {
                font-size: 75%;
                line-height: 0;
                margin-top: -1%;
                vertical-align: top
            }

            #form label[state=placeholder] {
                opacity: 0.8;
                pointer-events: none
            }
                #form label[state=placeholder]:hover { opacity: 0.5 }

            #form,
            [state=login] #tab button[role=login],
            [state=signin] #tab button[role=signin] { background-color: #FCFCFC }

            #tab {
                border-bottom: none;
                border-bottom-left-radius: 0;
                border-bottom-right-radius: 0;
                display: table;
                height: 20%;
                width: 100%
            }

            #tab button {
                border: none;
                border-radius: inherit;
                box-sizing: border-box;
                color: #666666;
                display: table-cell;
                font-size: 20px;
                font-weight: bold;
                padding: 0;
                height: 90%;
                text-transform: uppercase;
                transition: all 100ms ease-in 0s, height 200ms linear 0s;
                vertical-align: bottom;
                width: 50%
            }

            #tab [role=login] {
                border-top-right-radius: 0;
                box-shadow: 0 -3px 3px 0 rgba(0, 0, 0, 0.05);
                margin-right: auto
            }

            #tab [role=signin] {
                border-top-left-radius: 0;
                box-shadow: 0 -3px 3px 0 rgba(0, 0, 0, 0.05);
                margin-left: auto
            }

            [state=login] #tab button[role=login],
            [state=signin] #tab button[role=signin] {
                border: 1px solid #CCCCCC;
                border-bottom: none;
                height: 100%;
                z-index: 2
            }

            [state=signin] #tab button[role=login],
            [state=login] #tab button[role=signin] {
                background-color: #9F00FF;
                color: #FFFFFF;
                filter: brightness(0.8);
                z-index: 1
            }
                [state=signin] #tab button[role=login]:hover,
                [state=login] #tab button[role=signin]:hover { filter: brightness(1) }
        </style>

        <!-- Document Title -->
        <title> Covenant University Undergraduate Online Application | Registration </title>
    </head>

    <body>
        <!-- Main -->
        <main state=<?php echo $_GET["state"]; ?>>
            <h1 class=no-select role=header> Covenant University Undergraduate Online Application Registration Form </h1>
            <section role=layout>
                <div id=tab>
                    <button class=no-select role=login onclick="toggle('login')" type=button> Login </button>
                    <button class=no-select role=signin onclick="toggle('signin')" type=button> Sign-In </button>
                </div>

                <div id=form>
                    <form action="../scripts/create-user.php" id=signin method=POST role=signin>
                        <fieldset role=input>
                            <div state=tabbed> <label class=no-select> First Name </label> <input maxlength=32 name=signin__first_name type="text"/> </div>
                            <div state=tabbed> <label class=no-select> Middle Name </label> <input maxlength=32 name=signin__middle_name type="text"/> </div>
                            <div state=tabbed> <label class=no-select> Last Name </label> <input maxlength=32 name=signin__last_name type="text"/> </div>

                            <div>
                                <label class=no-select> Gender </label>
                                <select name=signin__gender>
                                    <option> Male </option>
                                    <option> Female </option>
                                    <option selected> Other </option>
                                </select>
                            </div>

                            <div>
                                <label class=no-select> Nationality </label>
                                <select name=signin__country>
                                    <option> Afghanistan </option>
                                    <option> Albania </option>
                                    <option> Algeria </option>
                                    <option> Andorra </option>
                                    <option> Angola </option>
                                    <option> Antigua and Barbuda </option>
                                    <option> Argentina </option>
                                    <option> Armenia </option>
                                    <option> Australia </option>
                                    <option> Austria </option>
                                    <option> Azerbaijan </option>
                                    <option> Bahamas </option>
                                    <option> Bahrain </option>
                                    <option> Bangladesh </option>
                                    <option> Barbados </option>
                                    <option> Belarus </option>
                                    <option> Belgium </option>
                                    <option> Belize </option>
                                    <option> Benin </option>
                                    <option> Bhutan </option>
                                    <option> Bolivia </option>
                                    <option> Bosnia and Herzegovina </option>
                                    <option> Botswana </option>
                                    <option> Brazil </option>
                                    <option> Brunei </option>
                                    <option> Bulgaria </option>
                                    <option> Burkina Faso </option>
                                    <option> Burundi </option>
                                    <option> Côte d'Ivoire </option>
                                    <option> Cabo Verde </option>
                                    <option> Cambodia </option>
                                    <option> Cameroon </option>
                                    <option> Canada </option>
                                    <option> Central African Republic </option>
                                    <option> Chad </option>
                                    <option> Chile </option>
                                    <option> China </option>
                                    <option> Colombia </option>
                                    <option> Comoros </option>
                                    <option> Congo </option>
                                    <option> Costa Rica </option>
                                    <option> Croatia </option>
                                    <option> Cuba </option>
                                    <option> Cyprus </option>
                                    <option> Czechia (Czech Republic) </option>
                                    <option> Democratic Republic of the Congo </option>
                                    <option> Denmark </option>
                                    <option> Djibouti </option>
                                    <option> Dominica </option>
                                    <option> Dominican Republic </option>
                                    <option> Ecuador </option>
                                    <option> Egypt </option>
                                    <option> El Salvador </option>
                                    <option> Equatorial Guinea </option>
                                    <option> Eritrea </option>
                                    <option> Estonia </option>
                                    <option> Eswatini </option>
                                    <option> Ethiopia </option>
                                    <option> Fiji </option>
                                    <option> Finland </option>
                                    <option> France </option>
                                    <option> Gabon </option>
                                    <option> Gambia </option>
                                    <option> Georgia </option>
                                    <option> Germany </option>
                                    <option> Ghana </option>
                                    <option> Greece </option>
                                    <option> Grenada </option>
                                    <option> Guatemala </option>
                                    <option> Guinea </option>
                                    <option> Guinea-Bissau </option>
                                    <option> Guyana </option>
                                    <option> Haiti </option>
                                    <option> Holy See </option>
                                    <option> Honduras </option>
                                    <option> Hungary </option>
                                    <option> Iceland </option>
                                    <option> India </option>
                                    <option> Indonesia </option>
                                    <option> Iran </option>
                                    <option> Iraq </option>
                                    <option> Ireland </option>
                                    <option> Israel </option>
                                    <option> Italy </option>
                                    <option> Jamaica </option>
                                    <option> Japan </option>
                                    <option> Jordan </option>
                                    <option> Kazakhstan </option>
                                    <option> Kenya </option>
                                    <option> Kiribati </option>
                                    <option> Kuwait </option>
                                    <option> Kyrgyzstan </option>
                                    <option> Laos </option>
                                    <option> Latvia </option>
                                    <option> Lebanon </option>
                                    <option> Lesotho </option>
                                    <option> Liberia </option>
                                    <option> Libya </option>
                                    <option> Liechtenstein </option>
                                    <option> Lithuania </option>
                                    <option> Luxembourg </option>
                                    <option> Madagascar </option>
                                    <option> Malawi </option>
                                    <option> Malaysia </option>
                                    <option> Maldives </option>
                                    <option> Mali </option>
                                    <option> Malta </option>
                                    <option> Marshall Islands </option>
                                    <option> Mauritania </option>
                                    <option> Mauritius </option>
                                    <option> Mexico </option>
                                    <option> Micronesia </option>
                                    <option> Moldova </option>
                                    <option> Monaco </option>
                                    <option> Mongolia </option>
                                    <option> Montenegro </option>
                                    <option> Morocco </option>
                                    <option> Mozambique </option>
                                    <option> Myanmar </option>
                                    <option> Namibia </option>
                                    <option> Nauru </option>
                                    <option> Nepal </option>
                                    <option> Netherlands </option>
                                    <option> New Zealand </option>
                                    <option> Nicaragua </option>
                                    <option> Niger </option>
                                    <option selected> Nigeria </option>
                                    <option> North Korea </option>
                                    <option> North Macedonia </option>
                                    <option> Norway </option>
                                    <option> Oman </option>
                                    <option> Pakistan </option>
                                    <option> Palau </option>
                                    <option> Palestine State </option>
                                    <option> Panama </option>
                                    <option> Papua New Guinea </option>
                                    <option> Paraguay </option>
                                    <option> Peru </option>
                                    <option> Philippines </option>
                                    <option> Poland </option>
                                    <option> Portugal </option>
                                    <option> Qatar </option>
                                    <option> Romania </option>
                                    <option> Russia </option>
                                    <option> Rwanda </option>
                                    <option> Saint Kitts and Nevis </option>
                                    <option> Saint Lucia </option>
                                    <option> Saint Vincent and the Grenadines </option>
                                    <option> Samoa </option>
                                    <option> San Marino </option>
                                    <option> Sao Tome and Principe </option>
                                    <option> Saudi Arabia </option>
                                    <option> Senegal </option>
                                    <option> Serbia </option>
                                    <option> Seychelles </option>
                                    <option> Sierra Leone </option>
                                    <option> Singapore </option>
                                    <option> Slovakia </option>
                                    <option> Slovenia </option>
                                    <option> Solomon Islands </option>
                                    <option> Somalia </option>
                                    <option> South Africa </option>
                                    <option> South Korea </option>
                                    <option> South Sudan </option>
                                    <option> Spain </option>
                                    <option> Sri Lanka </option>
                                    <option> Sudan </option>
                                    <option> Suriname </option>
                                    <option> Sweden </option>
                                    <option> Switzerland </option>
                                    <option> Syria </option>
                                    <option> Tajikistan </option>
                                    <option> Tanzania </option>
                                    <option> Thailand </option>
                                    <option> Timor-Leste </option>
                                    <option> Togo </option>
                                    <option> Tonga </option>
                                    <option> Trinidad and Tobago </option>
                                    <option> Tunisia </option>
                                    <option> Turkey </option>
                                    <option> Turkmenistan </option>
                                    <option> Tuvalu </option>
                                    <option> Uganda </option>
                                    <option> Ukraine </option>
                                    <option> United Arab Emirates </option>
                                    <option> United Kingdom </option>
                                    <option> United States of America </option>
                                    <option> Uruguay </option>
                                    <option> Uzbekistan </option>
                                    <option> Vanuatu </option>
                                    <option> Venezuela </option>
                                    <option> Vietnam </option>
                                    <option> Yemen </option>
                                    <option> Zambia </option>
                                    <option> Zimbabwe </option>
                                </select>
                            </div>

                            <div> <label class=no-select> Number </label> <input min=0 name=signin__number type="number"/> </div>
                            <div>
                                <label class=no-select> Program </label>
                                <select name=signin__program>
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
                        </fieldset>

                        <fieldset role=output> <div> <input type=submit value="Sign-In"/> </div> </fieldset>
                    </form>

                    <form action=# id=login method=POST role=login>
                        <fieldset role=input>
                            <div>
                                <label class=no-select> Name </label>
                                <input maxlength=32 name=login__name type="text"/>
                            </div>

                            <div>
                                <label class=no-select> Program </label>
                                <select name=login__program>
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
                        </fieldset>

                        <fieldset role=output> <div> <input type=submit value="Login"/> </div> </fieldset>
                    </form>
                </div>
            </section>
        </main>

        <!-- Document Script -->
        <script language=javascript type=text/javascript>
            function toggle(state) { document.getElementsByTagName("main").item(0).setAttribute("state", state) }

            void function() {
                var inputs = document.getElementsByTagName("input");
                var labels = document.getElementsByTagName("label");
                var selects = document.getElementsByTagName("select");

                function activateLabel(label) { label.setAttribute("state", "placeholder") }
                function deactivateLabel(label) { label.setAttribute("state", "label") }
                function enstateLabel(label, state) { null === state ? label.removeAttribute("state") : label.setAttribute("state", state) }
                function getAssociatedLabel(field) {
                    var labels = document.getElementsByTagName("label");

                    if (null !== field)
                    for (var subiterator = labels.length - 1; ~subiterator; --subiterator) {
                        var label = labels.item(subiterator);

                        if (field.parentNode === label.parentNode)
                        return label
                    }

                    return null
                }

                for (var iterator = labels.length - 1; ~iterator; --iterator) {
                    var label = labels.item(iterator);
                    if (null !== label) activateLabel(getAssociatedLabel(label))
                }

                for (var iterator = inputs.length - 1; ~iterator; --iterator) {
                    var input = inputs.item(iterator);

                    if (null !== input) {
                        var label = getAssociatedLabel(input);

                        if (input.value && null !== label)
                        deactivateLabel(label);

                        if (
                            "number" == input.getAttribute("type") ||
                            "text" == input.getAttribute("type")
                        ) void function(input, label) {
                            input.onblur = function() {
                                var value = String(input.value);

                                for (var trimming = true; trimming; ) switch (value.charAt(0)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\0': value = value.slice(1); break; default: trimming = false }
                                for (var trimming = true; trimming; ) switch (value.charAt(value.length - 1)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\0': value = value.slice(-1); break; default: trimming = false }

                                input.value = value;
                                if ("" == value) activateLabel(label);
                            };

                            input.onchange = input.oninput = function() {
                                deactivateLabel(label);

                                if ("number" == input.getAttribute("type"))
                                if (input.value.length > 12) input.value = input.value.slice(0, 12)
                            };
                            input.onclick = function() { deactivateLabel(label) };
                            input.ondblclick = function() { deactivateLabel(label) };
                            input.onfocus = function() { deactivateLabel(label) };

                            label.onclick = function() { input.focus() }
                        }(input, label)
                    }
                }

                for (var iterator = selects.length - 1; ~iterator; --iterator) {
                    var select = selects.item(iterator);

                    if (null !== select) {
                        var label = getAssociatedLabel(select);

                        void function(select, label) {
                            label.onclick = function() { select.focus() };
                            deactivateLabel(label)
                        }(select, label)
                    }
                }
            }();
        </script>
    </body>
</html>
