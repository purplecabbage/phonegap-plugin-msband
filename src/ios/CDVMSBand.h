

#import <Cordova/CDVPlugin.h>

@interface MSBandPlugin : CDVPlugin
{

}


- (void)watchSensor:(CDVInvokedUrlCommand*)command;

- (void)unwatchSensor:(CDVInvokedUrlCommand*)command;

@end
