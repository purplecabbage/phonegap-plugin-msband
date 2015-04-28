//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"

typedef enum
{
    MSBSensorBandContactNotWorn,
    MSBSensorBandContactWorn,
    MSBSensorBandContactUnknown
} MSBSensorBandContactState;

@interface MSBSensorBandContactData : MSBSensorData

@property (nonatomic, readonly) MSBSensorBandContactState wornState;

@end
