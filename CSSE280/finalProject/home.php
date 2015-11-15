<!-- HOME -->

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
     <div id="fixed">
         <div id="header-top">

             <!-- logo image -->
             <img id="logo" src="./image/logo.png">

             <!-- tabs using bootstrap -->
             <div id="tabs">
                 <ul class="nav nav-tabs">
                     <li class="active"><a href="#" data-toggle="tab">HOME</a></li>
                     <li><a href="#" data-toggle="tab">SEARCH</a></li>
                     <li><a href="Aboutme_setting.php" data-toggle="tab">ABOUTME</a></li>
                 </ul>
             </div>
             <button id="loginButton" type="button" class="btn btn-primary">LOGIN</button>
         </div>
     </div>

     <img id="welcomeImage" src="./image/home_parkour.jpg">

     <p id="eventTitle">Events</p>
     <div id="eventMenu"> 
         <dt>event1</dt>
         <dd>event1 contents</dd>

         <dt>event2</dt>
         <dd>event2 contents</dd>

         <dt>event3</dt>
         <dd>event3 contents</dd>
     </div>

 </body>

</html>
