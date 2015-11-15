/*  TicTacToe  Claude Anderson for CSSE 280.  October 22-23, 2015   */
"use strict";

var SIZE;  // 4 for 16 puzzle, 5 for 25 puzzle, etc.
var NUM_SQUARES;
var BOARD_WIDTH;   // will be calculated based on value of SIZE.
var BORDER_SIZE = 3;    // 3 pixels
var SQUARE_SIZE = 65; 
var FONT_SIZE = 50;

var squareList = [];  // array of the DOM elements for the squares, similar to 15-puzzle.
var moveCount;  // how many board squares are filled?
var playerTurn;  // Will be "X" or "O"
var correct;  // used for knowing which cells to highlight when a player wins.

$(function () {  // this is the jQuery version of window.onload. YOu are not required to use jQuery at all. 
    $("#Choose").click( // build the board and remove the form, just like 15-puzzle.
            function() {
                SIZE = parseInt($("#boardsize").text());
                var fileNameString = $("#gameType option:selected").text(); // You should assign it a value. 
                var fileString = "";
                if(fileNameString != "NEW GAME")
                    fileString = $("#" + fileNameString).text();  // You should assign it a value. 
                else
                    fileString = $("#new").text();  // You should assign it a value. 

                NUM_SQUARES = SIZE * SIZE; //unlike 15-puzzle, squares are fixed-size.
                BOARD_WIDTH = SIZE*SQUARE_SIZE + (SIZE+ 1)*BORDER_SIZE + 10; // BOARD size varies.

                console.log(fileNameString);

                console.log(fileString);

                // Add code to remove the form
                $("#form").remove();
                setup_board(fileString);
            });
});

var setup_board = function(fileString){ // put the squares in the board and in squareList 
    // A lot of this is just like 15-puzzle, but there is also some new stuff.  I removed about 30 lines of code

    playerTurn = fileString.split("|")[1];
    var squareString = fileString.split("|")[2]
    var squareChar = [];
    for(var i = 0; i < squareString.length; i++) {
        squareChar.push(squareString.substr(i, 1));
    }

    var boardDiv = $("#board");
    boardDiv.css("width", BOARD_WIDTH + "px");

    for(var i = 0; i < NUM_SQUARES; i++) {
        var nodeName = squareChar[i];
        if(squareChar[i] == "b") {
            nodeName = "&nbsp";
        }
        var newSpan = $("<span>" + nodeName + "</span>");
        newSpan.attr("id", i);
        newSpan.addClass("tile");
        newSpan.css({
            "width": SQUARE_SIZE + "px",
            "height": SQUARE_SIZE + "px",
            "line-height": SQUARE_SIZE + "px",
            "font-size": FONT_SIZE + "px",
        });

        /* arrange border */
        // left edge col.
        if(i % SIZE == 0)
            newSpan.css("border-left","none");
        // top row.
        if(Math.floor(i / SIZE) == 0)
            newSpan.css("border-top","none");
        // right edge col.
        if(i % SIZE == SIZE - 1)
            newSpan.css("border-right","none");
        // bottom row.
        if(Math.floor(i / SIZE) == SIZE - 1)
            newSpan.css("border-bottom","none"); 

        // Add tile at end of list.
        squareList.push(newSpan[0]);

        // Add to the DOM.
        boardDiv.append(newSpan); 

        // Make it respond to clicks.
        newSpan.click(recordClick);
    } 
};

