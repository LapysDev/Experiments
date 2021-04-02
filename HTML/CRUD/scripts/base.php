<!-- ... -->
<?php
    /* Global > ... */
    define("DATABASE_NAME", "PHP - Covenant University Undergraduates");
    define("DATABASE_TABLE_NAME", "Undergraduates");

    /* Function */
        // Connect To MySQL Database
        function connectToMySQLDatabase() {
            // Initialization > (Connection, ...)
            $connection = new mysqli("localhost" . ':' . 3306, "LapysDev", "Lapys30*)");

            $databaseTableFieldCount = 7;
            $databaseTableFields = array("Country", "First Name", "Gender", "ID", "Last Name", "Middle Name", "Program");
            $databaseTableKeys = array("", "", "", "PRIMARY KEY", "", "", "");
            $databaseTableMiscellanies = array("", "", "", "AUTO_INCREMENT", "", "", "");
            $databaseTableTypes = array("VARCHAR(32)", "VARCHAR(32)", "CHAR", "INT UNSIGNED", "VARCHAR(32)", "VARCHAR(32)", "VARCHAR(64)");

            $hasDatabaseTable = false;

            // Logic
            if (0x0 != $connection -> connect_errno) raiseMySQLException($connection -> connect_error);
            else {
                // ... --- NOTE (Lapys) -> Get the database.
                mysqli_query($connection, "CREATE DATABASE IF NOT EXISTS `" . DATABASE_NAME . '`');
                mysqli_select_db($connection, DATABASE_NAME);
                mysqli_query($connection, "USE `" . DATABASE_NAME . '`');

                // ... Update > Has Database Table
                foreach (mysqli_query($connection, "SHOW TABLES FROM `" . DATABASE_NAME . '`') -> fetch_all(MYSQLI_NUM) as $result)
                if (0 == strcasecmp(DATABASE_TABLE_NAME, $result[0])) { $hasDatabaseTable = true; break; }

                // Logic --- NOTE (Lapys) -> Ensure the table is as expected.
                if ($hasDatabaseTable) {
                    foreach (mysqli_query($connection, "DESCRIBE `" . DATABASE_TABLE_NAME . '`') -> fetch_all(MYSQLI_ASSOC) as $result) {
                        $hasDatabaseTableField = false;

                        for ($iterator = $databaseTableFieldCount - 1; $hasDatabaseTable && $iterator != -1; $iterator -= 1) {
                            if ($databaseTableFields[$iterator] == $result["Field"]) {
                                $hasDatabaseTableField = true;

                                if (0 != strcasecmp($databaseTableMiscellanies[$iterator], $result["Extra"])) $hasDatabaseTable = false;
                                switch ($result["Key"]) {
                                    case "MUL": $hasDatabaseTable = "MULTIPLE KEY" == $databaseTableKeys[$iterator]; break;
                                    case "PRI": $hasDatabaseTable = "PRIMARY KEY" == $databaseTableKeys[$iterator]; break;
                                    case "UNI": $databaseTableTypes = "UNIQUE KEY" == $databaseTableKeys[$iterator]; break;
                                }
                                if (0 != strcasecmp($databaseTableMiscellanies[$iterator], $result["Extra"])) $hasDatabaseTable = false;

                                break;
                            }

                            $databaseTableTypes[$iterator];
                        }

                        if (false == $hasDatabaseTableField) $hasDatabaseTable = false;
                        if (false == $hasDatabaseTable) break;
                    }

                    // Deletion
                    if (false == $hasDatabaseTable)
                    mysqli_query($connection, "DROP TABLE IF EXISTS `" . DATABASE_TABLE_NAME . '`');
                }

                // Logic --- NOTE (Lapys) -> Either the table does not exist or has an unexpected description.
                if (false == $hasDatabaseTable) {
                    $databaseTableSyntax = "";

                    for ($iterator = $databaseTableFieldCount - 1; $iterator != -1; $iterator -= 1) {
                        $databaseTableSyntax .= '`' . $databaseTableFields[$iterator] . '`';
                        $databaseTableSyntax .= ' ' . $databaseTableTypes[$iterator];
                        $databaseTableSyntax .= "" == $databaseTableMiscellanies[$iterator] ? "" : ' ' . $databaseTableMiscellanies[$iterator];
                        $databaseTableSyntax .= "" == $databaseTableKeys[$iterator] ? "" : ' ' . $databaseTableKeys[$iterator];
                        $databaseTableSyntax .= 0 == $iterator ? "" : ", ";
                    }

                    $databaseTableSyntax = "CREATE TABLE `" . DATABASE_TABLE_NAME . "` (" . $databaseTableSyntax . ')';
                    mysqli_query($connection, $databaseTableSyntax);
                }
            }

            // Return
            return $connection;
        }

        // : Disconnect From MySQL Database
        // : Raise MySQL Exception
        function disconnectFromMySQLDatabase($connection) { mysqli_close($connection);}
        function raiseMySQLException($message) {
            // Update > Message
            $message = "" != $message && false == is_null($message) ? ": " . $message : "";

            // ...; Terminate
            print("<div class=error> <strong>[SQLException]</strong>" . $message . " </div>");
            die("[SQLException]: " . $message . '\n');
        }
