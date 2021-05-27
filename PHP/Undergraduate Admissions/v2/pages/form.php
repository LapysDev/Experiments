<!-- Document Script -->
<?php include "../scripts/base.php"; ?>

<!-- Document -->
<html>
    <head>
        <!-- Document Stylesheet -->
        <link href="<?php echo $ROOT; ?>/stylesheets/form.css<?php echo "?v=" . rand(); ?>" media=all rel="stylesheet"/>

        <!-- Document Title -->
        <title> Covenant University Undergraduate Admission &bull; Registration </title>
    </head>

    <body>
        <!-- Main -->
        <main>
            <form action="<?php echo $ROOT; ?>/scripts/login.php" id=login method=POST>
                <legend> Login </legend>

                <!-- ... -->
                <fieldset>
                    <!-- Registration Number -->
                    <div>
                        <label> Registration Number </label>
                        <input max=99999999 maxlength=8 min=200000 name=login__registration_number placeholder="Registration Number" required type="number"/>
                    </div>

                    <!-- Password -->
                    <div>
                        <label> Password </label>
                        <input name=login__password placeholder=Password required type="password"/>
                    </div>
                </fieldset>

                <fieldset> <input type=submit value="Submit"/> </fieldset>
            </form>

            <form action="<?php echo $ROOT; ?>/scripts/signup.php" id=signup method=POST>
                <legend> Sign-Up </legend>

                <!-- ... -->
                <fieldset>
                    <!-- First Name -->
                    <div>
                        <label> First Name </label>
                        <input name=signup__first_name placeholder="First Name" required type="text"/>
                    </div>

                    <!-- Middle Name -->
                    <div>
                        <label> Middle Name </label>
                        <input name=signup__middle_name placeholder="Middle Name" type="text"/>
                    </div>

                    <!-- Last Name -->
                    <div>
                        <label> Last Name </label>
                        <input name=signup__last_name placeholder="Last Name" required type="text"/>
                    </div>

                    <!-- Gender -->
                    <div>
                        <label> Gender </label>
                        <select name=signup__gender>
                            <option value=M> Male </option>
                            <option value=F> Female </option>
                            <option selected value=O> Other </option>
                        </select>
                    </div>

                    <!-- Country -->
                    <div>
                        <label> Country </label>
                        <select name=signup__country>
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

                    <!-- Program -->
                    <div>
                        <label> Program </label>
                        <select name=signup__program required>
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

                    <!-- Registration Number -->
                    <div>
                        <label> Registration Number </label>
                        <input id=registrationField max=99999999 maxlength=8 min=200000 name=signup__registration_number placeholder="Registration Number" required type="number"/>
                    </div>

                    <!-- Password -->
                    <div>
                        <label> Password </label>
                        <input name=signup__password placeholder=Password required type="password"/>
                    </div>
                </fieldset>

                <fieldset> <input type=submit value="Submit"/> </fieldset>
            </form>
        </main>

        <!-- Document Script -->
        <script language=javascript src="<?php echo $ROOT; ?>/scripts/form.js<?php echo "?v=" . rand(); ?>" type=text/javascript> </script>
    </body>
</html>
