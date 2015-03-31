
var exec = require('cordova/exec');
var subscribers = {
	heartRate:[],

};



var sensorEventNames [ 
	"accelerometer",
	"gyroscope",
	"distance",
	"heartrate",
	"pedometer",
	"skintemperature",
	"uvlevel",
	"bandcontact"
];

function isValidSensorEvent(sensorEvent) {
	return (!sensorEvent || 
			!sensorEvent.toLowerCase ||
			sensorEventNames.indexOf(sensorEvent.toLowerCase()) < 0);
}


var sensorCallbacks = {};

// initialize internal structures 
sensorEventNames.forEach(function(sensorEventName){
	sensorCallbacks[sensorEventName] = [];
});

function onSensorUpdate(sensorEvent,res) {

}

function onSensorError(sensorEvent,res) {

}

// TODO: Retrieve the Band Version Information
// hardware version and firmware version






module.exports = {

	sensor:{
		on:function(sensorEvent,callback){
			if(isValidSensorEvent(sensorEvent)) {
				sensorEvent = sensorEvent.toLowerCase();
				if(sensorCallbacks[sensorEvent].length) {
					if(sensorCallbacks[sensorEvent].indexOf(callback) > -1) {
						console.log(("Sensor Add Error - Sensor callback already exists : " + sensorEvent);
					}
					else {
						sensorCallbacks[sensorEvent].push(callback);
						if(sensorCallbacks[sensorEvent].length === 1) {
							// only exec the native code if we go from 0->1
							// otherwise, we'll just notify the next time we receive a message
							exec(onSensorUpdate, onSensorError, "MSBandPlugin", "sensorWatch", [sensorEvent]);
						}
					}
				}
			}
			else {
				console.log("Sensor Add Error - Invalid Sensor : " + sensorEvent);
			}
		},
		un:function(sensorEvent,callback){
			if(isValidSensorEvent(sensorEvent)) {
				sensorEvent = sensorEvent.toLowerCase();
				if(sensorCallbacks[sensorEvent].length) {
					var index = sensorCallbacks[sensorEvent].indexOf(callback);
					sensorCallbacks[sensorEvent].splice(index,1);

					if(sensorCallbacks[sensorEvent].length < 1) {
						// only exec the native code if we go from 1->0
						exec(null, null, "MSBandPlugin", "sensorUnWatch", [sensorEvent]);
					}

				}
			}
			else {
				console.log("Sensor Remove Error - Invalid Sensor : " + sensorEvent);
			}
		}
	}
	

}