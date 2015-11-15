/*  "15 puzzle", expanded to be SIZE-squared puzzle.
    Written by Claude Anderson for CSSE 280.  April 11, 2013
    Revised October 2, 2015 
    renamed BOARD_SIZE to BOARD_WIDTH
    Changed names of parameters to swapDomElements
    Enhanced comments throughout the file.
    */

"use strict";

// CONSTANTS
var SIZE = 4;  // 4 for 16 puzzle, 5 for 25 puzzle, etc.
var NUM_SQUARES;
var BOARD_WIDTH = 500;  // 500 pixels
var BORDER_SIZE = 3;    // 3 pixels
var SQUARE_SIZE;
var FONT_SIZE = 50;

// GLOBAL VARS
var tileList = [];
var spacePos;
var emptySpace;
var minSwaps;
var maxSwaps;

$(function() {
    $("#sizeChoice").click (
            function() { 
                var radios = $('[name="size"]');
                radios.each(function() {
                    if(this.checked) {
                        SIZE = parseInt(this.value);
                        return false;   // This is new
                    }
                });
                NUM_SQUARES = SIZE * SIZE;
                SQUARE_SIZE = parseInt(BOARD_WIDTH - (SIZE - 1) * (BORDER_SIZE *3 + 1)) / SIZE;
                minSwaps = NUM_SQUARES;
                maxSwaps = NUM_SQUARES * 20; 
                $("#form").remove();
                setUpBoard();
            });
});

// called when the page first loads to create tiles and empty space 
var setUpBoard = function(){
    var boardDiv = $("#board");
    boardDiv.css("width", BOARD_WIDTH + "px");

    for(var i = 1; i <= NUM_SQUARES; i++) {
        var nodeName = i;
        if(i == NUM_SQUARES) {
            nodeName = "&nbsp";
        }
        // var newSpan = document.createElement("span");
        var newSpan = $("<span>" + nodeName + "</span>");
        newSpan.attr("id", nodeName);
        // newSpan.className = "tile";
        newSpan.addClass("tile");
        // newSpan.id = nodeName;
        // newSpan.innerHTML = nodeName;
        newSpan.css({
            "width": SQUARE_SIZE + "px",
            "height": SQUARE_SIZE + "px",
            "line-height": SQUARE_SIZE + "px",
            "border": BORDER_SIZE + "px solid red",
            "font-size": FONT_SIZE + "px"
        });


        if(i == NUM_SQUARES) {
            // class is now "tile space".
            // newSpan.classList.add("space");
            newSpan.addClass("space"); 
            // newSpan.innerHTML = "&nbsp";     // not need anymore
            spacePos = NUM_SQUARES - 1;
            emptySpace = newSpan;
        } 
        else {
            newSpan.mouseenter( function() {
                $(this).fadeTo('fast', 0.25);
            });

            newSpan.mouseleave( function() {
                $(this).fadeTo('fast', 1.0);
            });
        }

        // Add tile at end of list.
        tileList.push(newSpan[0]);

        // Add to the DOM.
        // boardDiv.appendChild(newSpan); 
        boardDiv.append(newSpan); 

        // Make it respond to clicks.
        newSpan.click(moveTile);
    } 
};

// shuffle the tiles
var numSwaps = parseInt(minSwaps + Math.random()*(maxSwaps - minSwaps));
var swapCount = 0;
while(swapCount < numSwaps) {
    var index = parseInt(Math.random() * NUM_SQUARES);
    // tileList[index] will be "this" inside moveTile.
    swapCount += moveTile.call(tileList[index]);
}

// Exchange the locations of two elements in the jQuery DOM.  
// Assumes that neither element is the parent of the other.	
// from http://stackoverflow.com/questions/10716986/swap-2-html-elements-and-preserve-event-listeners-on-them
//

var swapArrayElements = function(a, p1, p2) {
    var temp = a[p1];
    a[p1] = a[p2];
    a[p2] = temp;
};

var swapDomElements = function(element1, element2) {  
    // create marker element and insert it where element1 is
    // var temp = document.createElement("div");
    var temp = $("<div>");
    console.log(element1);
    console.log(element2);

    // element1.parentNode.insertBefore(temp, element1);
    temp.insertBefore(element1);

    // move element1 to immediately before element2
    // element2.parentNode.insertBefore(element1, element2);
    element1.insertBefore(element2);

    // move element2 to immediately before where element1 used to be
    // temp.parentNode.insertBefore(element2, temp);
    element2.insertBefore(temp);

    // remove temporary marker node
    // temp.parentNode.removeChild(temp);
    temp.remove();
}

// If clicked tile is next to the empty space, 
// swap them (in DOM and in tileList)
var moveTile = function() {

    // get position.
    var pos = tileList.indexOf(this);
    var diff = Math.abs(pos - spacePos);
    if(diff == 1 && sameRow(pos, spacePos, SIZE) || diff == SIZE) {
        console.log("swapping " + pos + " and " + spacePos);
        swapDomElements($(this), emptySpace);
        // this == tileList[i]
        swapArrayElements(tileList, pos, spacePos);
        spacePos = pos;
        return 1;
    } else {
        return 0;
    }
};

var sameRow = function(pos1, pos2, rowSize) {
    return rowNumber(pos1, rowSize) == rowNumber(pos2, rowSize);
};

var rowNumber = function(pos, rowSize) {
    return parseInt(pos / rowSize);
};



