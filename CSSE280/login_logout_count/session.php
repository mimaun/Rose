<?

include "db.php";
session_start();

$check = $db->quote($_SESSION["name"]);
$query_count_text = "select count(*) from login where name=$check;";
$count = $db->query($query_count_text);

?>
