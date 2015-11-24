<?php

header('Content-Type', 'application/json');

include("db.php");

if(isset($_POST["username"])) {
    $username = $_POST["username"];
    $username_q = $db->quote($username);
} 
else if(isset($_COOKIE["username"])) {
    $username = $_COOKIE["username"];
    $username_q = $db->quote($username);
}

$sql = "SELECT * FROM Users WHERE Username = $username_q;";


try {
    $result = $db->query($sql);

    while($row = $result->fetchObject()) {
        $userInfo[] = array(
            "city" => $row->City,
            "state" => $row->State,
            "experience" => $row->Experience,
            "aboutme" => $row->AboutMe,
        );
    }

    echo json_encode($userInfo);
} 

catch (PDOException $ex) {

    $errArr[] = array(
        "city" => "",
        "state" => "",
        "experience" => "",
        "aboutme" => ""
    );
    echo json_encode($errArr);
    
}

?>
