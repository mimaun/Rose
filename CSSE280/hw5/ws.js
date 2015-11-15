"use strict";

var problem_array = [];
var answer_array = [];
var word_array = []; 
var all_words = [];

var ROW_NUM = 0;
var COLUMN_NUM = 0;

var clickCount = 0; 
var firstPos = new Array(2);
var endPos = new Array(2); 

var allMatchFlag = false;
var firstMatchPos = new Array(2);

$(function() {

    $("body").css({
        // "width": "700px",
        "display": "block",
        "margin-right": "auto",
        "margin-left": "auto",
        "padding": "10px",
        "text-align": "center",
    });

    $("#tablePuzzle").css({ 
        "clear": "both",
        "border": "3px solid black",
        "font-family": "serif",
        "font-size": "20px",
        "text-align": "center",
        "margin-left": "auto",
        "margin-right": "auto",
        "padding": "5px",
        "float": "right",
    });

    $("#puzzleList ul").css({
        "position": "relative"
    });

    $("#puzzleList ul").css({
        "list-style": "none outside none",
        "float": "left",
        "position": "relative",
        "left": "50%"
    });

    $("#puzzleList li").css({
        "float": "left",
        "position": "relative",
        "left": "-50%",
        "margin-right": "10px",
        "margin-left": "10px"
    });

    // get selected file's name.
    $("#puzzleChoice").click(function() {
        var pazzleName = $("#puzzle option:selected").text();
        getPuzzleFile(pazzleName);
    }); 

    $("#answerSpace").css({
        "display": "block"
    });

    $("#form").css({
        "clear": "left",
        "display": "block",
        "position": "relative",
    });
});

function getPuzzleFile(filename) {

    ROW_NUM = 0;
    COLUMN_NUM = 0;

    // get data from file.
    $.get("puzzles/" + filename, function(data) {

        // split with new line code.
        var line_array = data.split(/[\n\s]+/g);
        ROW_NUM = line_array[0].length;

        // push each lines to each array.
        for(var i = 0; i < line_array.length; i++) {
            if(line_array[i].length == ROW_NUM) {
                problem_array.push(line_array[i]);
                COLUMN_NUM++;
            }
            else
                answer_array.push(line_array[i]);
        } 
        resolutionWord();
    }); 

}

function resolutionWord() { 

    // initialize.
    for(var i = 0; i < ROW_NUM; i++) {
        all_words[i] = [];
        for(var j = 0; j < COLUMN_NUM; j++) {
            all_words[i][j] = "";
        }
    }

    // resolution to a character.
    for(var i = 0; i < ROW_NUM; i++) {
        for(var j = 0; j < COLUMN_NUM; j++) {
            var w = problem_array[i].substr(j, 1);
            all_words[i][j] = w;
        }
    } 

    console.log(all_words.toString());
    createAnswerSpan();
}

function createAnswerSpan() {

    var newSpan;

    // answer span.
    for(var i = 0; i < ROW_NUM; i++) {
        newSpan = $("<span>" + answer_array[i] + "</span>");
        newSpan.addClass("answer");
        newSpan.addClass(answer_array[i].toLowerCase());
        newSpan.click(clickHint);
        $("#answerSpace").append(newSpan);
        $("#answerSpace").append("<br>");
    }

    $(".answer").css({
        "backgroud-color" : "transparent"
    }); 

    createTable();
}

// search direction: →
function rightHorizontal(x, y, i, word) { 

    // wall.
    if(x > COLUMN_NUM-1) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) { 

            console.log("match: " + all_words[y][x]);

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            rightHorizontal(x+1, y, i+1, word);
        } 
    }
}

// search direction: ←
function leftHorizontal(x, y, i, word) {

    // wall.
    if(x < 0) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {


            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            leftHorizontal(x-1, y, i+1, word);
        }
    }
}

// search direction: ↑
function upVertical(x, y, i, word) {

    // wall.
    if(y < 0) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            upVertical(x, y-1, i+1, word);
        }
    }
}

