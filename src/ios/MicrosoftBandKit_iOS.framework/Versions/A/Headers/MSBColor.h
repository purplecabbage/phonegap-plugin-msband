//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif




@class MSBError;

@interface MSBColor : NSObject


#if TARGET_OS_IPHONE

+ (id)colorWithUIColor:(UIColor *)color error:(NSError **)pError;
- (UIColor *)UIColor;

#else

+ (id)colorWithNSColor:(NSColor *)color error:(NSError **)pError;
- (NSColor *)NSColor;

#endif

+ (MSBColor *)colorWithRed:(NSUInteger)red green:(NSUInteger)green blue:(NSUInteger)blue;

@end
