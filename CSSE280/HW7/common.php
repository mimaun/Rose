<?php

// global variables.
$db = new PDO("mysql:dbname=imdb;host=localhost;", "morinom", "abcde");
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$actor_id = 0;

// when user put actor's name in form and push submit, method should be get. 
if($_SERVER['REQUEST_METHOD'] == 'GET') {

    $first_name = htmlspecialchars($_GET['firstname']);
    $last_name = htmlspecialchars($_GET['lastname']);

    $first_name_q = $db->quote($first_name);
    $first_name_like_q = $db->quote($first_name . ' %');
    $last_name_q = $db->quote($last_name);

}

// search whether the actor is in the database or not (return boolean).
function isFindActor () {

    global $first_name_q, $last_name_q, $first_name_like_q, $actor_id, $db;

    // at first, we should consider duplicate of actor's name.
    $actor_query_text = "
SELECT a1.id
FROM actors a1
WHERE a1.first_name LIKE $first_name_like_q
AND a1.last_name = $last_name_q
AND a1.film_count = (
SELECT MAX(a.film_count)
FROM actors a
    WHERE a.first_name LIKE $first_name_like_q
    AND a.last_name = $last_name_q
)
ORDER BY a1.id ASC
LIMIT 1
";

    try {
        $rows_actor = $db->query($actor_query_text);

        // found the actor who has duplicate.
        if ($rows_actor->rowCount () > 0) {

            foreach ($rows_actor as $row) {
                $actor_id = $row['id'];
            }
            return true;
        }

        // no duplicate. Second, we should search only one name which is in accrod on typed name.
        else {

            $actor_query_text = "
SELECT a1.id
FROM actors a1
WHERE a1.first_name = $first_name_q
AND a1.last_name = $last_name_q
AND a1.film_count = (
SELECT MAX(a.film_count)
FROM actors a
    WHERE a.first_name = $first_name_q
    AND a.last_name = $last_name_q
)
ORDER BY a1.id ASC
LIMIT 1
";

            $rows_actor = $db->query($actor_query_text);

            // found corresponded name.
            if ($rows_actor->rowCount () > 0) {

                foreach ($rows_actor as $row) { 
                    $actor_id = $row['id'];
                }
                return true;
            }

            // can't find name.
            else {
                return false;
            }
        }
    } 

    catch (PDOException $ex) {
        return false;
    }
}


function getQueryForAll() { 

    global $actor_id;

    $query_text = "
SELECT m.name, m.year
FROM movies m
JOIN roles r ON r.movie_id = m.id
JOIN actors a ON r.actor_id = a.id 
WHERE a.id = $db->quote($actor_id)
ORDER BY m.year DESC, m.name ASC
";

    return $query_text;

}

function getQueryWithKevin() {

    global $actor_id;

    $query_text = "
SELECT m.name, m.year
FROM movies m
JOIN roles r1 ON r1.movie_id = m.id
JOIN actors kevin ON r1.actor_id = kevin.id 
JOIN roles r2 ON r2.movie_id = m.id
JOIN actors a ON r2.actor_id = a.id 
WHERE a.id = $db->quote($actor_id)
    and kevin.first_name = 'Kevin' and kevin.last_name = 'Bacon'
ORDER BY m.year DESC, m.name ASC
";

    return $query_text;

}

// $db = new PDO("mysql:dbname=imdb;host=localhost;", "morinom", "abcde")

/*

 test: WHERE a.first_name = 'Rick' and a.last_name = 'Greenough' 
 test: WHERE a.first_name LIKE 'Rick%' and a.last_name = 'Greenough' 

 */

?>


