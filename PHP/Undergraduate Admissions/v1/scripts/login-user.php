<?php include "base.php"; ?>
<?php
    // Initialization > (Connection, ...)
    $connection = connectToMySQLDatabase();

    $firstName = $_POST["login__name"];
    $program = $_POST["login__program"];

    $gender = mysqli_query($connection, "SELECT * FROM `" . DATABASE_TABLE_NAME . "` WHERE `Program`='" . $program . "'");
    $country = mysqli_query($connection, "SELECT * FROM `" . DATABASE_TABLE_NAME . "` WHERE `Program`='" . $program . "'");

    // ...
    disconnectFromMySQLDatabase($connection);

    // ...
    if (false === $country) $country = "Male";
    else $country = $country -> fetch_all(MYSQLI_ASSOC)["Country"][0];

    if (0 == strcmp("", $country)) $country = "Nigeria";

    // ...
    if (false === $gender) $gender = "Male";
    else $gender = $gender -> fetch_all(MYSQLI_ASSOC)["Gender"][0];

    if (0 == strcmp("", $gender)) $gender = "Male";

    // ...
    header("Location: " . ROOT . "/pages/user.php?country=" . $country . "&gender=" . $gender . "&name=" . $firstName . "&program=" . $program);

    unset($country);
    unset($firstName);
    unset($gender);
    unset($program);
?>
