//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageElementData.h"

@interface MSBPageTextData : MSBPageElementData

@property (nonatomic, readonly) NSString  *text;

+ (MSBPageTextData *)pageTextDataWithElementId:(MSBPageElementIdentifier)elementId text:(NSString *)text error:(NSError **)pError;

@end
