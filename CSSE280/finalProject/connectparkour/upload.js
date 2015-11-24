"use strict";

$("#logout").click(function() {
	document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC";
	window.location.href = "Login.php";
});
