

window.onerror = function(err,fn,ln) {
    alert(err + ":" + fn + ":" + ln);
}


// map/list of switchIds to event names, to output txt divs, so we can create listeners in a loop
var targetIds = {"swBandContact": { evtName:"bandcontact"	 ,txtOutId:"txtBandContact"},
				 "swUV"			: { evtName:"uvlevel"		 ,txtOutId:"txtUV"},
				 "swSkinTemp"	: { evtName:"skintemperature",txtOutId:"txtSkinTemp"},
				 "swSteps"		: { evtName:"pedometer"		 ,txtOutId:"txtSteps"},
				 "swDistance"	: { evtName:"distance"		 ,txtOutId:"txtDistance"},
				 "swHR"			: { evtName:"heartrate"		 ,txtOutId:"txtHR"},
				 "swAccel"		: { evtName:"accelerometer"	 ,txtOutId:"txtAccel"},
				 "swGyro"		: { evtName:"gyroscope"		 ,txtOutId:"txtGyro"}};

var isBandConnected = false;


document.addEventListener('deviceready', onDeviceReady);

function onDeviceReady() {
	Object.keys(targetIds).forEach(function(key){
		var elem = document.getElementById(key);
			elem.addEventListener('click',function(evt){
	        	subscribeSwitchClicked(evt.target.id,evt.target.checked);
		});
	});
	btnGetBandInfo.addEventListener("click",getBandInfo);
    btnStopAllEvents.addEventListener("click",stopAllSensors);
    btnCreateTile.addEventListener("click",createTile);
	msband.connect(onBandConnectSuccess,onBandConnectError);
}   

function onBandConnectSuccess(evt) {
	isBandConnected = true;
    bandIcon.src="img/iconWhite64-2x.png";
}

function onBandConnectError(err) {
	isBandConnected = false;
    bandIcon.src="img/iconBlack64-2x.png";
}

function stopAllSensors() {
    msband.sensors.stopAllSensors();
    var checkBoxes = document.querySelectorAll(".onoffswitch-checkbox");
    Array.prototype.slice.call(checkBoxes).forEach(function(elem) {
        elem.checked = false;
    });
}

function onGotVersionInfoSuccess(evt) {
    pFirmwareVersion.innerText = evt.frameworkVersion;
    pHardwareVersion.innerText = evt.hardwareVersion;

}

function onGotVersionInfoError(err) {
	alert("onGotVersionInfoError:err: " + JSON.stringify(err));
}

function getBandInfo() {
    if(isBandConnected) {
    	msband.queryVersionInfo(onGotVersionInfoSuccess,onGotVersionInfoError);
    }
    else {
    	alert("oops, band is not connected");
    }
}

function createCallback(txtOutId) {
	return function(evt) {
        var output = "";
        for(var v in evt){
            output += v + ":" + evt[v] + "<br>";
        }
        document.getElementById(txtOutId).innerHTML = output;
	}
}

function subscribeSwitchClicked(id,isOn) {
	var targetSensor = targetIds[id];
	if(isOn) {
        document.getElementById(targetSensor.txtOutId).innerText = "subscribing to event : " + targetSensor.evtName;
		targetSensor.callback = createCallback(targetSensor.txtOutId);
		msband.sensors.on(targetSensor.evtName,targetSensor.callback);
	}
	else {
		msband.sensors.un(targetSensor.evtName,targetSensor.callback);
		targetSensor.callback = null;
	}
}

function createTile() {
	var tileName = "PhoneGap";

	var smIconImg = "www/pgBandIcons/24x24.png";
	var lgIconImg = "www/pgBandIcons/46x46.png";
	var tileId = "3de787e9-62d2-430b-ae12-5be4a16606e8";

	function onCreateTileSuccess() {
		alert("onCreateTileSuccess");
	}

	function onCreateTileError(err) {
		alert("onCreateTileError::" + err);
	}

	msband.tiles.addTile(onCreateTileSuccess,onCreateTileError,tileName,lgIconImg,smIconImg,tileId);


}



