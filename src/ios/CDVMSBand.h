

#import <Cordova/CDVPlugin.h>

@interface MSBandPlugin : CDVPlugin
{

}

- (void)queryVersionInfo:(CDVInvokedUrlCommand*)command;


- (void)watchSensor:(CDVInvokedUrlCommand*)command;

- (void)unwatchSensor:(CDVInvokedUrlCommand*)command;

@end
