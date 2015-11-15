<!--Name: Misato Morino-->
<!--Section: 01-->
<!--HW3-->
<!--html file, css file, mymovie, and image files-->

<!DOCTYPE html>
<html>
<head>
    <title>Rancid Tomatoes</title>

    <meta charset="utf-8" />
    <link href="movie.css" type="text/css" rel="stylesheet" />

    <!--favicon-->
    <link rel="shortcut icon" href="./rotten.gif" type="image/gif">
</head>

<body>
<div class="header">
    <div id="top">
        <img src="banner.png" alt="Rancid Tomatoes" />
    </div>
</div>

<?php
// get parameter.
$movie = $_GET["film"];

// get information from info.txt.
$info = file("./$movie/info.txt");
?>

<!-- Title -->
<h1><?=$info[0]?> (<?=$info[1]?>)</h1>

<div id="main">

    <!-- overview (right side) -->
    <div id="general_overview">
        <!-- image-->
        <img src="<?=$movie;?>/overview.png" alt="general overview" />

        <dl>
<?php
// get overview from overview.txt.
$overview = file("./$movie/overview.txt");

for($i = 0; $i < count($overview); $i++):

    $line = $overview[$i];
$line = explode(":", $line);
?>

                <dt><?=$line[0]?></dt>
                <dd><?=$line[1]?></dd>

<?php
endfor;
?>
        </dl>
    </div>
    <!-- end overview (right side) -->

    <div id="left">
        <div class="header">
            <div id="rating">
<?php
// if rating >= 60, img is "freshbig.png".
$rotten = "rottenbig.png";
if((int)$info[2] > 61)
    $rotten = "freshbig.png";
?>
                <img src=<?=$rotten?> alt="Rotten" />
                <span><?=$info[2]?>%</span>
            </div>
        </div>

<?php
$files = glob("$movie/review*.txt");
$fileNum = count($files);
$trigger = 0;
$img = "";

// if num of file is odd, left is larger than right.
$trigger = round($fileNum / 2);

$cnt = 0;

foreach($files as $file) {

    // left.
    if($cnt == 0) {
?>
        <div id="columns1">
<?php
    }

    // right.
    else if($cnt == $trigger) {
?>
        </div>
        <div id="columns2">
<?php
    }

    $contents = file($file);
    $imgName = strtolower($contents[1]);
?>

            <!-- a column -->
            <div class="column">
                <div class="review">
                    <p>
                        <img src="<?=$imgName?>.gif" alt="Rotten" />
                        <q><?=$contents[0]?></q>
                    </p>
                </div>
                <p>
                    <img src="critic.gif" alt="Critic" />
                    <?=$contents[2]?><br />
                    <em><?=$contents[3]?></em>
                </p>
            </div>

<?php
    $cnt++;
}
?>
        </div>
    </div>

    <div id="bottom">
        (1-<?=$fileNum?>) of <?=$fileNum?>
    </div>
</div>

<div class="validator">
    <a href="https://webster.cs.washington.edu/validate-html.php"><img src="http://webster.cs.washington.edu/w3c-html.png" alt="Valid HTML5" /></a> <br />
</div>
<div class="validator">
    <a href="https://webster.cs.washington.edu/validate-css.php"><img src="http://webster.cs.washington.edu/w3c-css.png" alt="Valid CSS" /></a>
</div>
</body>
</html>


