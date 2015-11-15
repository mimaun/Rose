<?php
include ("session.php");
?>

<!DOCTYPE html>
<html>
	<head>
		<meta content="text/html charset=utf8">
		<title>User profile</title>
	</head>
	<body>
		<h2> Hello, <?= $login_session ?></h3>
		<h3> Welcome to "Log you in"</h2>
		<h3> Click <a href="logout.php">here</a> to logout</h2>
		<h3> Return to 
			<a href="http://www.rose-hulman.edu/class/csse/csse290-WebProgramming/201520/Schedule/Schedule.htm#session26">Course schedule page</a>
		</h3>
	</body>
	
</html>