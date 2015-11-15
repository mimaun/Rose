<?php

function countBottles() {

    $digit = array("one", "two", "three", "four", "five", "six", "seven", "eight", "nine");
    $prefix = array("twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety");
    $tens = array("ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen");

    for($i = 0; $i < 10; $i++) {
        for($j = 0; $j < 10; $j++) {

            $value = "";

            /* 0 - 9 */
            if($i == 0) {
                /* 1 - 9 */
                if($j > 0) {
                    $value = $digit[$j-1];
                }
                /* 0 */
                else if($j == 0) {
                    $value = "zero";
                }
            }

            /* 10 - 19 */
            else if($i == 1) {
                /* 10 - 19 */
                $value = $tens[$j];
            }

            /* 20 - 99 */
            else if($i > 1) {
                if($j > 0) {
                    $value = $prefix[$i-2] . "-" . $digit[$j-1];
                } else {
                    /* 20, 30, 40, 50, 60, 70, 80, 90 */
                    $value = $prefix[$i-2];
                }
            }

            print $value . " bottles of beer on the wall.";
            print $value . " bottles of beer!";
            print "take one down, pass it around,";
            print $value . " bottles of beer on the wall.";
        }
    }
}

countBottles();

?>
