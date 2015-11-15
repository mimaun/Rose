<?php
function curPageURL() {
 $pageURL = 'http';
 if (isset($_SERVER["HTTPS"]) && $_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
 $pageURL .= "://";
 if ($_SERVER["SERVER_PORT"] != "80") {
  $pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
 } else {
  $pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
 }
 return $pageURL;
}
?>

<!DOCTYPE html>   <!-- TicTacToe Solution by Claude Anderson and (your name here) -->
<html>
<head>
	<title> TicTacToe </title>
	<link href="ttt.css" rel="stylesheet">

<?php
	if (isset($_GET["size"])) {
?>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
	<script src="ttt.js" type="text/javascript"></script>
<?php
	}
?>
    <meta chartype="utf-8" />
</head>
<body>
	
<?php

	if (!isset($_GET["size"])) { #display the form
?>
		<h1> TicTacToe </h1>
		<form action="<?=curPageURL()?>">
            Choose a row size:
            <input type="radio" name="size" value="3" />3
            <input type="radio" name="size" value="4" checked />4
            <input type="radio" name="size" value="5" />5
            <input type="radio" name="size" value="6" />6
            <input type="submit" value="Choose" />
        </form>
			

<?php
	} else {  # has the expected parameter, so this is the second HTTP request to the server.
	
	   $size=$_GET["size"];
        chdir("Files");
        $files = glob("$size*.txt");
        $filenames = array();
        array_push($filenames, "NEW GAME");
        foreach($files as $f) 
            array_push($filenames, substr($f, 1, 5));
?>

<!-- You write the part that makes the form and the hidden div that contains the file contents
THe code that I cut out is around 25 lines long  -->

<div id="boardsize"><?=$size?></div>

		<div id="form">
        <hr>
            Choose a file
            <select id="gameType">
<?
        foreach($filenames as $f) {
?>
        <option><?=$f?></option>
<?
    }
?>
        </select>
        <button id="Choose">Choose!</button> <br>
        <h1> TicTacToe </h1>
<?
        $b = "";
        for($i = 0; $i < $size * $size; $i++) 
            $b = $b . "b";
        $contents = array();
        foreach($files as $f) {
            array_push($contents, file("./" . $f)[0]);
            }
        ?>
        <div class="type" id="new"><?=$size. "|X|" . $b?></div>

<?
        for($i = 1; $i < count($filenames); $i++) {
?>
        <div class="type" id="<?=$filenames[$i]?>"><?=$contents[$i-1]?></div>
<?
        }
?>
        </div>

      <div id="board"></div>  <!-- placeholders for htings to be filled in by Javascript -->
      <div id="finalMessage"></div>
<?
    }
?>
   </body>
</html>
