<?php include "base.php"; ?>
<?php
    // Initialization > (Connection, ...)
    $connection = connectToMySQLDatabase();

    // Update > ...
    mysqli_query($connection, "DELETE FROM `" . DATABASE_TABLE_NAME . "`;");
    disconnectFromMySQLDatabase($connection);

    // ...
    header("Location: " . ROOT . "/index.php");
?>
