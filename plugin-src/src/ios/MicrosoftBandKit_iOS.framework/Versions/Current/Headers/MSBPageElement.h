//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageEnums.h"


typedef UInt16  MSBPageElementIdentifier;


@class MSBColor;
@class MSBRect;
@class MSBMargins;


@interface MSBPageElement : NSObject

@property(nonatomic, assign)        MSBPageElementIdentifier                    elementId;
@property(nonatomic, strong)        MSBRect                                     *rect;
@property(nonatomic, strong)        MSBMargins                                  *margins;
@property(nonatomic, strong)        MSBColor                                    *color;
@property(nonatomic, assign)        MSBPageElementHorizontalAlignment           horizontalAlignment;
@property(nonatomic, assign)        MSBPageElementVerticalAlignment             verticalAlignment;
@property(nonatomic, assign)        MSBPageElementVisibility                    visibility;


@end
