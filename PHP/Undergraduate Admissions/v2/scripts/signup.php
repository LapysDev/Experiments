<!-- Document Script -->
<?php
    /* ... */
    include "../scripts/base.php"; {
        // Constant > (... Name, Country, Gender, Password, Program, Registration Number)
        $country = $_POST["signup__country"];
        $firstName = $_POST["signup__first_name"];
        $gender = $_POST["signup__gender"][0];
        $lastName = $_POST["signup__last_name"];
        $middleName = $_POST["signup__middle_name"];
        $password = $_POST["signup__password"];
        $program = $_POST["signup__program"];
        $registrationNumber = $_POST["signup__registration_number"];

        // Logic > Error
        echo "SELECT * FROM `" . $DATABASE_TABLE -> getName() . "` WHERE `Registration Number`='" . $registrationNumber . '\'';
        if (0 != $DATABASE -> query("SELECT * FROM `" . $DATABASE_TABLE -> getName() . "` WHERE `Registration Number`='" . $registrationNumber . '\'') -> num_rows)
        header("Location: " . $ROOT . "/pages/form.php?submission-error=\"Student with registration number '" . $registrationNumber . "' already exists\"");

        if (0 != $DATABASE -> query("SELECT * FROM `" . $DATABASE_TABLE -> getName() . "` WHERE `Country`='" . $country . "' AND `First Name` LIKE '" . $firstName . "' AND `Gender`='" . $gender . "' AND `Last Name` LIKE '" . $lastName . "' AND `Middle Name` LIKE '" . $middleName . "' AND `Program`='" . $program . '\'') -> num_rows)
        header("Location: " . $ROOT . "/pages/form.php?submission-error=\"Student already exists\"");

        // ...
        $DATABASE -> query("INSERT INTO `" . $DATABASE_TABLE -> getName() . "` (`Country`, `First Name`, `Gender`, `Last Name`, `Middle Name`, `Password`, `Program`, `Registration Number`) VALUES ('" . $country . "', '" . $firstName . "', '" . $gender . "', '" . $lastName . "', '" . $middleName . "', '" . $password . "', '" . $program . "', '" . $registrationNumber . "')");
        // header("Location: " . $ROOT . "/pages/profile.php");
    }
?>
