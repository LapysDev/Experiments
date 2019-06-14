<!DOCTYPE html>

<?php
    // Initialization > Array
    $array = ['A', 'B', 'C'];
?>

<html>
<head>
    <!-- Document Metadata -->
        <!-- Character Encoding Set -->
        <meta charset=utf-8>

    <!-- Document Title -->
    <title> Debugging Room </title>
</head>

<body>
    <table style='
        border: 1px solid #CCC;
        color: #333;
        font-family: unifont;
        font-size: 1.175em;
        font-weight: 600;
        margin: 15px auto;
        text-align: left;
        width: 80%
    '>
        <caption style='
            font-family: Raleway;
            font-size: 165%;
            font-weight: bold;
            margin: 15px auto;
            text-align: left
        '> Debugging Room | PHP Array </caption>

        <tbody style='background-color: #E7E7E7'>
            <tr style="background-color: #FFF; font-family: 'Google Sans'; font-size: 120%">
                <th> $array </th> <th> <?php print_r($array) ?> </th>
            </tr>

            <tr> <td> $array[0] </td> <td> <?php echo $array[0] ?> </td> </tr>
            <tr> <td> $array[1] </td> <td> <?php echo $array[1] ?> </td> </tr>
            <tr> <td> $array[2] </td> <td> <?php echo $array[2] ?> </td> </tr>
            <tr> <td> $array[3] = 'D' </td> <td> <?php $array[3] = 'D'; print_r($array) ?> </td> </tr>
            <tr> <td> unset($array[0]) </td> <td> <?php unset($array[0]); print_r($array) ?> </td> </tr>
            <tr> <td> count($array) </td> <td> <?php echo count($array) ?> </td> </tr>
            <tr> <td> reset($array) </td> <td> <?php echo reset($array) ?> </td> </tr>
            <tr> <td> end($array) </td> <td> <?php echo end($array) ?> </td> </tr>
            <tr> <td> array_push($array, 'E') </td> <td> <?php array_push($array, 'E'); print_r($array) ?> </td> </tr>
            <tr> <td> array_pop($array) </td> <td> <?php array_pop($array); print_r($array) ?> </td> </tr>
            <tr> <td> array_unshift($array, 'A') </td> <td> <?php array_unshift($array, 'A'); print_r($array) ?> </td> </tr>
            <tr> <td> array_shift($array) </td> <td> <?php array_shift($array); print_r($array) ?> </td> </tr>
            <tr> <td> $array = array_merge($array, ['A', 'E']) </td> <td> <?php $array = array_merge($array, ['A', 'E']); print_r($array) ?> </td> </tr>
            <tr> <td> sort($array) </td> <td> <?php sort($array); print_r($array) ?> </td> </tr>
            <tr> <td> $array = array_slice($array, 0, 4) </td> <td> <?php $array = array_slice($array, 0, 4); print_r($array) ?> </td> </tr>
        </tbody>
    </table>
</body>
</html>
