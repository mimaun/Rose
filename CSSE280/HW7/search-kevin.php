<?

include("common.php");
include("top.html");

?>
    <h1>Results for <?=$first_name?> <?=$last_name?> with Kevin Bacon</h1>
<?
// find actor.
if(isFindActor()) {

    try {
        // get result.
        $rows_withKevin = $db->query(getQueryWithKevin());

        // found movies with Kevin, create table.
        if($rows_withKevin->rowCount() > 0) {
?> 
    <p>Movies with <?=$first_name?> <?=$last_name?> and Kevin Bacon in them.</p>
    <table id="result">
        <tr><th>#</th><th>Title</th><th>Year</th></tr>
<?
            $i = 1;
            foreach($rows_withKevin as $row) {
?>
            <tr><td><?=$i?></td><td><?=$row['name']?></td><td><?=$row['year']?></td></tr>
<?
                $i += 1;
            }
?>
    </table>
<?
        }

        // found actors, but no movies with Kevin..
        else {
?>
    <p><?=$first_name?> <?=$last_name?> wasn't on any films with Kevin Bacon.</p>
<?
        } 
    } 
    // exception happened.
    catch(PDOException $ex) {
?>
    <p>Actor <?=$first_name?> <?=$last_name?> not found.</p>
<?
    } 
}

// no actors.
else {
?>
    <p>Actor <?=$first_name?> <?=$last_name?> not found.</p>
<?
} 

?>

<?
include("bottom.html"); 
?>


