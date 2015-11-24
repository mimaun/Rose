"use Strict";

$("#logout").click(logout);
$("#search").addClass("active");

$("#namebutton").click(function (){
	$.ajax("SearchAction.php", {
		type:"GET",
		data: {"type": "name", "searchBy": $("#namesearch").val()},
		datatype:"json"
	}).done(populateResults).fail(failed);
});

$("#locationbutton").click(function (){
	$.ajax("SearchAction.php", {
		type:"GET",
		data: {"type": "location", "searchBy": $("#locationsearch").val()},
		datatype:"json"
	}).done(populateResults).fail(failed);
});

$("#userbutton").click(function (){
	$.ajax("SearchAction.php", {
		type:"GET",
		data: {"type":"PostedBy", "searchBy":$("#usersearch").val()},
		datatype:"json"
	}).done(populateResults).fail(failed);
});



function failed(){
	alert("Failed");
}

function populateResults(data){
	parsedData = JSON.parse(data);
	$("#searchresults").html("");
	for(var i = 0; i < parsedData.length; i++){
		var row = $("<div class='row searchelement'>");
		var image = $("<div class='col-xs-offset-3 col-xs-3 imageplace'>");
		image.append("<img src='" + parsedData[i].Path + "' alt='Pic' height='150px' width='200px'/>");
		var resultinfo = $("<div class='col-xs-2 resultinfo'>");
		resultinfo.append("<li class='eventname'>" + parsedData[i].Eventname + "</li>");
		resultinfo.append("<li>" + parsedData[i].City + ", " + parsedData[i].State + "</li>");
		resultinfo.append("<li>" + parsedData[i].Date + "</li>");
		var type;
		if(parsedData[i].Type == "1"){
			type = "Inside";
		} else {
			type = "Outside";
		}
		resultinfo.append("<li>" + type + "</li>");
		resultinfo.append("<li>Posted By: " + parsedData[i].PostedBy + "</li>");
		row.append(image);
		row.append(resultinfo);
		
		var button = $("<button class='btn btn-primary btn-medium join'>");
		button.append("Join");
		row.append(button);
		$("#searchresults").append(row);
	}
	
	$(".join").click(function (){
		console.log($(this).closest(".searchelement").children(".resultinfo").children(".eventname").html());
		$.ajax("Join.php", {
			type:"POST",
			data: {"EventName":$(this).closest(".searchelement").children(".resultinfo").children(".eventname").html()},
			datatype:"json"
		}).done(afterJoin).fail(failed);
	});
}

function afterJoin(){
	window.location = "home.php";
}

function logout(){
	console.log("into logout");
	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
	window.location = "Login.php"; 
}
