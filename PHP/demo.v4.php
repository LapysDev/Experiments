<!DOCTYPE html>

<?php
    // Initialization > Keys Array
    $keys_array = [
        'A', 'B', 'C',
        'Name' => 'Lapys',
        'Age' => 22
    ];
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
        '> Debugging Room | PHP Array (with Keys) </caption>

        <tbody style='background-color: #E7E7E7'>
            <tr style="background-color: #FFF; font-family: 'Google Sans'; font-size: 120%">
                <th> $keys_array </th> <th> <?php print_r($keys_array) ?> </th>
            </tr>

            <tr> <td> $keys_array[0] </td> <td> <?php echo $keys_array[0] ?> </td> </tr>
            <tr> <td> $keys_array[1] </td> <td> <?php echo $keys_array[1] ?> </td> </tr>
            <tr> <td> $keys_array[2] </td> <td> <?php echo $keys_array[2] ?> </td> </tr>
            <tr> <td> $keys_array['Name'] </td> <td> <?php echo $keys_array['Name'] ?> </td> </tr>
            <tr> <td> $keys_array['Age'] </td> <td> <?php echo $keys_array['Age'] ?> </td> </tr>
            <tr> <td> $keys_array['Job'] = 'Special Ops.' </td> <td> <?php $keys_array['Job'] = 'Special Ops.'; print_r($keys_array) ?> </td> </tr>
            <tr> <td> array_key_exists(0, $keys_array) </td> <td> <?php echo array_key_exists(0, $keys_array) ? 1 : 0 ?> </td> </tr>
            <tr> <td> array_key_exists('Name', $keys_array) </td> <td> <?php echo array_key_exists('Name', $keys_array) ? 1 : 0 ?> </td> </tr>
            <tr> <td> array_key_exists('Joel', $keys_array) </td> <td> <?php echo array_key_exists('Joel', $keys_array) ? 1 : 0 ?> </td> </tr>
            <tr> <td> array_keys($keys_array) </td> <td> <?php print_r(array_keys($keys_array)) ?> </td> </tr>
            <tr> <td> array_values($keys_array) </td> <td> <?php print_r(array_values($keys_array)) ?> </td> </tr>
        </tbody>
    </table>
</body>
</html>
