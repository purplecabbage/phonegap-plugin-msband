

#import "CDVMSBand.h"

@interface MSBandPlugin () {}
@property (nonatomic, weak) MSBClient *client;
@end

@implementation MSBandPlugin

-(void)initialize
{
//	[[MSBClientManager sharedManager] setDelegate:self];
//	NSArray *attachedClients = [[MSBClientManager sharedManager] attachedClients];
//
//	MSBClient *client = [attachedClients firstObject];
//	if (client)
//	{
//		[[MSBClientManager sharedManager] connectClient:client];
//	}
}

// Note: The delegate methods of MSBClientManagerDelegate protocol are called in the main thread.
-(void)clientManager:(MSBClientManager *)cm clientDidConnect:(MSBClient *)client
{
// handle connected event.
}

-(void)clientManager:(MSBClientManager *)cm clientDidDisconnect:(MSBClient *)client
{
	// handle disconnected event.
}

-(void)clientManager:(MSBClientManager *)cm client:(MSBClient *)client didFailToConnectWithError:(NSError *)error
{
	// handle failure event.
}


- (void)queryVersionInfo:(CDVInvokedUrlCommand*)command 
{
	// gets firmwareVersion and hardwareVersion
// 	[self.client firmwareVersionWithCompletionHandler:^(NSString *version,
// NSError *error){
// if (error)
//  // handle error
// else
//  // handle success
// }];
// [self.client hardwareVersionWithCompletionHandler:^(NSString *version,
// NSError *error){
// if (error)
//  // handle error
// else
//  // handle success
// }];
}

- (void)watchSensor:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)unwatchSensor:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
