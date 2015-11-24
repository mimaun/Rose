<?php
	$username = "brinegjr";
	$password = "abcde";
	$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
	$zipcode = $conn->quote($_GET['zipcode']);
	$query = "SELECT `EventName`, `City`, `State`, `PostedBy`, `Date` FROM Events WHERE `Zipcode`=" . $zipcode . " ORDER BY `Date`";
	$stmt = $conn->query($query);
	$wholeArray = array();
	while($row = $stmt->fetch()){
		$array = array("EventName" => $row['EventName'], "City" => $row['City'], "State" => $row['State'], "PostedBy" => $row['PostedBy'], "Date" => $row['Date']);
		array_push($wholeArray, $array);
	}
	echo json_encode($wholeArray);
?>