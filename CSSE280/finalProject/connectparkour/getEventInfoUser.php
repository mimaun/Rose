<?php
$username = "brinegjr";
$password = "abcde";
$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);

$username = $conn->quote($_COOKIE['username']);
$query = "SELECT e.EventName, e.Date, e.Type, e.City, e.State, e.PostedBy, e.Path
FROM Events e, (SELECT `EventName` FROM `EventsForUser` WHERE `Username` = " . $username . ") k 
WHERE e.EventName = k.EventName ORDER BY e.Date";
$stmt = $conn->query($query);
$wholeArray = array();
while($row = $stmt->fetch()){
	$array = array("EventName" => $row['EventName'], "Date" => $row['Date'], "Type" => $row['Type'], "City" => $row['City'], 
	"State" => $row['State'], "PostedBy" => $row['PostedBy'], "Path" => $row['Path']);
	array_push($wholeArray, $array);
}
echo json_encode($wholeArray);
?>