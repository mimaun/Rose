<?php
	$username = "brinegjr";
	$password = "abcde";
	$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
	$username = $conn->quote($_COOKIE['username']);
	$query = "SELECT `Zipcode` FROM `Users` WHERE `Username`=" . $username;
	$stmt = $conn->query($query);
	$array = array();
	while($row = $stmt->fetch()){
		array_push($array, $row['Zipcode']);
	}
	echo json_encode($array);
?>