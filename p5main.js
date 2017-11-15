var pic;
var t = " ";
var p;

function setup(){
  pic = select('.wrapper');
  p = createP('No website yet');
}

function draw(){
  //ajaxFunction();
}

function ajaxFunction(){
	var ajaxRequest;  // The variable that makes Ajax possible!

	try{
		// Opera 8.0+, Firefox, Safari
		ajaxRequest = new XMLHttpRequest();
	} catch (e){
		// Internet Explorer Browsers
		try{
			ajaxRequest = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try{
				ajaxRequest = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (e){
				// Something went wrong
				alert("Your browser broke!");
				return false;
			}
		}
	}
	// Create a function that will receive data sent from the server
	ajaxRequest.onreadystatechange = function(){
		if(ajaxRequest.readyState == 4){
			t = ajaxRequest.responseText;
      if(t != 0){
        p.hide();
      }
      p.html(t);
		}
	}
	ajaxRequest.open("GET", "websites.php", true);
	ajaxRequest.send(null);
}
