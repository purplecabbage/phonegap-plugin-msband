//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@class MSBColor;

@interface MSBTheme : NSObject

@property(nonatomic, strong)    MSBColor     *baseColor;
@property(nonatomic, strong)    MSBColor     *highLightColor;
@property(nonatomic, strong)    MSBColor     *lowLightColor;
@property(nonatomic, strong)    MSBColor     *secondaryTextColor;
@property(nonatomic, strong)    MSBColor     *highContrastColor;
@property(nonatomic, strong)    MSBColor     *mutedColor;

+ (MSBTheme *)themeWithBaseColor:(MSBColor *)baseColor highLightColor:(MSBColor *)highLightColor lowLightColor:(MSBColor *)lowLightColor secondaryTextColor:(MSBColor *)secondaryTextColor highContrastColor:(MSBColor *)highContrastColor mutedColor:(MSBColor *)mutedColor;
@end
