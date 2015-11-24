<?php

include("db.php");

$state = $_POST["state"];
$state  = $db->quote($state);
$sql = "SELECT * FROM cities WHERE state_code = $state";

try {
    $result = $db->query($sql);

    while($row = $result->fetchObject()) {
        $cityList[] = array(
            "city" => $row->city
        );
    }

    echo json_encode($cityList);
} 

catch (PDOException $ex) {
    $errArr[] = array("city" => "error");
    return json_encode($errArr);
}

?>
