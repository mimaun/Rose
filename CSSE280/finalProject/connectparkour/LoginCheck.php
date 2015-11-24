<?php
	$username = "brinegjr";
	$password = "abcde";
	$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
	$existingUser = $_GET["username"];
	$existingPass = $_GET["password"];
	$query = "SELECT `Username`, `Password` FROM `Users` WHERE `Username`='" . $existingUser . "' and `Password`='" . $existingPass . "'";
	$stmt = $conn->query($query);
	$row = $stmt->fetch();
	if($row['Username'] == $existingUser && $row['Password'] == $existingPass){
		echo "true";
	} else {
		echo "false";
	}
	
	function failedToConnect(){
		echo "conect to database failed";
	}
?>
