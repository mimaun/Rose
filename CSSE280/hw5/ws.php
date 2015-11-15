<!DOCTYPE html>

<!-- CSSE280 WebProgramming HW4                                                               -->
<!-- Name: Misato Morino                                                                      -->
<!-- ID: morinom                                                                              -->

<?php
function getWSFiles() {
    $files = array();
    // get file names from puzzles directory.
    foreach(glob("puzzles/*.ws") as $filename) {
        // delete "puzzles/"
        $f = explode("/", $filename)[1];
        array_push($files, $f);
    }
    return $files;
}

?>

<html lang="en">
<head>
    <meta charset="UTF-8">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script> 
    <script src="ws.js" type="text/javascript"></script>
    <title>Word Search</title>
</head>
<body>

<h1>HW5 Word Search</h1>

<p>Click first character, and end character.<p>
<p>When you want a hint, click the word in right section.</p>

<div id="puzzleList">
    <ul>
        <li>
            <table id="tablePuzzle"></table>
        </li>
        <li>
            <div id="answerSpace"></div>
        </li>
    </ul>
</div>

<div id="form">
    <p>Choose puzzle<p/>
    <select id="puzzle"> 
    <?php 
    // get filenames.
    $files = getWSFiles();
    foreach($files as $file):
        ?>
        <option><?=$file?></option>
        <?
    endforeach;
    ?>
    </select>
    <button id="puzzleChoice">Choice</button>
</div>


</body>
</html>
