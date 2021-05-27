<!-- ... -->
<?php
    /* Class > Database --- REDACT (Lapys) */
    class Database {
        // Constant > ...
        private const ANALYZE_ALL = 0x1;
        private const ANALYZE_TABLES = 0x2;
        private const EXECUTE_QUERY = 0x4;
        private const SILENCE_ERRORS = 0x8;

        // Definition > (Connection, Name, Tables)
        private $connection = NULL;
        private $name = NULL;
        private $tables = [];

        // [Constructor]
        public function __construct($name, $options = NULL) {
            // Modification > Target > Name; ...
            $this -> name = "" . $name;
            if (false == is_null($options)) $this -> openConnection($options -> path, $options -> username, $options -> password);
        }

        // Method
            // Analyze Tables --- NOTE (Lapys) -> Acquire live record of tables within the `Database`.
            protected function analyzeTables($flags = 0x0) {
                // Logic
                if ($this -> assertConnection(DatabaseException::UNOPEN_QUERY, $flags)) {
                    // Reset > Target > Tables; Loop
                    $this -> tables = [];
                    foreach ($this -> query("SHOW TABLES FROM `" . $this -> getName() . '`', $flags | Database::EXECUTE_QUERY) as $result) {
                        // Constant > Table Name
                        // Initialization > Table (Column Count, Field Names, Keys, Miscellanies, Types)
                        $tableName = $result[0];

                        $tableColumnCount = 0;
                        $tableFieldNames = [];
                        $tableKeys = [];
                        $tableMiscellanies = [];
                        $tableTypes = [];

                        // Loop
                        foreach ($this -> query("DESCRIBE `" . $tableName . '`', $flags | Database::EXECUTE_QUERY | Database::SILENCE_ERRORS) as $subresult) {
                            // Update > Table (Column Count, ...)
                            ++$tableColumnCount;

                            array_push($tableFieldNames, $subresult["Field"]);
                            array_push($tableMiscellanies, strtoupper($subresult["Extra"]));
                            array_push($tableTypes, $subresult["Type"]);

                            switch ($subresult["Key"]) {
                                case "PRI": array_push($tableKeys, "PRIMARY KEY"); break;
                                case "MUL": array_push($tableKeys, "MULTIPLE KEY"); break;
                                case "UNI": array_push($tableKeys, "UNIQUE KEY"); break;
                                default: array_push($tableKeys, "");
                            }
                        }

                        // Update > (Target > Tables)
                        array_push($this -> tables, new DatabaseTable($this, $tableName, $tableColumnCount, $tableFieldNames, $tableTypes, $tableKeys, $tableMiscellanies));
                    }
                }
            }

            // Assert Connection
            protected function assertConnection($error, $flags = 0x0) {
                // Logic > ...
                if ($this -> hasConnection()) return true;
                else if ($flags & Database::SILENCE_ERRORS) return false;
                else throw new DatabaseException($error);
            }

            // Close Connection
            public function closeConnection($flags = 0x0) {
                // Logic -> Assumes `mysqli_ping($this -> connection)` evaluates to `true`.
                if (false == mysqli_close($this -> connection)) {
                    // Logic > Error; Return
                    if (false == ($flags & Database::SILENCE_ERRORS)) throw new DatabaseException($this);
                    return false;
                }

                // Reset > Target > (Connection, Tables)
                $this -> connection = NULL;
                $this -> tables = [];

                // Return
                return true;
            }

            // Create Table
            public function createTable($name, $columnCount, $fieldNames, $types, $keys, $miscellanies, $flags = 0x0) {
                // Logic
                if ($this -> assertConnection(DatabaseException::UNOPEN_QUERY, $flags)) {
                    // Initialization > Table ...
                    $table = new DatabaseTable($this, $name, $columnCount, $fieldNames, $types, $keys, $miscellanies);
                    $tableExists = false;

                    // ...; Update > Table Exists
                    $this -> analyzeTables();

                    foreach ($this -> getTables() as $table)
                    if (0 == strcasecmp($name, $table -> getName())) { $tableExists = true; break; }

                    // Logic --- NOTE (Lapys) -> Ensure the table is as expected.
                    if (true == $tableExists) {
                        // Initialization > Table Column Count
                        $tableColumnCount = 0;

                        // Loop
                        foreach ($this -> query("DESCRIBE `" . $name . '`', Database::EXECUTE_QUERY) as $result) {
                            // Initialization > Field Exists; Loop
                            $fieldExists = false;
                            for ($iterator = $columnCount - 1; ~$iterator && $tableExists; --$iterator) {
                                // Initialization > (Field Name, Key, Miscellany, Type)
                                $fieldName = $fieldNames[$iterator];
                                $key = $keys[$iterator];
                                $miscellany = $miscellanies[$iterator];
                                $type = $types[$iterator];

                                // Logic --- NOTE (Lapys) -> Check that the table field names are consistent.
                                if (0 == strcmp($result["Field"], $fieldName)) {
                                    // Update > Field Exists
                                    $fieldExists = true;

                                    // Logic --- NOTE (Lapys) -> Check other field information for better accuracy.
                                    // : [Miscellany]
                                    if (0 != strcasecmp($result["Extra"], $miscellany))
                                    $fieldExists = false;

                                    // : [Key]
                                    switch ($result["Key"]) {
                                        case "MUL": $fieldExists = "MULTIPLE KEY" == $keys[$iterator]; break;
                                        case "PRI": $fieldExists = "PRIMARY KEY" == $keys[$iterator]; break;
                                        case "UNI": $fieldExists = "UNIQUE KEY" == $keys[$iterator];
                                    }

                                    // : [Type]
                                    if (0 != strcasecmp($result["Type"], $type))
                                    $fieldExists = false;

                                    // Terminate
                                    break;
                                }
                            }

                            // Logic > ...
                            if ($fieldExists) ++$tableColumnCount;
                            else { $tableExists = false; break; }
                        }

                        // ... Deletion --- NOTE (Lapys) -> Remove the unwanted table for replacement.
                        if (false == $tableExists || $columnCount != $tableColumnCount) {
                            $this -> destroyTable($name, $flags);
                            $tableExists = true;
                        }
                    }

                    // Logic --- NOTE (Lapys) -> Either the table does not exist or has an unexpected description.
                    if (false == $tableExists) {
                        // Initialization > Syntax
                        $syntax = "";

                        // Loop > Update > Syntax
                        for ($iterator = $columnCount - 1; ~$iterator; --$iterator) {
                            $syntax .= '`' . $fieldNames[$iterator] . '`';
                            $syntax .= ' ' . $types[$iterator];
                            $syntax .= "" == $miscellanies[$iterator] ? "" : ' ' . $miscellanies[$iterator];
                            $syntax .= "" == $keys[$iterator] ? "" : ' ' . $keys[$iterator];

                            $syntax .= 0 == $iterator ? "" : ", ";
                        }

                        // ...
                        $this -> query("CREATE TABLE `" . $name . "` (" . $syntax . ')');
                    }

                    // ...; Return
                    array_push($this -> tables, $table);
                    return $table;
                }

                // Return
                return NULL;
            }

            // Destroy Table
            public function destroyTable($name, $flags = 0x0) { return false == is_null($this -> query("DROP TABLE IF EXISTS `" . $name . '`', $flags)); }

            // Get (Last Error, Name, Tables)
            public function getLastError() { return $this -> hasConnection() ? mysqli_error($this -> connection) : ""; }
            public function getName() { return $this -> name; }
            public function getTables() { return $this -> tables; }

            // Query
            public function query($instruction, $flags = 0x0) {
                // Initialization > Result
                $evaluation = NULL;

                // Logic
                if ($this -> assertConnection(DatabaseException::UNOPEN_QUERY, $flags)) {
                    // Update > Evaluation
                    $evaluation = mysqli_query($this -> connection, $instruction);

                    // ...
                    if (false === $evaluation) {
                        if ($flags & Database::SILENCE_ERRORS) $evaluation = NULL;
                        else throw new DatabaseException($this);
                    }

                    // Logic > Update > Evaluation; ...
                    if ($flags & Database::EXECUTE_QUERY) {
                        if (false == is_null($evaluation)) $evaluation = mysqli_fetch_all($evaluation, MYSQLI_BOTH);
                        else if (false == ($flags & Database::SILENCE_ERRORS)) throw new DatabaseException(DatabaseException::INVALID_QUERY);
                    }

                    // Logic > ...
                    if ($flags & Database::ANALYZE_ALL)
                    $this -> analyzeTables();
                }

                // Return
                return $evaluation;
            }

            public function hasConnection() { return /* mysqli_ping() */ false == is_null($this -> connection); }
            public function openConnection($path, $username, $password, $flags = 0x0) {
                // Constant > Connection
                $connection = new mysqli($path, $username, $password);

                // Logic -> Assumes `mysqli_ping($connection)` evaluates to `true`.
                if (false == $this -> hasConnection()) {
                    // Constant > Connection Error (Code, Message)
                    $connectionErrorCode = mysqli_connect_errno();
                    $connectionErrorMessage = mysqli_connect_error();

                    // Logic
                    if (0x0 != $connectionErrorCode)
                        // Error
                        throw new DatabaseException($connectionErrorMessage, $connectionErrorCode);

                    else {
                        // Modification > Target > Connection
                        $this -> connection = $connection;

                        // ...
                        $this -> query("CREATE DATABASE IF NOT EXISTS `" . $this -> getName() . '`');
                        $this -> select();
                        $this -> analyzeTables();
                    }

                    // Return
                    return $connection;
                }
            }

            public function select($flags = 0x0) {
                // Initialization > Evaluation
                $evaluation = false;

                // Logic > Update > Evaluation; ...
                if ($this -> assertConnection(DatabaseException::UNOPEN_QUERY, $flags)) {
                    if (mysqli_select_db($this -> connection, $this -> getName()) || false == is_null($this -> query("USE `" . $this -> getName() . '`', Database::SILENCE_ERRORS))) $evaluation = $this -> getName() == $this -> query("SELECT DATABASE() FROM DUAL", Database::EXECUTE_QUERY | Database::SILENCE_ERRORS)[0]["DATABASE()"];
                    else if (false == ($flags & Database::SILENCE_ERRORS)) throw new DatabaseException($this);
                }

                // Return
                return $evaluation;
            }
    };
        /* Database Exception */
        class DatabaseException extends Exception {
            // Constant > ...
            public const INVALID_QUERY = 0x1;
            public const UNOPEN_QUERY = 0x2;

            // [Constructor]
            public function __construct($database, $code = 0x0, $previous = NULL) {
                // Initialization > Message; ...
                $message = "";

                // ... Update > Message
                if ($database instanceof Database) $message = 0x0 == $code ? $database -> getLastError() : $database;
                else switch (func_num_args() ? func_get_arg(0) : 0x0) {
                    case DatabaseException::INVALID_QUERY: $message = "Attempt to execute invalid database query/ instruction"; break;
                    case DatabaseException::UNOPEN_QUERY: $message = "Attempt to execute database query/ instruction without an open connection";
                }

                // ...
                parent::__construct($message, 0x0 == $code ? 0x1 : $code, $previous);
            }

            // Method > To String
            public function __toString() { return '[' . __CLASS__ . " (0x" . dechex($this -> code) . ")]" . ($this -> message ? ": " . $this -> message : "") . PHP_EOL; }
        };

        /* Database Table */
        class DatabaseTable {
            // Definition > (Column Count, Database, Field Names, Keys, Miscellanies, Types)
            private $columnCount = 0;
            private $database = NULL;
            private $fieldNames = [];
            private $keys = [];
            private $miscellanies = [];
            private $name = NULL;
            private $types = [];

            // [Constructor]
            public function __construct($database, $name, $columnCount, $fieldNames, $types, $keys, $miscellanies) {
                // Modification > Target > (Column Count, Database, Name)
                $this -> columnCount = $columnCount;
                $this -> database = $database;
                $this -> name = $name;

                // Loop > Update > (Target > ...)
                for ($iterator = 0; $columnCount != $iterator; ++$iterator) {
                    array_push($this -> fieldNames, $fieldNames[$iterator]);
                    array_push($this -> keys, $keys[$iterator]);
                    array_push($this -> miscellanies, $miscellanies[$iterator]);
                    array_push($this -> types, $types[$iterator]);
                }
            }

            // Method > ...
            public function getColumnCount() { return $this -> columnCount; }
            public function getDatabase() { return $this -> database; }
            public function getFieldName($index) { return $this -> fieldNames[$index]; }
            public function getFieldNames() { $fieldNames = []; foreach ($this -> fieldNames as $fieldName) array_push($fieldNames, $fieldName); return $fieldNames; }
            public function getFieldKey($index) { return $this -> keys[$index]; }
            public function getFieldKeys() { $keys = []; foreach ($this -> keys as $key) array_push($keys, $key); return $keys; }
            public function getFieldMiscellany($index) { return $this -> miscellanies[$index]; }
            public function getFieldMiscellanies() { $miscellanies = []; foreach ($this -> miscellanies as $miscellany) array_push($miscellanies, $miscellany); return $miscellanies; }
            public function getFieldType($index) { return $this -> types[$index]; }
            public function getFieldTypes() { $types = []; foreach ($this -> types as $type) array_push($types, $type); return $types; }
            public function getName() { return $this -> name; }

            public function setFieldKey($index, $key) { $this -> keys[$index] = $key; }
            public function setFieldMiscellany($index, $miscellany) { $this -> miscellanies[$index] = $miscellany; }
            public function setFieldName($index, $name) { $this -> fieldNames[$index] = $name; }
            public function setFieldType($index, $type) { $this -> types[$index] = $type; }
            public function setName($name) { $this -> name = $name; }
        };

    /* Global > (Database ..., Root) --- NOTE (Lapys) -> */
    $DATABASE = array_key_exists("DATABASE", get_defined_vars()) ? $DATABASE : new Database("Covenant University Undergraduate Admission", (object) [
        "password" => "Lapys30*)",
        "path" => "localhost" . ':' . 3306,
        "username" => "LapysDev"
    ]);

    $DATABASE_TABLE = array_key_exists("DATABASE_TABLE", get_defined_vars()) ? $DATABASE_TABLE : (is_null($DATABASE) ? NULL : $DATABASE -> createTable("Undergraduates", 9,
        /* Field Names */  ["Country", "First Name", "Gender", "ID", "Last Name", "Middle Name", "Password", "Program", "Registration Number"],
        /* Types */        ["VARCHAR(32)", "VARCHAR(32)", "ENUM('F','M','O')", "INT UNSIGNED", "VARCHAR(32)", "VARCHAR(32)", "VARCHAR(64)", "VARCHAR(64)", "VARCHAR(8)"],
        /* Keys */         ["", "", "", "PRIMARY KEY", "", "", "", "", ""],
        /* Miscellanies */ ["", "", "", "AUTO_INCREMENT", "", "", "", "", ""]
    ));

    $ROOT = (function($root) {
        // Logic -> Get the current working directory.
        if (false == isset($_SERVER["REQUEST_URI"]))
            // Update > URL
            $root = str_replace('\\', '/', getcwd()) . '/';

        else {
            // Initialization > (File Name, Server ...)
            $filename = /* __FILE__ */ $_SERVER["REQUEST_URI"];
            $server = NULL;

            // Update
                // File Name
                $filename = str_replace('\\', '/', $filename);

                if (false !== strpos($filename, '/')) $filename = trim(substr($filename, strrpos($filename, '/') + 1));
                if (false !== strpos($filename, '?')) $filename = trim(substr($filename, 0, strrpos($filename, '?')));

                // Server ...
                if (is_null($server) && isset($_SERVER["SERVER_ADDR"])) $server = $_SERVER["SERVER_ADDR"];
                if (is_null($server) && isset($_SERVER["SERVER_NAME"])) $server = $_SERVER["SERVER_NAME"];

                if (isset($_SERVER["SERVER_PORT"])) $server = false == is_null($server) ? $server . ':' . $_SERVER["SERVER_PORT"] : "";

                // Root
                $root = str_replace('\\', '/', $_SERVER["REQUEST_URI"]);
                if (false !== strpos($root, '?')) $root = trim(substr($root, 0, strrpos($root, '?')));
                if ("" !== $filename && strpos($root, $filename) == strlen($root) - strlen($filename)) $root = trim(substr($root, 0, strrpos($root, $filename)));

                $root = $server . '/' . substr($root, (int) ('/' == $root[0]));
                $root = (function($serverProtocol, $protocols) {
                    foreach ($protocols as $protocol) {
                        if (false !== stripos($serverProtocol, $protocol))
                        return strtolower($protocol) . "://";
                    } return "";
                })(isset($_SERVER["SERVER_PROTOCOL"]) ? $_SERVER["SERVER_PROTOCOL"] : "HTTP", [
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
                ]) . $root;
        }

        // Logic > ... -> Re-route the varying directories back to the root.
        if (strrpos($root, "pages/") == strlen($root) - strlen("pages/")) $root = substr($root, 0, strrpos($root, "pages/"));
        if (strrpos($root, "scripts/") == strlen($root) - strlen("scripts/")) $root = substr($root, 0, strrpos($root, "scripts/"));
        if (strrpos($root, "stylesheets/") == strlen($root) - strlen("stylesheets/")) $root = substr($root, 0, strrpos($root, "stylesheets/"));

        if ('/' == $root[strlen($root) - 1]) $root = substr($root, 0, -1); // -> Remove trailing slashes.

        // Return
        return $root;
    })("");
?>

<!-- Document Scripts -->
<script language=javascript type=text/javascript> var ROOT = "<?php echo str_replace('"', "\\\"", $ROOT); ?>"; void (document.currentScript.outerHTML = "") </script>
<script language=javascript src="<?php echo $ROOT; ?>/scripts/base.js<?php echo "?v=" . rand(); ?>" type=text/javascript> </script>

<!-- Document Stylesheet -->
<link href="<?php echo $ROOT; ?>/stylesheets/base.css<?php echo "?v=" . rand(); ?>" media=all rel="stylesheet"/>

<!-- Document Favorite Icon -->
<link href="<?php echo $ROOT; ?>/favicon.ico" rel="shortcut icon"/>

<!-- Document Metadata -->
<meta charset="UTF-8"/>
<meta content="height=device-height, initial-scale=1.0, maximum-scale=1.0, minimal-ui, minimum-scale=1.0, user-scalable=no, width=device-width" name="viewport"/>
<meta content="text/html; charset=UTF-8" http-equiv="Content-Type"/>
