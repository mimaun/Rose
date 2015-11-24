<?php
if (!isset($_COOKIE['username'])) {
	header("Location:Login.php");
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
		<link rel="stylesheet" href="SearchStyle.css"/>
	</head>

	<body>

		<div id="fixed">
			<?php
			include "header.html";
			?>
			
		</div>
		
		<div class="wrap">
			<div class="wraprow">
				<div class="row">
					<div class="col-xs-offset-4 col-xs-1 text-right">
						<label for="searchname">Name: </label>
					</div>
					<div class="col-xs-2">
						<input id="namesearch" class="textbox" name="searchname" type="text" value="" placeholder="Enter name of event" />
					</div>
					<div class="col-xs-1">
						<button id="namebutton" class="btn btn-primary btn-med searchbutton" type="button">
							Search
						</button>
					</div>
				</div>
			</div>
			<p>
				Or
			</p>
			<div class="wraprow">
				<div class="row">
					<div class="col-xs-offset-4 col-xs-1 text-right">
						<label for="searchlocation">Location: </label>
					</div>
					<div class="col-xs-2">
						<input id="locationsearch" class="textbox" name="searchlocation" type="text" value="" placeholder="Enter location in format 'City, State'" />
					</div>
					<div class="col-xs-1">
						<button id="locationbutton" class="btn btn-primary btn-med searchbutton" type="button">
							Search
						</button>
					</div>
				</div>
			</div>
			<p>
				Or
			</p>
			<div class="row">
				<div class="col-xs-offset-4 col-xs-1 text-right">
					<label for="searchuser">Posted By: </label>
				</div>
				<div class="col-xs-2">
					<input id="usersearch" class="textbox" name="searchuser" type="text" value="" placeholder="Enter a username" />
				</div>
				<div class="col-xs-1">
					<button id="userbutton" class="btn btn-primary btn-med searchbutton" type="button">
						Search
					</button>
				</div>
			</div>
		</div>

		<div id="searchresults">
			
		</div>

		<!--<script src="jquery-1.11.3.js"></script>
		<script src="//code.jquery.com/ui/1.11.0/jquery-ui.js"></script>
		<script src="bootstrap-4.0.0-alpha/dist/js/bootstrap.min.js"></script>-->
		<script src="Search.js"></script>
	</body>

</html>
