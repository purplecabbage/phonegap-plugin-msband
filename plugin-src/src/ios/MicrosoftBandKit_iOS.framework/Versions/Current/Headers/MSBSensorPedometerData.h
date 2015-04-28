//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"

@interface MSBSensorPedometerData : MSBSensorData

@property (nonatomic, readonly) int totalSteps;
@property (nonatomic, readonly) int stepRate;
@property (nonatomic, readonly) int movementRate;
@property (nonatomic, readonly) int totalMovements;
@property (nonatomic, readonly) int movementMode;

@end
