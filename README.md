# ms-band-plugin
PhoneGap Plugin for Microsoft Band


###To run the demo ( iOS only for now )

    cd demo/
    cordova plugin add cordova-plugin-device
    cordova plugin add cordova-plugin-statusbar
    cordova plugin add cordova-plugin-console
    cordova plugin add --link ../plugin-src/
    cordova platform add ios
    cordova run ios --device
