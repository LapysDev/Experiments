<?php include "base.php"; ?>
<?php
    // Initialization > (Connection, ...)
    $connection = connectToMySQLDatabase();

    $country = $_POST["signin__country"];
    $firstName = $_POST["signin__first_name"];
    $gender = $_POST["signin__gender"][0];
    $lastName = $_POST["signin__last_name"];
    $middleName = $_POST["signin__middle_name"];
    $program = $_POST["signin__program"];

    // Update > ...
    mysqli_query($connection, "INSERT INTO `" . DATABASE_TABLE_NAME . "` (`Country`, `First Name`, `Gender`, `Last Name`, `Middle Name`, `Program`) VALUES ('" . $country . "', '" . $firstName . "', '" . $gender . "', '" . $lastName . "', '" . $middleName . "', '" . $program . "')");
    disconnectFromMySQLDatabase($connection);

    // ...
    header("Location: " . ROOT . "/pages/user.php?country=" . $country . "&gender=" . $gender . "&name=" . $firstName . "&program=" . $program);

    unset($country);
    unset($firstName);
    unset($gender);
    unset($lastName);
    unset($middleName);
    unset($program);
?>
