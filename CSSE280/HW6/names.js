"use strict"

var WEB_APP = "http://wwwuser.csse.rose-hulman.edu/babynames/babynames.php";
// http://wwwuser.csse.rose-hulman.edu/babynames/babynames.php?type=list

$(function() {
    
    // click handler of search button.
    $("#search").click(searchClick);

    $.ajax(WEB_APP,
            {
                "type" : "GET",
                "data" : {"type" : "list"},
                "datatype" : "text",
            }).done(loadBabies).fail(ajaxFailed);

});

function loadBabies(data) {
    // hide "Loading..."
    $("#loadingnames").hide();

    // baby names array.
    var babies = data.split("\n");
    console.log(babies.length);
    for(var i = 0; i < babies.length; i++) {
        var option = $("<option>").html(babies[i]).val(babies[i]);
        $("#allnames").append(option);
    }

    // make select available.
    $("#allnames").prop("disabled", false);
}

function searchClick(e) {

    // get selected name.
    var name = $("#allnames").val();

    // get gender.
    var gender = $("#genderm").prop("checked") ? "m" : "f";

    // name sould be not empty.
    if(name) {

        $("#resultsarea").show();
        $("#loadingmeaning").show();
        $("#loadinggraph").show();
        $("#loadingcelebs").show();

        $.get(WEB_APP, 
                {"type" : "meaning", "name" : name}).done(displayMeaning);
        $("#norankdata").hide();
        $("#graph").html("");

        $.ajax(WEB_APP, {
            "type" : "GET",
            "data" : {
                "type" : "rank", 
                "name" : name, 
                "gender" : gender
            },
            "datatype" : "text"
        }).done(displayGraph).fail(ajaxRankFailed);

        $.ajax(WEB_APP, {
            "type" : "GET",
            "data" : {
                "type" : "celebs", 
                "name" : name, 
                "gender" : gender
            },
            "datatype" : "json"
        }).done(displayCelebs).fail(ajaxFailed); 
    }

}

function displayCelebs(data) {
    $("#loadingcelebs").hide();
    if(!data) return;

    $.each(data.actors, function(key, value) {
        var li = $("<li>");
        li.html(value.firstName + " " + value.lastName + " (" + value.filmCount + " films)");

        // fix for singular vs plural
        $("#celebs").append(li);
    });
}

function displayGraph(data) {
    $("#loadinggraph").hide();

    // data not found.
    if(!data) return;

    // table row.
    var trYears = $("<tr>");
    var trRanks = $("<tr>"); 
    $("#graph").append(trYears);
    $("#graph").append(trRanks);

    // get all <rank> in data.
    var ranks = $(data).find("rank");
    ranks.each(function() {

        // year table header.
        var thYear = $("<th>");

        // rank table cell.
        var tdRank = $("<td>");

        // pink graph.
        var divRank = $("<div>");

        thYear.html($(this).attr("year"));
        trYears.append(thYear);

        tdRank.html($(this).text());
        tdRank.css({
            "vertical-align":"bottom",
            "height":"250px"
        });

        var rank = parseInt($(this).text());
        if(rank >= 1 && rank <= 10) {
            divRank.addClass("popular");
        } 

        // divRank.html(rank);
        if(rank == 0) {
            divRank.height("0px");
        } else {
            divRank.height(Math.floor((1000 - rank)/4) + "px");
            divRank.css({
                "width":"50px",
                "background-color":"pink"
            });
        }

        $(".popular").css("color","red");

        tdRank.append(divRank);
        trRanks.append(tdRank);

    });
}

function displayMeaning(data) {
    $("#originmeaning").show();
    $("#meaning").html(data);
    $("#loadingmeaning").hide();
}

function ajaxFailed(xhr, status, exception) {
    console.log(xhr, status, exception);
}

function ajaxRankFailed(xhr, status, exception) {
    $("#loadinggraph").hide();
    console.log(xhr.status);
    if(xhr.status == "410") {
        $("#norankdata").show();
    } else { 
        console.log("else");
        console.log(xhr, status, exception);
    }
}