// search direction: ↓
function downVertical(x, y, i, word) {

    // wall.
    if(y > ROW_NUM-1) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true; 
                return;
            }

            // continue survey.
            downVertical(x, y+1, i+1, word);
        }
    }
}

// search direction: ↑→
function upRight(x, y, i, word) { 

    // wall.
    if(y < 0 || x > COLUMN_NUM-1) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {
            console.log(all_words[y][x]);

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            upRight(x+1, y-1, i+1, word);
        }
    } 
}

// search direction: ←↑
function upLeft(x, y, i, word) {

    // wall.
    if(y < 0 || x < 0) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true; 
                return;
            }

            // continue survey.
            upLeft(x-1, y-1, i+1, word);
        }
    } 
}

// search direction: ↓→
function downRight(x, y, i, word) {

    // wall.
    if(y > ROW_NUM-1 || x > COLUMN_NUM-1) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            downRight(x+1, y+1, i+1, word);
        }
    } 
}

// search direction: ←↓
function downLeft(x, y, i, word) {

    // wall.
    if(y > ROW_NUM-1 || x < 0) return;

    // check if all_words[x][y] == word[i] or not.
    else {
        // match.
        if(all_words[y][x].match(word.substr(i, 1))) {

            if(i == 0) {
                firstMatchPos = [];
                firstMatchPos.push(x);
                firstMatchPos.push(y);
            }

            // all match.
            else if(i == word.length-1) { 
                console.log("all match");
                allMatchFlag = true;
                return;
            }

            // continue survey.
            downLeft(x-1, y+1, i+1, word);
        }
    } 
}

function createTable() {

    var table = $("#tablePuzzle");
    var tbody = $("<tbody>");

    for(var i = 0; i < ROW_NUM; i++) {

        // create table row.
        var tr = $("<tr>");

        for(var j = 0; j < COLUMN_NUM; j++) {

            // create table column (cell).
            var td = $("<td>");
            td.css({ 
                "border": "2px dotted gray",
            });

            td.text(all_words[i][j]); 

            // get x, y for each cell.
            td.click(function() {
                // x
                var x = this.cellIndex;
                // y
                var y = $(this).closest('tr').index();

                clickCharacter(x, y);
            });

            tr.append(td);
        }
        tbody.append(tr);
    }
    table.append(tbody);

    $("#tablePuzzle td").hover(
            // mouseover
            function(){
                $(this).css("color","red");
            },
            // mouseout
            function(){
                $(this).css("color","black");
            }
            ); 
} 

