<?php

include("db.php");

// session start.
session_start();
if(isset($_SESSION)) {
    session_unset();
    session_destroy();
} 
session_start();

if(isset($_REQUEST['username']) && isset($_REQUEST['password'])) {

    $name = $_REQUEST['username'];
    $name_quoted = $db->quote($name);
    $password = $db->quote($_REQUEST['password']);
    $pass_quoted = $db->quote($password);

    // print $query_text;

    $query_count_text = "select count(*) from login where name=$name_quoted and password=$password;";
    // print $query_count_text;
    $count = $db->query($query_count_text);
    // print $count->fetchColumn();

    if($count->fetchColumn() > 0) {
        $_SESSION["name"] = $name;
        $query_text = "select * from login where name = $name_quoted and password = $password;";
        $rows = $db->query($query_text);
        // print $count;

        foreach($rows as $row) {
            $visits = $row["visits"];
            $id = $row["id"];
            $query_text = "replace into login (id, name, password, visits) values (" .
                $id . "," . $name_quoted . "," . $password. "," . ($visits+1) . ");";
            // print $query_text;
            $replace_rows = $db->exec($query_text);
            header("location: profile.php");
        }
    }
    else {  // unsuccessful login.
        // redirect.
        header("location: index.php");
    }


}

?>


