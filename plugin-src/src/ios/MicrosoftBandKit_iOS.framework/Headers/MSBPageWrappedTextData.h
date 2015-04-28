//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageElementData.h"

@interface MSBPageWrappedTextData : MSBPageElementData

@property (nonatomic, readonly) NSString  *text;

+ (MSBPageWrappedTextData *)pageWrappedTextDataWithElementId:(MSBPageElementIdentifier)elementId text:(NSString *)text error:(NSError **)pError;

@end
