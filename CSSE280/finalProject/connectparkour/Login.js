"use strict";

var existingUsername = "";
var existingPassword = "";

function registerUser(){
	var username = $("#desireduser").val();
	var password = $("#desiredpass").val();
	var zipcode = $("#zipcode").val();
	$.ajax("Registration.php", {
		"type": "POST",
		"data": {"user": username, "pass": password, "zipcode":zipcode},
		"datatype": "json"
	}).fail(failed);
}

function checkUser(){
	existingUsername = $("#user").val();
	existingPassword = $("#pass").val();
	$.ajax("LoginCheck.php", {
		"type": "GET",
		"data": {"username": existingUsername, "password": existingPassword},
		"datatype": "text"
	}).done(processUser).fail(loginFailed);
}

function processUser(data){
	if(data == "true"){
		document.cookie = "username=" + existingUsername + ";";
		window.location = "home.php";
	} else {
		$("#errorspot").html("");
		$("#errorspot").append("<p style='color:white'>Username or password was incorrect.  Please try again.</p>");
	}
}

function loginFailed(xhr, status, exception){
	console.log(exception);
}

function failed(){
	$("#errorspot2").html();
	$("#errorspot2").append("Registration failed. Please try again");
}
