<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="exam1.css">
    <title>Factors of numbers</title>
</head>
<body>

<h1>Factors of numbers</h1>

<?php

function checkPrime($i) {

    $num = array(-1);

    if($i == 1) return array_push($num, 1);
    else if($i == 2) return $num;
    else {
//    judge whether i is prime number or not
        for ($j = 2; $j <= round($i / 2); $j++):
            if ($i % $j == 0)
                array_push($num, $j);
            else continue;
        endfor;
    }
    return $num;
}
?>

<?php
$max = (int)$_GET["max"];
$cols= (int)$_GET["cols"];

?>
<div id="numbers" column-count="<?=$cols?>">
    <?
    for($i = 1; $i < $max+1; $i++):

    $num = checkPrime($i);
    // prime number
    if(count($num) == 1) {
    ?>
    <div class="prime">
        <? echo $i; ?>
        <?
        continue;
        }

        else {
        ?>
        <div class="non-prime">
            <? echo $i . " "; ?>
            <span>
                &ensp;
            <?
            for($k = 1; $k < count($num); $k++) :
                echo $num[$k] . " ";
            endfor;
            ?> </span> <?
            }
            ?>
        </div>

        <?
        endfor;
        ?>
    </div>

</body>
</html>
