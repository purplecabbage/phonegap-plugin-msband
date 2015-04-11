//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"

typedef NS_ENUM(NSUInteger, MSBHeartRateQuality)
{
    MSBHearRateAcquiring,
    MSBHeartRateLocked
};

@interface MSBSensorHeartRateData : MSBSensorData

@property (nonatomic, readonly) NSUInteger heartRate;
@property (nonatomic, readonly) MSBHeartRateQuality quality;

@end
