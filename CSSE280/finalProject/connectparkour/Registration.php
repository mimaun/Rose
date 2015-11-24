<?php
try{
	$username = "brinegjr";
	$password = "abcde";
	$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
	
	$userToEnter = null;
	$passToEnter = null;
	if(isset($_POST["user"])){
		$userToEnter = $_POST["user"];
		$userToEnter = explode(" ", $userToEnter);
		$userToEnter = $userToEnter[0];
	}
	if(isset($_POST["pass"])){
		$passToEnter = $_POST["pass"];
		$passToEnter = explode(" ", $passToEnter);
		$passToEnter = $passToEnter[0];
	}
	$zipcode = $_POST['zipcode'];
	if($userToEnter != null && $passToEnter != null){
		$query = "INSERT INTO `Users`(`Username`, `Password`, `City`, `State`, `Zipcode`, `Experience`, `AboutMe`) VALUES (:username,:password,NULL,NULL, :zipcode,NULL,NULL)";
		$stmt = $conn->prepare($query);
		$stmt->bindParam(':username', $userToEnter, PDO::PARAM_STR);
		$stmt->bindParam(':password', $passToEnter, PDO::PARAM_STR);
		$stmt->bindParam(':zipcode', $zipcode, PDO::PARAM_STR);
		$stmt->execute();
		echo "query about to run";
		
	} else {
		echo $userToEnter . " " . $passToEnter;
	}
}
catch (Exception $e){
	echo "in catch";
	echo $e->getMessage();
}
	
	function failedToConnect(){
		echo "conect to database failed";
	}
?>
