//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageElementData.h"

@interface MSBPageBarcodeCode39Data : MSBPageElementData

@property (nonatomic, readonly) NSString  *value;

+ (MSBPageBarcodeCode39Data *)pageBarcodeCode39DataWithElementId:(MSBPageElementIdentifier)elementId value:(NSString *)value error:(NSError **)pError;

@end
