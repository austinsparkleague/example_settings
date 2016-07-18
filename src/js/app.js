//This event is called when the webview is closed (when the user cancels or saves)
Pebble.addEventListener("webviewclosed", function(e){
    //Prints the response
    console.log("Got response " + e.response);
    if(e.response){
        //If it exists it sends it to the Pebble as a JSON object
        Pebble.sendAppMessage(JSON.parse(decodeURIComponent(e.response)));
    }
});

//This event listener is called when the settings button is clicked
Pebble.addEventListener("showConfiguration", function(){
    //It opens the URL you provide it with this function. We give you an example webpage that works
    //with this tutorial perfectly.
    Pebble.openURL("https://austinsparkleague.github.io/webpage_example/");
});