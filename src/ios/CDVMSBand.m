

#import "CDVMSBand.h"

@interface MSBandPlugin () {}
@property (nonatomic, weak) MSBClient *client;
@end

@implementation MSBandPlugin

-(void)connect:(CDVInvokedUrlCommand*)command
{
	[[MSBClientManager sharedManager] setDelegate:self];
	NSArray *attachedClients = [[MSBClientManager sharedManager] attachedClients];

	_client = [attachedClients firstObject];
	if (_client)
	{
        // connect to it
		[[MSBClientManager sharedManager] connectClient:_client];
	}
    else {
        
        // TODO: no bands detected
    }
}

// Note: The delegate methods of MSBClientManagerDelegate protocol are called in the main thread.
-(void)clientManager:(MSBClientManager *)cm clientDidConnect:(MSBClient *)client
{
    // handle connected event.
    self.client = client;
    // TODO: notify js
}

-(void)clientManager:(MSBClientManager *)cm clientDidDisconnect:(MSBClient *)client
{
	// handle disconnected event.
    self.client = nil;
}

-(void)clientManager:(MSBClientManager *)cm client:(MSBClient *)client didFailToConnectWithError:(NSError *)error
{
	// handle failure event.
    // TODO: notify js
}


- (void)queryVersionInfo:(CDVInvokedUrlCommand*)command 
{
    __weak MSBClient* weakClient = self.client;
    __block NSString* callbackId = [NSString stringWithString:command.callbackId ];
    
	// gets firmwareVersion and hardwareVersion
 	[weakClient firmwareVersionWithCompletionHandler:^(NSString *version,
        NSError *error){
        // create a dictionary to hold our results
        NSMutableDictionary* versionInfo = [NSMutableDictionary dictionaryWithCapacity:2];
        if (error) {
            // handle error
            dispatch_async(dispatch_get_main_queue(), ^{
                CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
            });
        }
        else {
            // handle success
            // set the frameworkVersion, and go get the hardware version
            [versionInfo setObject:[NSString stringWithString:version] forKey:@"frameworkVersion"];
            [weakClient hardwareVersionWithCompletionHandler:^(NSString *hwVersion,                                                NSError *error){
                if (error) {
                    // handle error
                    dispatch_async(dispatch_get_main_queue(), ^{
                        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
                        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
                    });
                }
                else {
                    // handle success
                    // got the hardware version
                    [versionInfo setObject:[NSString stringWithString:hwVersion] forKey:@"hardwareVersion"];
                    dispatch_async(dispatch_get_main_queue(), ^{
                        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:versionInfo];
                        
                        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
                    });
                }
            }];
        }
    }];
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
