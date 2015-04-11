//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBSensorData.h"
#import "MSBSensorAccelData.h"
#import "MSBSensorGyroData.h"

@interface MSBSensorAccelGyroData : MSBSensorData

@property (nonatomic, readonly) MSBSensorAccelData *accel;
@property (nonatomic, readonly) MSBSensorGyroData *gyro;

@end
