<?php include "base.php"; ?>
<?php
    // Initialization > (Connection, ...)
    $connection = connectToMySQLDatabase();

    $country = $_POST["country"];
    $gender = $_POST["gender"][0];
    $name = $_POST["name"];
    $program = $_POST["program"];

    // Update > ...
    mysqli_query($connection, "UPDATE `" . DATABASE_TABLE_NAME . "` SET (`Country`, `First Name`, `Gender`, `Program`) VALUES ('" . $country . "', '" . $name . "', '" . $gender . "', '" . $program . "') WHERE `ID`=1");
    // echo "UPDATE `" . DATABASE_TABLE_NAME . "` SET (`Country`, `First Name`, `Gender`, `Program`) VALUES ('" . $country . "', '" . $name . "', '" . $gender . "', '" . $program . "') WHERE `ID`=1" . "<br/>";
    disconnectFromMySQLDatabase($connection);

    // ...
    header("Location: " . ROOT . "/pages/user.php?country=" . $country . "&gender=" . $gender . "&name=" . $name . "&program=" . $program);

    unset($country);
    unset($name);
    unset($gender);
    unset($program);
?>
