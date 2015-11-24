<!-- HOME -->
<?php
	if(!isset($_COOKIE['username'])){
		header("Location:Login.php");
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
     <script type="text/javascript" src="home.js"></script>
     <link rel="stylesheet" type="text/css" href="home.css">
 </head>

 <body>

     <!-- NO SCROLL -->
         <?php
         include "header.html";
         ?>

     <img id="welcomeImage" src="./image/home_parkour.jpg">

     <p id="eventTitle">Events</p>
     <div id="eventMenu"> 
         
     </div>
     
     <p id="localEvents">Local Events</p>
     <div id="localMenu">
     	
     </div>

 </body>

</html>
