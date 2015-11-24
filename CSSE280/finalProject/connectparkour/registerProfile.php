<?php

header('Content-Type', 'application/json');

include("db.php");

// get username from cookie.
if(isset($_COOKIE["username"])) {
    $username = $db->quote($_COOKIE["username"]);
} 

if(isset($_POST["state"])) {
    $stateToEnter = $_POST["state"];
    $stateToEnter = $db->quote($stateToEnter);
}

if(isset($_POST["city"])) {
    $cityToEnter = $_POST["city"];
    $cityToEnter = $db->quote($cityToEnter);
}

if(isset($_POST["experience"])) {
    $exToEnter = $_POST["experience"];
    $exToEnter = $db->quote($exToEnter);
} else {
    $exToEnter = $db->quote();
}

if(isset($_POST["aboutme"])) {
    $amToEnter = $_POST["aboutme"];
    $amToEnter = $db->quote($amToEnter);
} else {
    $amToEnter = $db->quote();
} 

$get_Id_query = "
SELECT Id FROM Users WHERE Username = $username;
";

try {
    $result = $db->query($get_Id_query);
    while($row = $result->fetchObject()) {
        $id[] = array(
            "id" => $row->Id
        );
        if($id != null) {
            $Id = $id[0];
            $pid = $db->quote($Id["id"]);
        }
    }
}

catch(PDOException $ex) {
    echo "in catch";
    echo $ex->getMessage();
    return json_encode(array("success" => false)); 
} 

$replace_query_text = "
    UPDATE Users 
    SET City = $cityToEnter, State = $stateToEnter, Experience = $exToEnter, AboutMe = $amToEnter
    WHERE Id = $pid
;
"; 

echo "-----**--------";
echo $replace_query_text;

// replacae user data.
try {
        $db->query($replace_query_text);
        return json_encode(array("success" => true));
}

catch(PDOException $ex) {
    echo "in catch";
    echo $ex->getMessage();
    return json_encode(array("success" => false)); 
} 
?>
