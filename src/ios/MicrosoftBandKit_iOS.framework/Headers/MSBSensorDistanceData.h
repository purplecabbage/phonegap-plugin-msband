//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"

typedef NS_ENUM(NSUInteger, MSBPedometerMode)
{
    MSBPedometerUnknown,
    MSBPedometerIdle,
    MSBPedometerWalking,
    MSBPedometerJogging,
    MSBPedometerRunning,
};

@interface MSBSensorDistanceData : MSBSensorData

@property (nonatomic, readonly) NSUInteger totalDistance;
@property (nonatomic, readonly) double speed;
@property (nonatomic, readonly) double pace;
@property (nonatomic, readonly) MSBPedometerMode pedometerMode;

@end
