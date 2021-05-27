<!-- Document Script -->
<?php
    include "../scripts/base.php";

    ini_set("session.cookie_lifetime", '0');
    ini_set("session.name", "CovenantUniversityUndergraduateAdmissionUserSession");
    ini_set("session.use_cookies", '1');
    ini_set("session.use_strict_mode", '1');
    session_start();

    if (isset($_SESSION)) {
        $_SESSION["pizza"] = true;
        echo "<div> Session Name: \"" . session_name() . "\" </div>";
    }

    session_unset(); // remove all variables
    session_destroy(); // destroy
?>
