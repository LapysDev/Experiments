<!DOCTYPE html>
<html>
    <head>
        <!-- Document Script -->
        <?php include "../scripts/base.php"; ?>

        <!-- Document Title -->
        <title> Covenant University Undergraduate Online Application | My Account </title>
    </head>

    <body>
        <?php
            // Initialization > (Connection, ..., Results, ...)
            $connection = connectToMySQLDatabase();

            $country = $_GET["country"];
            $gender = $_GET["gender"];
            $name = $_GET["name"];
            $program = $_GET["program"];

            $results = false;
            $userFound = false;

            // ... Update > Results
            (function($nameFields) {
                global $connection;
                global $country;
                global $gender;
                global $name;
                global $program;
                global $results;
                global $userFound;

                foreach ($nameFields as $nameField)
                if (false == $userFound) {
                    $results = mysqli_query($connection, "SELECT * FROM `" . DATABASE_TABLE_NAME . "` WHERE `Country`='" . $country . "' AND `Gender`='" . $gender . "' AND `" . $nameField . "`='" . $name . "' AND `Program`='" . $program . "'");
                    if (false !== $results) if (0 != $results -> num_rows) $userFound = true;
                }
            })(array("First Name", "Middle Name", "Last Name"));

            foreach ($results as $result) {
                $country = $result["Country"];
                $name = $result["First Name"] . ' ' . $result["Middle Name"] . ' ' . $result["Last Name"];
                $program = $result["Program"];

                switch ($result["Gender"]) {
                    case 'F': $gender = "&#9792;"; break;
                    case 'M': $gender = "&#2642;"; break;
                    case 'O': $gender = "&#2642;"; break;
                }
            }
        ?>

        <h1> Welcome, <?php echo $name . ' ' . $gender; ?> (<?php echo $country; ?>) </h1>
        <h2> Studying <?php echo $program; ?> </h2>

        <small> Thank you for registering with us </small>

        <form action=../scripts/delete-user.php method=POST>
            <input type=submit value="Delete Account"/>
        </form>

        <form action=../pages/update.php method=POST>
            <input type=submit value="Update Account"/>
        </form>

        <?php
            disconnectFromMySQLDatabase($connection);

            unset($connection, $country, $gender, $name, $program);
            unset($results, $userFound);
        ?>

        <!-- USER PAGE -->
        <!--   Display information -->
        <!--   Modify information -->
    </body>
</html>
