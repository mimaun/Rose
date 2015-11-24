<?php
if (!isset($_COOKIE["username"])) {
	header('Location:Login.php');
}
?>

<!DOCTYPE html>
<!-- Michael Laritz -->
<html>
	<head>
		<title>connectParkour</title>
		<meta chartype="utf-8" />

		<!-- read jQuery and jQueryUI. -->
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
		<script src="//code.jquery.com/ui/1.11.0/jquery-ui.js"></script>

		<!-- read bootstrap. -->
		<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css" />

		<!-- read local files. -->
		<link rel="stylesheet" href="event.css" />
		<script src="upload.js"></script>
	</head>
	<body>

		<?php
		include "header.html";
		?>
		<div class="frame">
		<?php
		$target_dir = "EventImages/";
		$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
		$uploadOk = 1;
		$imageFileType = pathinfo($target_file, PATHINFO_EXTENSION);
		// Check if image file is a actual image or fake image
		if (isset($_POST["submit"])) {
			$check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
			if ($check !== false) {
				//echo "File is an image - " . $check["mime"] . ".";
				$uploadOk = 1;
			} else {
				//echo "File is not an image.";
				$uploadOk = 0;
			}
		}
		// Check if file already exists
		if (file_exists($target_file)) {
			$length = strlen($imageFileType);
			$lengthOfPath = strlen($target_file);
			$substrlength = $lengthOfPath - $length;
			$substr = substr($target_file, 0, $substrlength);
			while(file_exists($target_file)){
				$substr = $substr . "1";
				$target_file = $substr . $imageFileType;
			}
			$uploadOk = 1;
		}
		// Check file size
		if ($_FILES["fileToUpload"]["size"] > 500000) {
			echo "Sorry, your file is too large.";
			$uploadOk = 0;
		}
		// Allow certain file formats
		if ($imageFileType != "JPG" && $imageFileType != "jpg" && $imageFileType != "PNG" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "JPEG" && $imageFileType != "gif" && $imageFileType != "GIF") {
			echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
			$uploadOk = 0;
		}
		// Check if $uploadOk is set to 0 by an error
		if ($uploadOk == 0) {
			echo "Sorry, your file was not uploaded.";
			// if everything is ok, try to upload file
		} else {
			if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
				echo "The file " . basename($_FILES["fileToUpload"]["name"]) . " has been uploaded.";
			} else {
				echo "Sorry, there was an error uploading your file.";
			}
		}
		$ampm = $_POST["ampm"];
		
		if($_POST["hour"]==12){
			$hour = 0 + $ampm;
		}else{
			$hour = $_POST["hour"] + $ampm;
		}
		$minute = $_POST["minute"];
		$year = $_POST["year"];
		$month = $_POST["month"];
		$day = $_POST["day"];

		$username = "brinegjr";
		$password = "abcde";
		// Create connection
		$conn = new PDO('mysql:host=localhost;dbname=brinegjr', $username, $password);
		// Check connection
		// if ($conn -> connect_error) {
		// die("Connection failed: " . $conn -> connect_error);
		// }

		$EventNamev = $conn -> quote($_POST["eventName"]);
		$Cityv = $conn -> quote($_POST["eventCity"]);
		$Statev = $conn -> quote($_POST["eventState"]);
		$Statev = explode("\\", $Statev);
		$Statev = $Statev[0];
		$Zipcodev = $conn -> quote($_POST['zipcode']);
		$PostedByv = $conn -> quote($_COOKIE['username']);
		$Pathv = $conn -> quote($target_file);
		$date = $year . "-" . $month . "-" . $day . " " . $hour . ":" . $minute . ":00";
		$Datev = $conn -> quote($date);
		//$str="YYYY-MM-DD JJ:MM:SS"
		$Typev = $conn -> quote($_POST["in_out"] + 0);
		if($_POST["in_out"] + 0 == 0){
			$type="Outdoor";
		}else{
			$type="Indoor";
		}

		//($Idv, $EventNamev, $Cityv, $Statev, $PostedByv, $Pathv, $Datev, $Typev);

		$sql = "INSERT INTO `Events` (`EventName`,`City`,`State`, `Zipcode`, `PostedBy`,`Path`,`Date`,`Type`) VALUES (" . $EventNamev . ", " . $Cityv . ", " . $Statev . "', " . $Zipcodev . ", ". $PostedByv . ", " . $Pathv . ", " . $Datev . ", " . $Typev . ")";
		$query = "INSERT INTO `EventsForUser` (`EventName`, `Username`) VALUES (" . $EventNamev . ", " . $PostedByv . ")";
		//
		// if ($conn -> query($sql) === TRUE) {
		// echo "New record created successfully";
		// } else {
		// echo "Error: " . $sql . "<br>" . $conn -> error;
		// }
		$conn -> query($sql);
		$conn->query($query);
		
	?>
	</div>
	<div class="frame">
		<h2>Event Added</h2>
		<p>Name of Event: <?= $_POST["eventName"] ?></p>
		<p>City: <?= $_POST["eventCity"] ?></p>
		<p>State: <?= $_POST["eventState"] ?></p>
		<p>Zipcode: <?= $_POST['zipcode'] ?></p>
		<p>Posted By: <?= $_COOKIE['username'] ?></p>
		<p>Date(YYYY-MM-DD HH:MM:SS): <?= $date ?></p>
		<p>Type: <?= $type ?></p>
		<?php
		if(strlen($Pathv) > strlen("EventImages/")){
			?>
			<p>Picture: <img src=<?= $Pathv ?> alt="Missing Picture" /></p>
			<?php
		}
		$conn -> close();
		?>
	</div>
	
	</body>
</html>
