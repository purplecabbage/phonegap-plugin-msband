//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"

typedef NS_ENUM(NSUInteger, MSBUVIndexLevel)
{
    MSBUVLevelNone,
    MSBUVLevelLow,
    MSBUVLevelMedium,
    MSBUVLevelHigh,
    MSBUVLevelVeryHigh
};

@interface MSBSensorUVData : MSBSensorData

@property (nonatomic, readonly) MSBUVIndexLevel uvIndexLevel;

@end