var recordClick = function() {  // do everything that happens when user clicks a row.
    var squareID = parseInt($(this).attr("id"));
    var content = $(this).text();
    console.log("id: " + squareID + ", content: " + content);

    // occupied.
    if(content == "X" || content == "O") return;

    // you can put char.
    else {
        $(this).text(playerTurn);
        if(playerTurn == "X") playerTurn = "O";
        else playerTurn = "X";
    }

    var winDiv = $("#finalMessage");

    // check col and row win.
    for(var i = 0; i < SIZE; i++) {

    // check x win.
        if(
            checkWinEachDir("v", i, "X") ||
            checkWinEachDir("h", i*SIZE, "X") 
          ) {
            winDiv.text("X Won!");
            return;
        }

        // check o win.
        else if(
                checkWinEachDir("v", i, "O") ||
                checkWinEachDir("h", i*SIZE, "O") 
               ) {
            winDiv.text("O Won!");
            return;
        }
    }

    // check diag x win.
    if(
            checkForWin(0, NUM_SQUARES, SIZE+1, "X") ||
            checkForWin(SIZE-1, NUM_SQUARES-SIZE+1, SIZE-1, "X") 
      ) {
        winDiv.text("X Won!");
    }

    // check diag o win.
    else if(
            checkForWin(0, NUM_SQUARES, SIZE+1, "O") ||
            checkForWin(SIZE-1, NUM_SQUARES-SIZE+1, SIZE-1, "O")
           ) {
        winDiv.text("O Won!");
    } 

    // puzzle is filled and no one win.
    else {
        for(var i = 0; i < squareList.length; i++) {
            if(squareList[i].innerHTML == "X" || squareList[i].innerHTML == "O")
                continue;
            else
                return;
        }
        winDiv.text("CAT");
    }
};	

// chcek for win in row and col.
function checkWinEachDir(direction, first, symbol) {

    correct = [];

    // col.
    if(direction == "v") {
        for(var i = first; i <= first+SIZE*(SIZE-1); i += SIZE) { 
            if(squareList[i].innerHTML != symbol)
                return false;
            else
                correct.push(squareList[i]);	
        }
    }

    // row.
    else if(direction == "h") {
        for(var i = first; i < first+SIZE; i++) { 
            if(squareList[i].innerHTML != symbol)
                return false;
            else
                correct.push(squareList[i]);	
        } 
    }

    for(var i = 0; i < correct.length; i++) {
        correct[i].classList.add("highlighted");
    }

    return true;		
}

    // The elegant way to check for a win.  You'll need ot add four calls to this function in the above code.
    var checkForWin = function(first, limit, increment, symbol){
        correct = [];
        for (var i=first; i<limit; i+=increment)
            if (squareList[i].innerHTML != symbol)
                return false;
            else
                correct.push(squareList[i]);	

        for(var i = 0; i < correct.length; i++) {
            correct[i].classList.add("highlighted");
        }
        return true;		
    };

    /* Or you can do it the "brute force" way by calling these functions:
     * 
     * Hve these tests in recordClick:
     * 		if (checkRow(row, playerTurn) ||   // check for win and highlight
     checkCol(col, playerTurn) ||   
     checkDiags(playerTurn)){


     var checkRow = function(row, symbol) {
     correct = [];
     for (var i=row*SIZE; i<(row+1)*SIZE; i++)
     if (squareList[i].innerHTML != symbol)
     return false;
     else
     correct.push(squareList[i]);
     return true;			
     };

     var checkCol = function(col, symbol) {
     correct = [];
     for (var i=col; i<NUM_SQUARES; i+=SIZE)
     if (squareList[i].innerHTML != symbol)
     return false;
     else
     correct.push(squareList[i]);	
     return true;		
     };

     var checkDiags = function(symbol) {

     var found = true; // check downward diagonal first
     correct = [];
     for (var i=0; i<NUM_SQUARES; i+=(SIZE+1))
     if (squareList[i].innerHTML != symbol)
     found = false;
     else
     correct.push(squareList[i]);
     if (found) 
     return true;

     correct = []; // upward
     for (var j=SIZE-1; j<NUM_SQUARES-1; j+=(SIZE-1))
     if (squareList[j].innerHTML != symbol)
     return false;
     else
     correct.push(squareList[j]);
     return true;
     };

     var checkForWin = function(first, increment, limit, symbol){
     correct = [];
     for (var i=first; i<limit; i+=increment)
     if (squareList[i].innerHTML != symbol)
     return false;
     else
     correct.push(squareList[i]);	
     return true;		
     }
     */

