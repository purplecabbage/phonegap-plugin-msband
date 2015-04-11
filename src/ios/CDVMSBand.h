
#import <MicrosoftBandKit_iOS/MicrosoftBandKit_iOS.h>
#import <Cordova/CDVPlugin.h>

@interface MSBandPlugin : CDVPlugin<MSBClientManagerDelegate>
{

}

- (void)queryVersionInfo:(CDVInvokedUrlCommand*)command;


- (void)watchSensor:(CDVInvokedUrlCommand*)command;

- (void)unwatchSensor:(CDVInvokedUrlCommand*)command;

@end
