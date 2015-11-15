<?php

$db = new PDO("mysql:dbname=world;host=localhost", "root", "tgh02lic");
$rows = $db->query("SELECT * FROM countries WHERE population > 1000000;");

var_dump($rows);

foreach($rows as $row) {
    print $row["name"];
    print "\n";
}
?>
