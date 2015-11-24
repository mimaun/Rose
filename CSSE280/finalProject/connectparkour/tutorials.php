<?php
	if(!isset($_COOKIE["username"])){
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
        
        <link rel="stylesheet" type="text/css" href="aboutme.css">
        <link rel="stylesheet" type="text/css" href="tutorials.css">
	</head>
	<body>
		
        <?php
        include "header.html";
        ?>


        


		<div>
			<h1>Tutorials</h1>
			<?php
			$username = "brinegjr";
			$password = "abcde";
			$conn = new PDO("mysql:host=localhost;dbname=brinegjr", $username, $password);
			$array = ["Kong Vault", "Dash Vault", "Side Flip", "Cheat Gainer"];
			for($i = 0; $i < count($array); $i++){
				$move = $conn->quote($array[$i]);
				$query = "SELECT `Link` FROM `Tutorials` WHERE `Move`=" . $move;
				$stmt = $conn->query($query);
				echo "<h2>" . $array[$i] . "</h2>";
				while($row = $stmt->fetch()){
					echo $row['Link'];
				}
			}
			?>
			<img id="mashup" src="image/mashup.png" alt="Unable to load photo" />
		</div>
		
		<script type="text/javascript" src="tutorials.js"></script>
	</body>
</html>