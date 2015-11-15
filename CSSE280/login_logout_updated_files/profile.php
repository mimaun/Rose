<?php
include ("session.php");

// from stackoverflow.com/questions/69262/is-there-an-easy-way-in-net-to-get-st-nd-rd-and-th-endings-for-number/69284#69284
function ordinal($num) {  
    $ones = $num % 10;
    $tens = floor($num / 10) % 10;
    if ($tens == 1) {
        $suff = "th";
    } else {
        switch ($ones) {
            case 1 : $suff = "st"; break;
            case 2 : $suff = "nd"; break;
            case 3 : $suff = "rd"; break;
            default : $suff = "th";
        }
    }
    return $num . $suff;
}
?>

<!DOCTYPE html>
<html>
	<head>
		<meta content="text/html charset=utf8">
		<title>User profile</title>
	</head>
	<body>
		<h2> 
			Hello, <?= $login_session ?>, your ID# is <?= $login_id ?> <br />
			This is your <?= ordinal($login_visits) ?> visit to this site.
		</h2>
		<h3> Welcome to "Log you in"</h3>
		<h3> Click <a href="logout.php">here</a> to logout</h3>
		<h3> Return to 
			<a href="http://www.rose-hulman.edu/class/csse/csse280/201610/Schedule/Schedule.htm#session26">Course schedule page</a>
		</h3>
	</body>
	
</html>