

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
// used to demo various tile apis
var tileId = "3de787e9-62d2-430b-ae12-5be4a16606e8";

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
    btnGetTileSlots.addEventListener("click",onBtnGetTileSlots);
    btnSendTileMessage.addEventListener("click",onBtnSendTileMessage);
    btnRemoveTile.addEventListener("click",onBtnRemoveTile);
    btnSendTheme.addEventListener("click",onBtnSendTheme);
	btnGetTheme.addEventListener("click",onBtnGetTheme);

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

    var output = "";
    for(var v in evt){
        output += v + ":" + evt[v] + "<br>";
    }
    txtBandInfo.innerHTML = output;

}

function onGotVersionInfoError(err) {
	alert("onGotVersionInfoError:err: " + JSON.stringify(err));
}

function getBandInfo() {
    if(isBandConnected) {
    	msband.queryBandInfo(onGotVersionInfoSuccess,onGotVersionInfoError);
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

	function onCreateTileSuccess() {
		alert("onCreateTileSuccess");
	}

	function onCreateTileError(err) {
		alert("onCreateTileError::" + err);
	}

	msband.tiles.addTile(onCreateTileSuccess,
						 onCreateTileError,
						 tileId,
						 tileName,
						 lgIconImg,
						 smIconImg);
}

function onBtnGetTileSlots() {
	function onGetTileCountSuccess(res) {
		alert("onGetTileCountSuccess :: " + res);
	}

	function onGetTileCountError(err) {
		alert("onGetTileCountError::" + err);
	}

	msband.tiles.getRemainingTileCapacity(onGetTileCountSuccess, onGetTileCountError);
}

function onBtnSendTileMessage(){
	function success(res) {
		alert("onBtnSendTileMessage Success " + res);
	}
	function error(err) {
		alert("onBtnSendTileMessage Error " + err);
	}


	var title = txtMessageTitle.value;
	var body = taMessageBody.value;

	msband.tiles.sendMesageWithTileId(success,error,tileId,title,body);
}

function onBtnRemoveTile(){
	function success(res) {
		alert("onBtnRemoveTile Success " + res);
	}
	function error(err) {
		alert("onBtnRemoveTile Error " + err);
	}

	msband.tiles.removeTile(success,error,tileId);
}

// Theming

function onBtnGetTheme() {

	function success(res) {

		txtBaseColor.value = res.baseColor;
		txtBaseColor.style.borderRight = "solid 20px" + res.baseColor;

		txtHLColor.value = res.highLightColor;
		txtHLColor.style.borderRight = "solid 20px" + res.highLightColor;

		txtLLColor.value = res.lowLightColor;
		txtLLColor.style.borderRight = "solid 20px" + res.lowLightColor;

		txtSecTextColor.value = res.secondaryTextColor;
		txtSecTextColor.style.borderRight = "solid 20px" + res.secondaryTextColor;

		txtHiContColor.value = res.highContrastColor;
		txtHiContColor.style.borderRight = "solid 20px" + res.highContrastColor;

		txtMutedColor.value = res.mutedColor;
		txtMutedColor.style.borderRight = "solid 20px" + res.mutedColor;

	}
	function error(err) {
		alert("onBtnSendTheme Error " + err);
	}

	msband.personalization.getCurrentTheme(success,error);
}

function onBtnSendTheme() {

	var baseColor = txtBaseColor.value;
	var highLightColor = txtHLColor.value;
	var lowLightColor = txtLLColor.value;
	var secondaryTextColor = txtSecTextColor.value;
	var highContrastColor = txtHiContColor.value;
	var mutedColor = txtMutedColor.value;

	function success(res) {
		alert("onBtnSendTheme Success " + res);
	}
	function error(err) {
		alert("onBtnSendTheme Error " + err);
	}

	msband.personalization.setCurrentTheme(success,error,
		[baseColor,highLightColor,lowLightColor,secondaryTextColor,highContrastColor,mutedColor]);
}
