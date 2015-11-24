$(function(){
    $("#settingButton").click(function() {
        console.log("Hello");
        window.location.href = "aboutme_setting.php";
    });
    
    $("#logout").click(function(){
    	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
		window.location = "Login.php";
    });
    
    $("#aboutme").addClass("active");

    var username = $("#username").text();

    $.ajax({
        "url" : "./getUserProfile.php",
        "type" : "POST",
        "data" : {
            "username" : username
        },
        "dataType" : "json",
        "success" : function(data, dataType) {

            if(data == null) {
                console.log("city data is empty");
                return;
            }

            console.log("success");
            console.log(data[0].city);
            console.log(data[0].state);
            console.log(data[0].experience);
            console.log(data[0].aboutme);
            
            // show data.
            $("#city").text(data[0].city);
            $("#state").text(data[0].state); 
            $("#experience").val(data[0].experience);
            $("TEXTAREA#aboutme").val(data[0].aboutme);
        },
        "error" : function(xhr, textStatus, errorThrown) {
            console.log("ajax error: " + errorThrown);
            console.log("textStatus: " + textStatus);
            console.log("req: " + xhr.URL);
        }
    }); 
});
