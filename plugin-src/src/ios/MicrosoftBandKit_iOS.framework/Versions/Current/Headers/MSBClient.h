//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
@protocol MSBTileManagerProtocol;
@protocol MSBPersonalizationManagerProtocol;
@protocol MSBNotificationManagerProtocol;
@protocol MSBSensorManagerProtocol;

@interface MSBClient : NSObject

@property (readonly) NSString 									      *name;
@property (readonly) NSUUID 									      *connectionIdentifier;
@property (readonly) BOOL 										      isDeviceConnected;

@property (nonatomic, readonly) id<MSBTileManagerProtocol>            tileManager;
@property (nonatomic, readonly) id<MSBPersonalizationManagerProtocol> personalizationManager;
@property (nonatomic, readonly) id<MSBNotificationManagerProtocol>    notificationManager;
@property (nonatomic, readonly) id<MSBSensorManagerProtocol>          sensorManager;

/**
 Get the the device firmware version asynchronously
 @param completionHandler
 */
- (void)firmwareVersionWithCompletionHandler:(void(^)(NSString *version, NSError *error))completionHandler;

/**
 Get the the hardware version asynchronously
 @param completionHandler
 */
- (void)hardwareVersionWithCompletionHandler:(void(^)(NSString *version, NSError *error))completionHandler;
@end
