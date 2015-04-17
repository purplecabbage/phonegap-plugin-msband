



document.addEventListener('deviceready', onDeviceReady);

function onDeviceReady() {

}   

btnGetBandInfo.addEventListener("click",getBandInfo);

function getBandInfo() {
    if(cordova) {
        alert("i gots me some cordova")
    }
}

[swBandContact, swUV, swSkinTemp, swSteps, swDistance, swHR, swAccel, swGyro].forEach(function(elem){
	elem.addEventListener('click',function(evt){
		window.alert(evt.target.checked);
	});
});

// txtBandContact
// txtUV
// txtSkinTemp
// txtSteps
// txtDistance
// txtHR
// txtAccel
// txtGyro


