<?php
include("db.php");
session_start();

$check = $db->quote($_SESSION['name']);
$query_text = "select * from login where name=$check;";
$rows = $db->query($query_text);

foreach($rows as $row) { // at most one row
	$login_session = $row['name'];
	$login_id = $row['id'];
	$login_visits = $row['visits'];
	
}

if(!isset($login_session)) {
	header("Location: index.php");
}

?>