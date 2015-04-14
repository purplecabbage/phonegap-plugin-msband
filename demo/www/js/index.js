



document.addEventListener('deviceready', onDeviceReady);

function onDeviceReady() {

}   

btnGetBandInfo.addEventListener("click",getBandInfo);

function getBandInfo() {
    if(cordova) {
        alert("i gots me some cordova")
    }
}


