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
        <script type="text/javascript" src="event.js"></script>
        <link rel="stylesheet" type="text/css" href="event.css">
	</head>
	<body>
		
       	<?php
       	include "header.html";
       	?>


        


        <div class="frame">
		<div>
			<h2>Add Event</h2> <br>
		</div>
		<div>
			<p>Required *</p>
		</div>
		
		
		<form id="form1" name="form1" method="post" action="upload.php"  enctype="multipart/form-data">
			<p>
				<label>Name of Event*
					<input name="eventName" type="text" id="eventName" value="" required="required"/>
				</label>
			</p>
			<p>
				<label>City*
					<input name="eventCity" type="text" id="eventCity" value="" required="required"/>
				</label>
				
			</p>
			<p>
				<label>State*
				<select id="eventState" name="eventState" >
						<?php
						$file_lines = file("StateList.txt");  # array of lines from the file.
						foreach($file_lines as $line) {
						?>
							<option value="<?="$line" ?>"><?=$line ?></option>
						<?php
						}
						?>
				</select>
				</label>
			</p>
			<p>
				<label>Zipcode*
					<input name="zipcode" type="text" id="zipcode" value="" required="required"/>
				</label>
				
			</p>
			<p>
				<label>Date*
					<select id="month" name="month" >
						<?php
						for ($i=1; $i <= 12; $i++) {
							if($i < 10){
								$temp = "0" . $i;
								?> 
								<option value="<?="$temp" ?>"><?=$temp ?></option>
							<?php
							}else{
							?> 
								<option value="<?="$i" ?>"><?=$i ?></option>
							<?php
							}
						} 
						?>
					</select>
					<select id="day" name="day">
						<?php
						for ($i=1; $i <= 31; $i++) {
							if($i < 10){
								$temp = "0" . $i;
								?> 
								<option value="<?="$temp" ?>"><?=$temp ?></option>
							<?php
							}else{
							?> 
								<option value="<?="$i" ?>"><?=$i ?></option>
							<?php
							}
						} 
						?>
					</select>
					<select id="year" name="year" >
						<?php
						for ($i=2015; $i < 2101; $i++) {
							?> 
							<option value="<?="$i" ?>"><?=$i ?></option>
							<?php
						} 
						?>
					</select>
				</label>
			</p>
			<p>
				<label>Time*
					<select id="hour" name="hour" >
						<?php
						for ($i=1; $i <= 12; $i++) {
							if($i<10){
								$temp="0" . $i;
								?> 
								<option value="<?="$temp" ?>"><?=$temp ?></option>
							<?php
							}else{
							?> 
								<option value="<?="$i" ?>"><?=$i ?></option>
							<?php
							}
						} 
						?>
					</select>
					:
					<select id="minute" name="minute" >
						<?php
						for ($i=0; $i < 60; $i++) {
							if($i<10){
								$temp="0" . $i;
								?> 
								<option value="<?="$temp" ?>"><?=$temp ?></option>
							<?php
							}else{
							?> 
								<option value="<?="$i" ?>"><?=$i ?></option>
							<?php
							}
						} 
						?>
					</select>
				</label>
				<span id="morning_afternoon">
				<label>
					<input name="ampm" type="radio" id="ampm" value="0" checked="checked" />
					am
				</label>
				<label>
					<input type="radio" name="ampm" id="ampm" value="12" />
					pm
				</label>
				</span>
			</p>
			<p>
				<label>
					<input type="radio" name="in_out" id="in_out" value="1" checked="checked" />
					indoor
				</label>
				<label>
					<input type="radio" name="in_out" id="in_out" value="0" />
					outdoor
				</label>
			</p>
			<p>
				<label>
    					Select image to upload:
    					<input type="file" name="fileToUpload" id="fileToUpload">
    					
					
				</label>
			</p>
			<p>
				<label>
					<input type="submit" name="Submit" id="Submit" value="Submit" />
				</label>
			</p>
		</form>
        <div>
		
		<script src="event.js"></script>
	</body>
</html>
