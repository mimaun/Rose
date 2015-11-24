<?php 

$db = new PDO("mysql:dbname=brinegjr;host=localhost", "brinegjr", "abcde");
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

if(isset($_COOKIE["username"])) {
    $username = $_COOKIE["username"];
}

?>
