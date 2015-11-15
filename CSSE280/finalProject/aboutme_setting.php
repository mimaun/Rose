<!-- ABOUTME -->

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

        <div id="header-top">

            <!-- logo image -->
            <img id="logo" src="./image/logo.png">

            <!-- tabs using bootstrap -->
            <div id="tabs">
                <ul class="nav nav-tabs">
                    <li><a href="home.php" data-toggle="tab">HOME</a></li>
                    <li><a href="#" data-toggle="tab">SEARCH</a></li>
                    <li><a href="#" data-toggle="tab">LOGIN</a></li>
                    <li class="active"><a href="#" data-toggle="tab">ABOUTME</a></li>
                </ul>
            </div> 
        </div>

        <h2>Profile Setting</h2>

        <form id="profileForm">
            First Name :&#009;<INPUT type="TEXT" id="firstname"> <br>
            Last Name :&#009;<INPUT type="TEXT" id="lastname"> <br>
            ZIP Code :&#009;<INPUT type="TEXT" id="lastname"> <br>
            City :&#009;&#009;<INPUT type="TEXT" id="city"> <br>
            <INPUT type="RADIO" name="playStyle" id="indoor" checked> Indoor
            <INPUT type="RADIO" name="playStyle" id="outdoor"> Outdoor
            <TEXTAREA id="description" cols=75 rows=15 placeholder="Description"></TEXTAREA>
            <INPUT type="SUBMIT" id="submitButton">
        </form>

    </body>

</html>
