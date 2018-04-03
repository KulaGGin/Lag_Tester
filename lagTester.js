window.onload = function(e) {
	document.addEventListener("mousedown", mouseDown, false);
	function mouseDown(e) {
		const buttonNum = e.which;

		if(buttonNum === 1) {
			//console.log("You pressed left mouse button.");
			document.body.style.background = "white";
		}
	}

	document.addEventListener("mouseup", mouseUp, false);
	function mouseUp(e) {
		const buttonNum = e.which;

		if(buttonNum === 1)
		{
			//console.log("You released left mouse button.");
			document.body.style.background = "black";
		}
	}

};