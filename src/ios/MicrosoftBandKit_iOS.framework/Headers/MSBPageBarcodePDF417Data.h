//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageElementData.h"

@interface MSBPageBarcodePDF417Data : MSBPageElementData

@property (nonatomic, readonly) NSString  *value;

+ (MSBPageBarcodePDF417Data *)pageBarcodePDF417DataWithElementId:(MSBPageElementIdentifier)elementId value:(NSString *)value error:(NSError **)pError;

@end
