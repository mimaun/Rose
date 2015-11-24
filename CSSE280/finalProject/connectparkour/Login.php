<?php
	if(isset($_COOKIE["username"])){
		header('Location:home.php');
	}
?>

<!DOCTYPE HTML>
<html>
	<head>
		<meta charset="UTF-8"/>
		<title>connectParkour</title>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
     	<script src="//code.jquery.com/ui/1.11.0/jquery-ui.js"></script>
     	
		<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css" />
		<link rel="stylesheet" href="loginStyle.css"/>
	</head>

	<body>

		<div id="tophalf">
			<div class="row">
				<div class="col-xs-offset-4 col-xs-2 text-right">
					<p class="logintitle">
						<u>Log in:</u>
					</p>
				</div>
			</div>
			<div class="loginboxes">

				<div class="row">
					<div class="col-xs-offset-6 col-xs-1 text-right">
						<label for="username">Username: </label>
					</div>
					<div class="col-xs-1">
						<input id="user" name="username" type="text" value="" placeholder="Enter Username"/>
					</div>
				</div>
				<div class="row">
					<div class="col-xs-offset-6 col-xs-1 text-right">
						<label for="password">Password: </label>
					</div>
					<div class="col-xs-1">
						<input id="pass" name="password" type="password" value="" placeholder="Enter Password"/>
					</div>
				</div>
				<div class="row">
					<div class="col-xs-offset-6 col-xs-2">
						<button onclick="checkUser()" type="button" class="btn btn-primary btn-large pull-right">
							Log in
						</button>
						<div id="errorspot">
							
						</div>
					</div>
				</div>
				<img id="logo" src="image/logo.png" height="150px" width="800px"/>
			</div>
		</div>

		<div class="row">
			<div class="col-xs-offset-4 col-xs-2 text-right">
				<p class="logintitle">
					<u>Register:</u>
				</p>
			</div>
		</div>
		<div class="loginboxes">
			<div class="row">
				<div class="col-xs-offset-6 col-xs-1 text-right">
					<label for="newuser">New Username: </label>
				</div>
				<div class="col-xs-1">
					<input id="desireduser" name="newuser" type="text" value="" placeholder="Enter desired username" />
				</div>
			</div>
			<div class="row">
				<div class="col-xs-offset-6 col-xs-1 text-right">
					<label for="newpass">New Password: </label>
				</div>
				<div class="col-xs-1">
					<input id="desiredpass" name="newpass" type="password" value="" placeholder="Enter desired password" />
				</div>
			</div>
			<div class="row">
				<div class="col-xs-offset-6 col-xs-1 text-right">
					<label for="zipcode">Zipcode: </label>
				</div>
				<div class="col-xs-1">
					<input id="zipcode" name="zipcode" type="text" value="" placeholder="Enter desired password" />
				</div>
			</div>
			<div class="row">
				<div class="col-xs-offset-6 col-xs-2">
					<button onclick="registerUser()" type="button" class="btn btn-primary btn-large pull-right">
						Register
					</button>
				</div>
				<div id="errorspot2">
					
				</div>
			</div>
		</div>

		<script src="Login.js"></script>
	</body>
</html>
