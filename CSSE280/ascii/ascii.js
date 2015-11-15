// <!-- CSSE280 WebProgramming HW4                                                               -->
// <!-- Name: Misato Morino                                                                      -->
// <!-- ID: morinom                                                                              -->
// <!-- Contents: ascii.html, ascii.css, ascii.js, animation.js, myanimation.js, myanimation.txt -->

"use scrict";

var velocity;
var currentFrame;
var frames;
var timer;
var index;

window.onload = pageLoad;

// Initially
function pageLoad() { 
    console.log("pageLoad");

    velocity = 250;

    // first setting.
    document.getElementById("stop").disabled = true;
    document.getElementById("start").onclick = playAnimation;
    document.getElementById("stop").onclick = stopAnimation;
    document.getElementById("animationList").onchange = changeAnimation;
    document.getElementById("size").onchange = chagneSize;

    // observe speed radio.
    var speedArray = document.getElementsByName("speed");
    for(var i = 0; i < speedArray.length; i++) {
        speedArray[i].onchange = changeSpeed;
    }
}

/*
 * This will be called when value of speed is changed.
 * */
function changeSpeed() {
    console.log("changeSpeed");
    var speeds = document.getElementsByName("speed");
    var selectedSpeed;
    var speed = {
        "turbo": 50,
        "normal": 250,
        "slo-mo": 1000
    }

    // radio scanning.
    for(var i = 0; i < speeds.length; i++) {
        if(speeds[i].checked) {
            selectedSpeed = speeds[i].value;
            velocity = speed[selectedSpeed];
        }
    } 

    // stop timer.
    clearInterval(timer);

    // restart timer.
    timer = setInterval("nextFrame()", velocity);
}

/*
 * This will be called after changing value of speed.
 * */
function chagneSize() {
    console.log("changeSize");
    var selectedSize = document.getElementById("size").value;

   var size = {
       "tiny": 7,
       "small": 10,
       "medium": 12,
       "large": 16,
       "extra large": 24,
       "xxl": 32
   }

   // change font size.
   document.getElementById("textbox").style.fontSize = size[selectedSize] + "pt";
}

/*
 * This will be called after changing value of animation list.
 * */
function changeAnimation() {

    // get animation name.
    var name = document.getElementById("animationList").value;
    
    // get animation data.
    var animation = ANIMATIONS[name];
    document.getElementById("textbox").value = animation; 
}

/*
 * This will be called after pushing startButton.
 * */
function playAnimation() {
    console.log("playAnimation");

    // UI setting.
    document.getElementById("start").disabled = true;
    document.getElementById("stop").disabled = false;
    document.getElementById("animationList").disabled = true;
    document.getElementById("textbox").disabled = true;

    // get information from textbox, and separate animation data every frame.
    frames = document.getElementById("textbox").value.split("=====\n");

    // get first section.
    currentFrame = frames[index = 0];

    // start timer.
    timer = setInterval("nextFrame()", velocity);
}

function nextFrame() {

    // drawing.
    document.getElementById("textbox").value = currentFrame;

    // get array's index of currentFrame.
    console.log("i: " + index);
    console.log("frame length: " + frames.length);

    // if currentFrame is last frame.
    if(index === frames.length - 1) {
        console.log("Now return to first frame");
        index = -1;
    }

    // nexe frame.
    currentFrame = frames[++index];
}

/*
 * This will be called after pushing stopButton.
 * */
function stopAnimation() {
    console.log("stopAnimation");

    // UI setting.
    document.getElementById("start").disabled = false;
    document.getElementById("stop").disabled = true;
    document.getElementById("animationList").disabled = false; 
    document.getElementById("textbox").disabled = false;

    // textbox refresh.
    changeAnimation();

    // stop timer.
    clearInterval(timer);
    index = 0;
}

