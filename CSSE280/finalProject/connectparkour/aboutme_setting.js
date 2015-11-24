"use strict";

var state = "AL"; 
var city = ""; 



$(function() { 
	
	$("#logout").click(function (){
	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
	window.location.href = "Login.php";
	});

    // get state information from State.txt .
    $.get("States.txt", function(data) {
        var stateArr = data.split("\n");

        $.each(stateArr, function(i, val) {
            var stateOpt = $("<option>");
            stateOpt.html(val);
            $("#state").append(stateOpt);
        });
    }); 

    // append list of city in AL to option.
    getCityList();

    getUserInformation();

    // user selected the state.
    $("#state").change(function() { 
        state = $(this).val();
        getCityList();
    });

    // user selected the city.
    $("#city").change(function() {
        city = $(this).val();
    });

    // after user pushed submit button, register information to database.
    $("#submitButton").click(function() {
        var ex = $("TEXTAREA#experience").val();
        var about = $("TEXTAREA#aboutme").val();
        console.log(ex);
        console.log(about);
        registerInformation(city, state, ex, about);
    });
});

/*
 * Get City List from mySQL.
 *
 * Script: GetCity.php
 * Table: cities
 * */
function getCityList() { 

    $.ajax({
        "url" : "./GetCity.php",
        "type" : "POST",
        "data" : {
            "state" : state
        },
        "dataType" : "json",
        "success" : function(data, dataType) {

            if(data == null) {
                console.log("city data is empty");
                return;
            }

            console.log("success");
            // reset option.
            $("#city option").remove();

            // append city option.
            for(var i = 0; i < data.length; i++) {
                var cityOpt = $("<option>");
                cityOpt.html(data[i].city);
                $("#city").append(cityOpt);
            }

            // init.
            city = data[0].city;
        },
        "error" : function(xhr, textStatus, errorThrown) {
            console.log("ajax error: " + errorThrown);
            console.log("textStatus: " + textStatus);
            console.log("req: " + xhr.URL);
        }
    }); 

}

function getUserInformation() {

    // get username from cookie.
    var cookies = document.cookie;
    var username = "";
    if(cookies.length > 0) {
        var st = cookies.indexOf("username=");
        if(st != -1) {
            st = st + "username".length + 1;
            var ed = cookies.indexOf(";",st);
            if(ed == -1) ed = cookies.length;
            username = unescape(cookies.substring(st,ed));
        }
    }

    $.ajax({
        "url" : "./getUserProfile.php",
        "type" : "POST",
        "data" : username,
        "dataType" : "json",
        "success" : function(data, dataType) {

            if(data == null) {
                console.log("city data is empty");
                return;
            }

            console.log("success");
            console.log(data[0].experience);
            console.log(data[0].aboutme);
            console.log("success");

            $("#experience").val(data[0].experience);
            $("TEXTAREA#aboutme").val(data[0].aboutme);
        },
        "error" : function(xhr, textStatus, errorThrown) {
            console.log("ajax error: " + errorThrown);
            console.log("textStatus: " + textStatus);
            console.log("req: " + xhr.URL);
        }
    }); 
}

function registerInformation(city, state, experience, aboutme) {

    $.ajax({
        "url" : "./registerProfile.php",
        "type" : "POST",
        "data" : {
            // "username", username,
            "city" : city,
            "state" : state,
            "experience" : experience,
            "aboutme" : aboutme
        },
        // "dataType" : "json",
        "success" : function(response) {

            console.log(response);
        },
        "error" : function(xhr, textStatus, errorThrown) {
            console.log("ajax error: " + errorThrown);
            console.log("textStatus: " + textStatus);
            console.log("req: " + xhr.URL);
        }
    }); 

    window.location.href = "./aboutme.php"; 
}

