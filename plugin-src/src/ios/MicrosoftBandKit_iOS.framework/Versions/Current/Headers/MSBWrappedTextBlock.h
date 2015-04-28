//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBTextElement.h"
#import "MSBPageEnums.h"



@interface MSBWrappedTextBlock : MSBTextElement

@property(nonatomic, assign)    MSBWrappedTextBlockFont            font;


-(id)initWithRect:(MSBRect *)rect font:(MSBWrappedTextBlockFont)font;

@end
