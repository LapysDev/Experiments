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
    <?php $list = [1, 2, 3]; ?>

    <p>
        <code>for</code> statement:
            <?php
                // Initialization > (Iterator, Length)
                $iterator = 0;
                $length = count($list);

                // Loop > Echo
                for ($iterator; $iterator != $length; $iterator = $iterator + 1)
                    echo $list[$iterator] . ($iterator == $length - 1 ? '' : ', ');
            ?> <br>
        <code>foreach</code> statement: <?php foreach ($list as $item) echo $item . ', ' ?> <br>
        Extended <code>foreach</code> statement: <?php foreach ($list as $key => $value) echo $value . ($key == $length - 1 ? '' : ', ') ?> <br>
        <code>while</code> statement:
            <?php
                // Update > Iterator
                $iterator = $length;

                // Loop
                while ($iterator) {
                    // Update > Iterator
                    $iterator = $iterator - 1;

                    // Echo
                    echo $list[$iterator] . ($iterator ? ', ' : '');
                }
            ?> <br>
    </p>

    <small> <em><code>break</code> and <code>continue</code> keywords apply as well.</em> </small>
</body>
</html>
