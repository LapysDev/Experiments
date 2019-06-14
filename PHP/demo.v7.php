<!DOCTYPE html>
<html>
<head>
    <!-- Document Metadata -->
        <!-- Character Encoding Set -->
        <meta charset=utf-8>

    <!-- Document Title -->
    <title> Debugging Room </title>
</head>

<body>
    <?php
        // Function > Sum
        function sum() {
            // Initialization > (Is Array, Arguments, Iterator, Result)
            $args = is_array(func_get_args()[0]) ? func_get_args()[0] : func_get_args();
            $iterator = count($args);
            $result = 0;

            // Loop > Update > Result
            while ($iterator)
                $result += $args[$iterator -= 1];

            // Return
            return $result;
        }

        // Echo
        echo sum(2, 3) + sum([3, 2])
    ?>
</body>
</html>
