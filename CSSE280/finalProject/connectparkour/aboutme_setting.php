 <?php
    $username = "";

    // if user login
	if(isset($_COOKIE["username"])){
        $username = $_COOKIE["username"]; 
    } else {
		header('Location:Login.php');
    }
?> 

<? //$username="testuser" ?>

<html> 
    <head>
        <title>About Me</title> 
        <meta charset="utf-8">

        <!-- read jQuery and jQueryUI. -->
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script src="//code.jquery.com/ui/1.11.0/jquery-ui.js"></script>  

        <!-- read bootstrap. -->
        <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css" />

        <!-- read local files. -->
        <script type="text/javascript" src="aboutme_setting.js"></script>
        <link rel="stylesheet" type="text/css" href="aboutme_setting.css">
    </head>

    <body>

        <?php
        include "header.html";
		?>

        <h2>Profile Setting</h2>

        <form id="profileForm">
            Username :&#009;<span id="username"><?=$username?></span> <br>
            State :&#009;&#009;<SELECT id="state"></SELECT> <br>
            City :&#009;&#009;<SELECT id="city"></SELECT> <br>

            Experience: <br>
            <TEXTAREA id="experience" cols=75 rows=6 placeholder="Experience"></TEXTAREA> <br>
            Introduction yourself: <br>
            <TEXTAREA id="aboutme" cols=75 rows=6 placeholder="About you"></TEXTAREA><br>

            <button id="submitButton" type="button" class="btn btn-default">SUBMIT</button> <br>
        </form>

    </body>

</html>
