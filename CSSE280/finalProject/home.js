"use strict";

// onload.
$(function() {

    $("#eventMenu dt").click(showEvent); 
    $("#loginButton").click(function() {
        window.location.href = "Login.php";
    }); 

});

function showEvent() {

    console.log("showEvent");

    $(this).next().slideToggle();
}


