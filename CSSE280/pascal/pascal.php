<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Pascal Triangle</title>
    <link rel="stylesheet", type="text/css" href="pascal.css">
</head>
<body>

<h1>Pascal Triangle</h1>

<?php

$num = 4;
$oddColor = "red";
$evenColor = "lightgreen";

if ($_SERVER["REQUEST_METHOD"] == "POST") {

    getValue();
}

?>

<br />
<form action="pascal.php" method="post" 
<div>
<fieldset>
    <legend>Pascsl choices: </legend>
    <input type="radio" name="val" value="4" checked="checked" />4
    <input type="radio" name="val" value="8" />8
    <input type="radio" name="val" value="12" />12
    <input type="radio" name="val" value="16" />16
    <input type="radio" name="val" value="20" />24
    <input type="radio" name="val" value="24" />28
    <input type="radio" name="val" value="32" />32
    <br />
Color for odd numbers: 
    <input type="text" name="oddColor" /> Any HTML color name
    <br />
Color for even numbers: 
    <select name="evenColor">
        <option value="lightgreen">Green</option>
        <option value="lightblue">Blue</option>
        <option value="orange">Orange</option>
        <option value="yellow">Yellow</option>
    </select> 
</fieldset>
</div>
<div>
<input type="submit" name="send" value="Submit" />
</div>
</form>
<br />
<br />


</body>
</html>


<?php

function getValue() {

    global $num;
    global $oddColor;
    global $evenColor;
    // get value of radio button.
    /*if(isset($_POST["val"]))*/ 
    $num = (int)$_POST["val"];

    // get value of oddColor.
    $oddColor = htmlspecialchars($_POST["oddColor"]);

    // get value of evenColor;
    $evenColor = $_POST["evenColor"];

    draw();
}

// pascal functino.
function comb($n, $r) {
    if($r == 0 || $r == $n) return 1;
    else return comb($n - 1, $r - 1) + comb($n - 1, $r);
}

// judge even or odd.
function isEven($x) {
    // odd.
    if($x % 2) return false;

    // even.
    else return true;
} 

function draw() {

    global $num;
    global $evenColor;
    global $oddColor;

?>
<div id="pascal">
    <?
    for($i = 0; $i <= $num; $i++) :
    for($j = 0; $j <= $i; $j++) :

    $val = comb($i, $j);
    if(isEven($val)) {
    ?>
        <span class="even" style="background-color: <?=$evenColor?>">
                    <?
                    }
                    else {
                    ?>
                        <span class="odd" style="background-color: <?=$oddColor?>">
                        <?
                        }
                        ?>
                        <?=comb($i, $j)?>
                    </span>
        <?php

        endfor;
        ?>
        <br>
        <?
        endfor;
        ?>
</div>
        <?
} 
        ?>


