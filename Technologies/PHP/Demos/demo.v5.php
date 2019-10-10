<!DOCTYPE html>

<?php
    // Initialization > String
    $string = 'Hello'
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
        '> Debugging Room | PHP String </caption>

        <tbody style='background-color: #E7E7E7'>
            <tr style="background-color: #FFF; font-family: 'Google Sans'; font-size: 120%">
                <th> $string </th> <th> <?php echo $string ?> </th>
            </tr>
            <tr> <td> "Formatted String: '$string'" </td> <td> <?php echo "Formatted String: '$string'" ?> </td> </tr>
            <tr> <td> $string . ', World!' </td> <td> <?php echo $string . ', World!' ?> </td> </tr>
            <tr> <td> strlen($string) </td> <td> <?php echo strlen($string) ?> </td> </tr>
            <tr> <td> substr($string, 0, -3) </td> <td> <?php echo substr($string, 0, -3) ?> </td> </tr>
            <tr> <td> explode('l', $string) </td> <td> <?php print_r(explode('l', $string)) ?> </td> </tr>
            <tr> <td> implode('l', explode('l', $string)) </td> <td> <?php echo implode('l', explode('l', $string)) ?> </td> </tr>
            <tr> <td> str_split($string) </td> <td> <?php print_r(str_split($string)) ?> </td> </tr>
        </tbody>
    </table>
</body>
</html>
