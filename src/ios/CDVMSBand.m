

#import "CDVMSBand.h"

@interface MSBandPlugin () {}
@property (nonatomic, weak) MSBClient *client;
@property (nonatomic, retain) NSString* connectCallbackId;
@end

@implementation MSBandPlugin

-(void)connect:(CDVInvokedUrlCommand*)command
{
	[[MSBClientManager sharedManager] setDelegate:self];
	NSArray *attachedClients = [[MSBClientManager sharedManager] attachedClients];
    
    self.connectCallbackId = [NSString stringWithString:command.callbackId ];

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
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.connectCallbackId];
    
}

-(void)clientManager:(MSBClientManager *)cm clientDidDisconnect:(MSBClient *)client
{
	// handle disconnected event.
    // TODO: pass back something to say that this is a disconnect, and different fromt the error below.
    self.client = nil;
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.connectCallbackId];
}

-(void)clientManager:(MSBClientManager *)cm client:(MSBClient *)client didFailToConnectWithError:(NSError *)error
{
    // handle connect error event.
    // TODO: pass back resultCode based on this type of error
    self.client = nil;
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.connectCallbackId];
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
    __block NSString* callbackId = [NSString stringWithString:command.callbackId ];
    __block NSString* event = [NSString stringWithString:(NSString*)command.arguments[0]];
    
    
    if([event compare:@"bandcontact"] == 0) {

    }
    else if([event compare:@"accelerometer"] == 0) {
        [self.client.sensorManager startAccelerometerUpdatesToQueue:nil errorRef:nil withHandler:^(MSBSensorAccelData *accelerometerData, NSError *error) {
            
            
            NSMutableDictionary* accelProps = [NSMutableDictionary dictionaryWithCapacity:4];
            
            [accelProps setValue:[NSNumber numberWithDouble:accelerometerData.x] forKey:@"x"];
            [accelProps setValue:[NSNumber numberWithDouble:accelerometerData.y] forKey:@"y"];
            [accelProps setValue:[NSNumber numberWithDouble:accelerometerData.z] forKey:@"z"];
            [accelProps setValue:[NSNumber numberWithDouble:([[NSDate date] timeIntervalSince1970] * 1000)] forKey:@"timestamp"];
            
            NSMutableDictionary* payload = [NSMutableDictionary dictionaryWithCapacity:4];
            [payload setValue:event forKey:@"event"];
            [payload setValue:accelProps forKey:@"reading"];
            
            
            
            CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:payload];
            [result setKeepCallback:[NSNumber numberWithBool:YES]];
            [self.commandDelegate sendPluginResult:result callbackId:callbackId];
        }];
        
    }
    else if([event compare:@"gyroscope"] == 0) {
        
    }
    else if([event compare:@"distance"] == 0) {
        
    }
    else if([event compare:@"heartrate"] == 0) {
        
    }
    else if([event compare:@"pedometer"] == 0) {
        
    }
    else if([event compare:@"skintemperature"] == 0) {
        
    }
    else if([event compare:@"uvlevel"] == 0) {
        
    }
//    dispatch_async(dispatch_get_main_queue(), ^{
//        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
//        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
//    });
}

- (void)unwatchSensor:(CDVInvokedUrlCommand*)command
{
    __block NSString* callbackId = [NSString stringWithString:command.callbackId ];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    });
}

@end
