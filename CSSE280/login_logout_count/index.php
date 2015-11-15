<?php
session_start();
if(isset($_SESSION)) {
    session_unset();
    session_destroy();
}

session_start();
?>
<!DOCTYPE html">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>login logout system </title>
		<link rel="stylesheet" type="text/css" href="style.css" />
	</head>

	<body>
		<h2> Some pre-defined usernames and passwords:</h2>
		<h4> Username : tom  &nbsp; &nbsp; &nbsp; &nbsp; Password : tom </h4>
		<h4> Username : huck  &nbsp; &nbsp; &nbsp; &nbsp; Password : huck </h4>
		<h4> Username : becky  &nbsp; &nbsp; &nbsp; &nbsp; Password : becky </h4>

		<div class="contain">
			<form method="post" name="login" action="login.php">
				<label for="name" class="labelname"> Username </label>
				<input type="text" name="username" id="userid" required="required" />
				<br />
				<label for="name" class="labelname"> Password </label>
				<input type="password" name="password" id="passid" required="required"  />
				<br />
				<input type="submit" name="submit" id="submit"  value="Login" />
			</form>
		</div>

		<p>
			This is site is a hybrid of code from <a href="http://www.2my4edge.com/2013/07/simple-login-logout-system-using-php.html">2my4edge.com</a>
			and <a href="http://www.webstepbook.com/supplements-2ed/codefiles/ch14-cookies-sessions-files.zip">Web Programming, Step by Step<a>.  
			<br />	Blended, shaped, and enhanced for CSSE 280/290 by Claude Anderson at Rose-Hulman Institute of Technology.
	</body>
</html>
