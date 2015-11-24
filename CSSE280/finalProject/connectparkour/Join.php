<?php
	$username = "brinegjr";
	$password = "abcde";
	$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
	$eventname = $conn->quote($_POST['EventName']);
	$username = $conn->quote($_COOKIE['username']);
	$query = "INSERT INTO `EventsForUser`(`EventName`, `Username`) VALUES(" . $eventname . ", " . $username . ")";
	$stmt = $conn->query($query);
	$error = $conn->errorInfo();
	print_r($error);
?>