?>

<!-- Document Scripts -->
<script language=javascript type=text/javascript>
    /* NOTE (Lapys) */
    var ROOT = <?php
        // Global > URL
        $url = "";

        // Logic -> Get the current working directory.
        if (false == isset($_SERVER["REQUEST_URI"])) {
            // ... URL
            global $url;
            $url = str_replace('\\', '/', getcwd()) . '/';
        }

        else {
            // Definition > URL
            global $url;

            // Initialization > (File Name, Server ...)
            $filename = str_replace('\\', '/', $_SERVER["REQUEST_URI"] /* __FILE__ */);
            $server = (function($indices) {
                foreach ($indices as $index) {
                    if (isset($_SERVER[$index]))
                    return $_SERVER[$index];
                } return "";
            })(array("SERVER_ADDR", "SERVER_NAME"));

            // Update
            // : File Name
            if (false !== strpos($filename, '/')) $filename = trim(substr($filename, strrpos($filename, '/') + 1));
            if (false !== strpos($filename, '?')) $filename = trim(substr($filename, 0, strrpos($filename, '?')));

            // : Server ...
            if (isset($_SERVER["SERVER_PORT"]))
            $server = "" != $server ? $server . ':' . $_SERVER["SERVER_PORT"] : "";

            // : URL
            $url = str_replace('\\', '/', $_SERVER["REQUEST_URI"]);
            if (false !== strpos($url, '?')) $url = trim(substr($url, 0, strrpos($url, '?')));
            if ("" !== $filename && strpos($url, $filename) == strlen($url) - strlen($filename)) $url = trim(substr($url, 0, strrpos($url, $filename)));

            $url = $server . '/' . substr($url, (int) ('/' == $url[0]));
            $url = (function($protocols) {
                $serverProtocol = isset($_SERVER["SERVER_PROTOCOL"]) ? $_SERVER["SERVER_PROTOCOL"] : "HTTP";

                foreach ($protocols as $protocol) {
                    if (false !== stripos($serverProtocol, $protocol))
                    return strtolower($protocol) . "://";
                }

                return "";
            })(array(
                "EXPECT", // -> Interaction streams
                "DATA", // -> Data (RFC 2397)
                "FILE", // -> Local filesystem
                "FTP", // -> Files transfers
                "GLOB", // -> Pathname matching patterns
                "HTTP", "HTTPS", // -> Hypertext transfers
                "OGG", // -> Audio streams
                "PHAR", // -> PHP archives
                "PHP", // -> I/O streams
                "RAR", // -> Roshal archives
                "SSH2", // -> Secure shell system
                "ZLIB" // -> Compression streams
            )) . $url;
        }

        // Logic -> Re-route the varying directories back to the root.
        if (strrpos($url, "pages/") == strlen($url) - strlen("pages/")) $url = substr($url, 0, strrpos($url, "pages/"));
        if (strrpos($url, "scripts/") == strlen($url) - strlen("scripts/")) $url = substr($url, 0, strrpos($url, "scripts/"));
        if (strrpos($url, "stylesheets/") == strlen($url) - strlen("stylesheets/")) $url = substr($url, 0, strrpos($url, "stylesheets/"));

        if ('/' == $url[strlen($url) - 1]) $url = substr($url, 0, -1);

        // Definition, Deletion
        define("ROOT", $url);
        unset($url);

        // ...
        echo '"' . str_replace('"', "\\\"", ROOT) . '"';
    ?>;
</script>

<script language=javascript src="<?php echo ROOT; ?>/scripts/base.js<?php echo "?v=" . rand(); ?>" type=text/javascript> </script>

<!-- Document Stylesheet -->
<link href="<?php echo ROOT; ?>/stylesheets/base.css<?php echo "?v=" . rand(); ?>" media=all rel="stylesheet"/>

<!-- Document Favorite Icon -->
<link href="<?php echo ROOT; ?>/favicon.ico" rel="shortcut icon"/>

<!-- Document Metadata -->
<meta charset="UTF-8"/>
<meta content="height=device-height, initial-scale=1.0, maximum-scale=1.0, minimal-ui, minimum-scale=1.0, user-scalable=no, width=device-width" name="viewport"/>
<meta content="text/html; charset=UTF-8" http-equiv="Content-Type"/>