function clickCharacter(x, y) {

    clickCount++;

    var chosenPosArr = [];
    var currentID = Number($(this).attr("id"));

    var isStartCheck = false; 

    // first click.
    if(clickCount % 2) {
        firstPos[0] = x;
        firstPos[1] = y;
        isStartCheck = false;
    }
    // second click.
    else { 
        endPos[0] = x;
        endPos[1] = y;
        isStartCheck = true;
        chosenPosArr.length = 0;
    } 

    var selectedWord = "";

    // get chosen word.
    if(isStartCheck) {
        console.log("check start");
        selectedWord = "";

        // ↓
        if(firstPos[0] == endPos[0] && endPos[1] > firstPos[1]) { 
            for(var i = 0; i <= endPos[1] - firstPos[1]; i++) {
                selectedWord += all_words[firstPos[1]+i][firstPos[0]];
                // array.push(y, x)
                chosenPosArr.push(new Array(firstPos[1]+i, firstPos[0]));
            }
        }

        // ↑
        else if(firstPos[0] == endPos[0] && endPos[1] < firstPos[1]) { 
            for(var i = 0; i <= firstPos[1] - endPos[1]; i++) {
                selectedWord += all_words[firstPos[1]-i][firstPos[0]]; 
                chosenPosArr.push(new Array(firstPos[1]-i, firstPos[0]));
            }
        }

        // →
        else if(firstPos[1] == endPos[1] && endPos[0] > firstPos[0]) {
            for(var i = 0; i <= endPos[0] - firstPos[0]; i++)  {
                selectedWord += all_words[firstPos[1]][firstPos[0]+i]; 
                chosenPosArr.push(new Array(firstPos[1], firstPos[0]+i));
            }
        }

        // ←
        else if(firstPos[1] == endPos[1] && endPos[0] < firstPos[0]) {
            for(var i = 0; i <= firstPos[0] - endPos[0]; i++) {
                selectedWord += all_words[firstPos[1]][firstPos[0]-i];
                chosenPosArr.push(new Array(firstPos[1], firstPos[0]-i));
            }
        }

        else if(Math.abs(endPos[0] - firstPos[0]) == Math.abs(endPos[1] - firstPos[1])) {
            // ↓→
            if(endPos[1] > firstPos[1] && endPos[0] > firstPos[0]) {
                for(var i = 0; i <= endPos[1] - firstPos[1]; i++) {
                    selectedWord += all_words[firstPos[1]+i][firstPos[0]+i];
                    chosenPosArr.push(new Array(firstPos[1]+i, firstPos[0]+i));
                }
            }
            // ←↓
            else if(endPos[1] > firstPos[1] && endPos[0] < firstPos[0]) {
                for(var i = 0; i <= endPos[1] - firstPos[1]; i++) {
                    selectedWord += all_words[firstPos[1]+i][firstPos[0]-i];
                    chosenPosArr.push(new Array(firstPos[1]+i, firstPos[0]-i));
                }
            }
            // ↑→
            else if(endPos[1] < firstPos[1] && endPos[0] > firstPos[0]) {
                for(var i = 0; i <= firstPos[1] - endPos[1]; i++) {
                    selectedWord += all_words[firstPos[1]-i][firstPos[0]+i];
                    chosenPosArr.push(new Array(firstPos[1]-i, firstPos[0]+i));
                }
            }
            // ←↑
            else if(endPos[1] < firstPos[1] && endPos[0] < firstPos[0]) {
                for(var i = 0; i <= firstPos[1] - endPos[1]; i++) {
                    selectedWord += all_words[firstPos[1]-i][firstPos[0]-i];
                    chosenPosArr.push(new Array(firstPos[1]-i, firstPos[0]-i));
                }
            }
        } 

        console.log("You selected: " + selectedWord);
        if(compareWithAnswer(selectedWord)) {
            console.log("found");
            addHighlight(chosenPosArr, selectedWord);
        }
    } 
    else return;
}

// positions -> [y, x] of table, word -> found word
function addHighlight(positions, word) {
    console.log("addHighlight");

    // highlight found word in table.
    for(var i = 0; i < positions.length; i++) {
        // col * y + x
        $("#tablePuzzle td").eq(ROW_NUM * positions[i][0] + positions[i][1]).
            css("background-color","lightgreen");
    }

    // add line-through to found answer.
    $("." + word).css({
        "text-decoration":"line-through",
        "color":"gray",
    });
}

function compareWithAnswer(selected) {
    if(answer_array.indexOf(selected) != -1) return true;
    else false;
}

function clickHint() {
    console.log("click");
    var hintWord = $(this).text();
    allMatchFlag = false;
    var foundFlag = false;

    for(var i = 0; i < ROW_NUM; i++) {
        for(var j = 0; j < COLUMN_NUM; j++) {
            rightHorizontal(j, i, 0, hintWord);
            leftHorizontal(j, i, 0, hintWord);
            upVertical(j, i, 0, hintWord);
            downVertical(j, i, 0, hintWord);
            upRight(j, i, 0, hintWord);
            upLeft(j, i, 0, hintWord);
            downRight(j, i, 0, hintWord);
            downLeft(j, i, 0, hintWord);

            if(allMatchFlag) {
                addHintHighlight();
                return;
            }
        }
    }

    console.log("not found"); 
}

function addHintHighlight() {

    // all[y][x]
    console.log(all_words[firstMatchPos[1]][firstMatchPos[0]]);

    $("#tablePuzzle td").eq(ROW_NUM * firstMatchPos[1] + firstMatchPos[0]).
        css("background-color","yellow");
}

