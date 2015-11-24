<?php
$username = "brinegjr";
$password = "abcde";
$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);

if (isset($_GET["type"])) {
	$type = $_GET["type"];
	if ($type == "name") {
		$searchBy = $conn->quote($_GET["searchBy"]);
		$query = "SELECT `EventName`, `City`, `State`, `Type`, `Path`, `PostedBy`, `Date` FROM `Events` WHERE `EventName`=" . $searchBy . " ORDER BY `Date`";
		$stmt = $conn->query($query);
		if(!$stmt){
			print_r($conn->errorInfo());
		}
		else{
			$wholeArray = array();
			while ($row = $stmt->fetch()) {
				$array = array('Eventname' => $row['EventName'], 'City' => $row['City'], 'State' => $row['State'], 'Type' => $row['Type'], 'Path' => $row['Path'], 'PostedBy' => $row['PostedBy'], 'Date' => $row['Date']);
				array_push($wholeArray, $array);
			}
			echo json_encode($wholeArray);
		}
	} else if ($type == "location") {
		$searchBy = $_GET['searchBy'];
		$searchArr = explode(", ", $searchBy);
		$searchArr = array_map("strval", $searchArr);
		$city = $searchArr[0];
		$state = $searchArr[1];
		$query = "SELECT `EventName`, `City`, `State`, `Type`, `Path`, `PostedBy`, `Date` FROM Events WHERE `City`='" . $city . "'" . " AND `State`='" . $state . "' ORDER BY `Date`";
		$stmt = $conn->query($query);
		if (!$stmt) {
			print_r($conn->errorInfo());
		} else {
			$wholeArray = array();
			while ($row = $stmt->fetch()) {
				$array = array('Eventname' => $row['EventName'], 'City' => $row['City'], 'State' => $row['State'], 'Type' => $row['Type'], 'Path' => $row['Path'], 'PostedBy' => $row['PostedBy'], 'Date' => $row['Date']);
				array_push($wholeArray, $array);
			}
			echo json_encode($wholeArray);
		}
	} else if ($type == "PostedBy"){
		$searchBy = $_GET["searchBy"];
		$searchBy = $conn->quote($searchBy);
		$query = "SELECT `EventName`, `City`, `State`, `Type`, `Path`, `PostedBy`, `Date` FROM Events WHERE `PostedBy`=" . $searchBy . " ORDER BY `Date`";
		$stmt = $conn->query($query);
		if(!$stmt){
			print_r($conn->errorInfo());
		}
		else{
			$wholeArray = array();
			while ($row = $stmt->fetch()) {
				$array = array('Eventname' => $row['EventName'], 'City' => $row['City'], 'State' => $row['State'], 'Type' => $row['Type'], 'Path' => $row['Path'], 'PostedBy' => $row['PostedBy'], 'Date' => $row['Date']);
				array_push($wholeArray, $array);
			}
			echo json_encode($wholeArray);
		}
	}
}
?>