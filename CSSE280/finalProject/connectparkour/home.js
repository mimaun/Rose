// onload.
var count = 0;
$(function() {
	
	$("#home").addClass("active");

	$("#logout").click(logout);
	
	$.ajax("getEventInfoUser.php", {
		type:"GET",
		datatype:"json"
	}).done(fillEvents).fail(failed);
	
	
	$.ajax("getUserZipcode.php", {
		type:"GET",
		datatype:"json"
	}).done(getNearbyCodes);
	
	
});

function getNearbyCodes(data){
	var parsedData = JSON.parse(data);
	var zipcode = parsedData[0];
	zipcode = "" + zipcode;
	var url = "http://api.geonames.org/findNearbyPostalCodesJSON?";
	$.ajax(url, {
		type:"GET",
		data: {"postalcode":zipcode, "country":"US", "radius":30, "username":"brinegjr"},
		datatype:"json"
	}).done(processNearbyCodes);
}

function processNearbyCodes(data){
	for(var i = 0; i < data.postalCodes.length; i++){
		$.ajax("searchForEventsByZip.php", {
			type:"GET",
			data: {"zipcode":data.postalCodes[i].postalCode},
			datatype:"json"
		}).done(function(newData){
			parsedData = JSON.parse(newData);
			var maindiv = $("#localMenu");
			for(var j = 0; j < parsedData.length; j++){
				maindiv.append("<div class='localevent'><p id='eventname" + count + "'>" + parsedData[j].EventName + "</p><p></br>" + parsedData[j].City + ", " + parsedData[j].State + "</br>Posted by: " + parsedData[j].PostedBy + "</br>" + parsedData[j].Date);
				maindiv.append("<button id='" + count + "' class='btn btn-primary btn-medium join' onclick='join(this)'>Join</button>");
				count++;
			}
		});
	}
}

function join(element){
	var idname = "eventname" + element.id;
	console.log($("#" + idname).html());
	$.ajax("Join.php", {
			type:"POST",
			data: {"EventName":$("#" + idname).html()},
			datatype:"json"
		}).done(afterJoin).fail(failed);
}

function showEvent() {

    $(this).next().slideToggle();
}

function login(){
	window.location.href = "Login.php";
} 

function logout(){
	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
	window.location.href = "Login.php";
}

function fillEvents(data){
	parsedData = JSON.parse(data);
	var eventmenu = $("#eventMenu");
	for(var i = 0; i < parsedData.length; i++){
		var dt = $("<dt>");
		dt.append(parsedData[i].EventName + " " + parsedData[i].Date);
		var dd = $("<dd>");
		var divrow = $("<div class='row'>");
		var divcol = $("<div class='col-xs-3'>");
		var image = "<img src='" + parsedData[i].Path + "' alt='Pic' style='height:98px;width=100px;'/>";
		divcol.append(image);
		var divcol2 = $("<div class='col-xs-4'>");
		var p = $("<p>");
		p.append(parsedData[i].City + ", " + parsedData[i].State);
		divcol2.append(p);
		var divcol3 = $("<div clas='col-xs-4'>");
		p = $("<p>");
		var type = "";
		if(parsedData[i].Type = 0){
			type = "Outside";
		} else { 
			type = "Inside"; 
		}
		p.append("Event scheduled by: <a href='aboutme.php?username=" + parsedData[i].PostedBy + "'>"+ parsedData[i].PostedBy + "</a><br> Type: " + type);
		divcol3.append(p);
		divrow.append(divcol);
		divrow.append(divcol2);
		divrow.append(divcol3);
		dd.append(divrow);
		eventmenu.append(dt);
		eventmenu.append(dd);
	}
	$("#eventMenu dt").click(showEvent);
}

function failed(){
	alert("failed to load events");
}

function afterJoin(){
	window.location = "home.php";
}
