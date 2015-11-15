$(function () {
	$("#ChangeContent").click(loadDoc);
	$("#UsejQuery").click(loadDocjQuery);
	$("#UseLoad").click(loadDocjQueryLoad);
	$("#booklinks a").click(function (e) {
		var url = $(this).attr('href');
		// $('#result').load(url + " " + url.substring(url.indexOf("#")));
		$('#result').load("books.html" + " " + url.substring(url.indexOf("#")));
        console.log(url + " " + url.substring(url.indexOf("#")));
		e.preventDefault();
	});
});


function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      document.getElementById("demo").innerHTML = xhttp.responseText;
    }
  };
  xhttp.open("GET", "ajax_info.txt", true);
  xhttp.send();
}

function loadDocjQuery() {
	console.log("function called");
	$.ajax({
    	"url": "ajax_info2.txt",
    	"type": "GET",
    	"success": myAjaxSuccessFunction,
    	"error": ajaxFailure
    });
}

function myAjaxSuccessFunction(data) {
   	console.log(" success function called");
   	console.log(data);

    $("#demo").html(data);
}
function ajaxFailure(xhr, status, exception) {
    console.log(xhr, status, exception);
}

function loadDocjQueryLoad() {
	$("#demo").load("ajax_info3.txt");
}



