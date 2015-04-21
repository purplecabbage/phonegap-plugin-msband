
var exec = require('cordova/exec');
var subscribers = {

};

var BandContactState = {
	NotWorn:0,
	Worn:1
};

var BandContactReading = {
	'bandContactState':BandContactState.NotWorn
}

var HeartRateQuality = {
	Acquiring:0,
	Locked:1
};

var BandAccelerometerReading = {
	x:0,
	y:0,
	z:0
};

var BandMotionType = {
	Idle:0,
	Jogging:1,
	Running:2,
	Unknown:3,
	Walking:4
};

var BandDistanceReading = {
	currentMotion:BandMotionType.Unknown, // motion type
	pace:0,
	speed:0,
	totalDistance:0
}

var BandGyroscopeReading = {
	x:0,y:0,z:0 // angular velocity
}

var BandHeartRateReading = {
	heartRate:0,
	heartRateQuality:HeartRateQuality.Acquiring
}

var BandPedometerReading = {
	totalSteps:0
}

var BandSkinTemperatureReading = {
	temperature:0 // degrees celcius
}

var UVExposureLevel = {
	None:0,
	Low:1,
	Medium:2,
	High:3,
	VeryHigh:4
}

var BandUVLightReading = {
	exposureLevel:0
}


var sensorEventNames = [
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
			sensorEventNames.indexOf(sensorEvent.toLowerCase()) > -1);
}


var sensorCallbacks = {};

// initialize internal structures 
sensorEventNames.forEach(function(sensorEventName){
	sensorCallbacks[sensorEventName] = [];
});

function onSensorUpdate(result) {
    var eventName = result.event;
    var reading = result.reading;
    sensorCallbacks[eventName].forEach(function(cb){
    	cb(reading);
    });
}

function onSensorError(sensorEvent,res) {
	alert("onSensorError::" + JSON.stringify(sensorEvent));
}
            
               


// TODO: Retrieve the Band Version Information
// hardware version and firmware version


module.exports = {
    connect:function(success,fail){// todo: callbacks
        function onConnectSuccess(res) {
            success && success();
        }
               
        function onConnectError(err) {
            fail && fail();
        }
        exec(onConnectSuccess, onConnectError, "MSBandPlugin", "connect", []);
    },
    queryVersionInfo:function(win,lose) { // todo:callbacks
		function onInfoSuccess(res) {
			win && win(res);
		}
       
		function onInfoError(err) {
			lose && lose(err);
		}

        exec(onInfoSuccess, onInfoError, "MSBandPlugin", "queryVersionInfo", []);
    },
	sensors:{
		on:function(sensorEvent,callback){
			//alert("sensorEvent :: " + sensorEvent);
			if(isValidSensorEvent(sensorEvent)) {
				sensorEvent = sensorEvent.toLowerCase();
				//if(sensorCallbacks[sensorEvent].length) {
					if(sensorCallbacks[sensorEvent].indexOf(callback) > -1) {
						alert("Sensor Add Error - Sensor callback already exists : " + sensorEvent);
					}
					else {
						sensorCallbacks[sensorEvent].push(callback);
						//alert("sensorCallbacks[sensorEvent].length = " + sensorCallbacks[sensorEvent].length);
						if(sensorCallbacks[sensorEvent].length === 1) {
							// only exec the native code if we go from 0->1
							// otherwise, we'll just notify the next time we receive a message
							exec(onSensorUpdate, onSensorError, "MSBandPlugin", "watchSensor", [sensorEvent]);
						}
					}
				//}
			}
			else {
				alert("Sensor Add Error - Invalid Sensor : " + sensorEvent);
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
						exec(null, null, "MSBandPlugin", "unwatchSensor", [sensorEvent]);
					}
				}
			}
			else {
				console.log("Sensor Remove Error - Invalid Sensor : " + sensorEvent);
			}
		}
	},
	vibrate:function(){
		exec(null, null, "MSBandPlugin", "vibrate", []);
	},
	stopAllSensors:function(){
		//sensorEventNames.forEach(...)
	}
}
