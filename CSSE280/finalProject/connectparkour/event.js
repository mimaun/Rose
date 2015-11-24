"use strict";
var list;
var stateSection
$("#event").addClass("active");

window.onload = function() {
	list = document.getElementsByTagName("p");

	stateSection = document.getElementById("eventState");

	
	
	$("#logout").click(function(){
	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
	window.location.href = "Login.php";
	});

};
