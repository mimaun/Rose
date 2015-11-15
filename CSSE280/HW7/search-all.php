<?

include("common.php");
include("top.html"); 

?>
    <h1>Results for <?=$first_name?> <?=$last_name?></h1>
<?

// found actor (return true).
if(isFindActor()) {

    try {
        // get list of movies.
        $rows = $db->query(getQueryForAll());

        // create table.
        if($rows->rowCount() > 0) {
?> 
    <p>Movies with <?=$first_name?> <?=$last_name?> in them.</p>
    <table id="result">
        <tr><th>#</th><th>Title</th><th>Year</th></tr>
<?
            $i = 1;
            foreach($rows as $row) {
?>
            <tr><td><?=$i?></td><td><?=$row['name']?></td><td><?=$row['year']?></td></tr>
<?
                $i += 1;
            }
?>
    </table>
<?
        } 
    }  // finish try

    // something exception happen.
    catch(PDOException $ex) {
?>
    <p>Actor <?=$first_name?> <?=$last_name?> not found.</p>
<?
    } 
}

// actor is not found (return false).
else {
?>
    <p>Actor <?=$first_name?> <?=$last_name?> not found.</p>
<?
} 

?>

<?
    include("bottom.html"); 
?>



