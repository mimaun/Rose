<!DOCTYPE html>
<html>
<head>
    <title>Simple message board</title>
    <link href="msgboard.css" type="text/css" rel="stylesheet" />
</head>

<body>
<h1>Simple Message Board</h1>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    # user is posting a message
    save_post();
}

display_posts();
?>

<form action="msgboard.php" method="post"
      enctype="multipart/form-data">
    <fieldset>
        <legend>post a new message</legend>

        <div>
            user name: <br />
            <input type="text" name="username" size="50" /> <br />

            <label>
                <input type="checkbox" name="anonymous" />
                post anonymously
            </label>
        </div>

        <div>
            message: <br />
            <textarea name="message" rows="8" cols="60"></textarea>
        </div>

        <div>
            image (optional): <br />
            <input type="file" name="image" size="50" />
        </div>

        <div>
            <input type="submit" value="post message" />
        </div>
    </fieldset>
</form>
</body>
</html>

<?php

# Saves the user's form POST data as a message on the server.
# You should fill in the details
# Hint:  For each post, save the text (and image if there is one) as separate files.
#        Include date and time in the filenames so that display_posts can display them in date order.
# Hint: Some useful PHP functions:  file_put_contents, isset, is_uploaded_file, move_uploaded_file

function save_post() {

    $username = NULL;
    $message = NULL;

    // check whether username is anonymous or not.
    if(isset($_POST["anonymous"])) $username = "anoanymous message";
    else $username = htmlspecialchars($_POST["username"]);

    // ex. 2015-09-26:05-48-06.
    $date = date("Y-m-d:H-i-s");

    // get message.
    $message = htmlspecialchars($_POST["message"]);

    // check image file.
    if(is_uploaded_file($_FILES["image"]["tmp_name"])) {

        // save image file.
        if(move_uploaded_file($_FILES["image"]["tmp_name"], "posts/" . $date . "_image.png")) {
            chmod("posts/" . $date . "_image.png", 0755);
            // $image = file_get_contents("posts/" . $date . "_image.png");
            // header('Content-type: iamge/jpg');
        }
    }

    // save username and message to file.
    if(isset($username) && isset($message)) {

        // filename: Y-m-d:H-i-s.txt
        file_put_contents("posts/" . $date . ".txt", $username . ": " . $message . "\n");
        chmod("posts/" . $date . ".txt", 0755);
    }

    $username = NULL;
    $message = NULL;
}

# Displays all messages on the board, each in its own div.
# You should fill in the details.
# Hint: Some useful PHP functions:  file_exists, glob, rsort, str_replace
function display_posts() {

    $textFiles = array();
    $dateList = array();

    // get all text file name.
    foreach(glob("posts/*.txt") as $filename) array_push($textFiles, $filename);

    // sort.
    rsort($textFiles);

    // make date list to make sure whether image file exists or not.
    foreach($textFiles as $filename) {
        $date = explode(".txt", $filename);
        array_push($dateList, $date[0]);
    }

    for($i = 0; $i < count($dateList); $i++) :

        // check whether image file exists or not.
        // if(file_exists("posts/" . $date[i] . "_image.png")) {
        // }
        if(file_exists($dateList[$i] . ".txt")) :
            $message = file($dateList[$i] . ".txt")[0];
            ?>
            <div class="message">
                <?
                if(file_exists($dateList[$i] . "_image.png")) :
                    $imageName = $dateList[$i] . "_image.png";
                    ?>
                    <img src=<?=$imageName?> alt="user image" />
                    <?
                endif;
                echo $message;
                ?>
            </div>
            <?php
        endif;
    endfor;
}

?>

