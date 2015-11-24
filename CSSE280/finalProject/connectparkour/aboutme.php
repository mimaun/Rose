 <?php

 /*
  * if username isn't posted, page will show user's profile.
  * if code could get other usernamme with post, page will show the username's profile.
  * */

 if(isset($_GET["username"])) {
     $username = $_GET["username"];
 } 
 else if(isset($_COOKIE["username"])) {
     $username = $_COOKIE["username"];
 }
 else if(!isset($_COOKIE["username"])) {
     header("Location: Login.php");
 }
?> 

<html> 
    <head>
        <title>connectParkour</title> 
        <meta charset="utf-8">

        <!-- read jQuery and jQueryUI. -->
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script src="//code.jquery.com/ui/1.11.0/jquery-ui.js"></script>  

        <!-- read bootstrap. -->
        <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css" />

        <!-- read local files. -->
        <script type="text/javascript" src="aboutme.js"></script>
        <link rel="stylesheet" type="text/css" href="aboutme.css">
    </head> 
    <body>

        <?php
        include "header.html";
        ?>
        

        <h2><span id="username"><?=$username?></span>'s Profile</h2> 

        <div id="profileDiv">
            City: <span id="city"></span> <br>
            State: <span id="state"></span> <br>
            Experience: <br>
            <TEXTAREA id="experience" class="profileTextArea" readonly></TEXTAREA> <br>
            AboutMe: <br>
            <TEXTAREA id="aboutme" class="profileTextArea" readonly></TEXTAREA> <br>
			<?php
			if(!isset($_GET['username'])){
				echo "<button id='settingButton' type='button' class='btn btn-default'>SETTING</button> <br>";
			}
            ?>
        </div>


    </body>
</html>

