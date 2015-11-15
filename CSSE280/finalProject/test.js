"use strict";

var WEB_APP = "http://www.postcodez.com/api/zip/47803/api.xml";

$(function() {
    $.ajax(WEB_APP)
        .done(function() {
            console.log($(this));
        })
    .fail(function() {
        console.log("fail")
    });
});
