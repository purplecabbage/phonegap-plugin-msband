//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@interface MSBPageData : NSObject

@property (nonatomic, readonly) NSUUID           *pageId;
@property (nonatomic, readonly) NSUInteger        pageTemplateIndex;
@property (nonatomic, readonly) NSArray          *values;

/*
 * Factory method for MSBPageInfo class.
 * @param pageId A unique identifier for the page.
 * @param templateIndex The index of the template.
 * @param value An array of MSBPageElementValues to update.
 * @return An instance of MSBPageInfo.
 */
+ (MSBPageData *)pageDataWithId:(NSUUID *)pageId templateIndex:(NSUInteger)templateIndex value:(NSArray *)values;

@end
