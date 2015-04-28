//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@interface MSBMargins : NSObject

@property(nonatomic, assign)    UInt16      left;
@property(nonatomic, assign)    UInt16      top;
@property(nonatomic, assign)    UInt16      right;
@property(nonatomic, assign)    UInt16      bottom;

+(MSBMargins *)marginsWithLeft:(UInt16)left top:(UInt16)top right:(UInt16)right bottom:(UInt16)bottom;

@end
