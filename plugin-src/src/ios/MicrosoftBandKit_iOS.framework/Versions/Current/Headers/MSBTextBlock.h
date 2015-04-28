//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBTextElement.h"
#import "MSBPageEnums.h"


typedef UInt16  MSBTextBlockBaseline;



@interface MSBTextBlock : MSBTextElement

@property(nonatomic, assign)    MSBTextBlockFont                    font;
@property(nonatomic, assign)    MSBTextBlockBaseline                baseline;
@property(nonatomic, assign)    MSBTextBlockBaselineAlignment       baselineAlignment;

-(id)initWithRect:(MSBRect *)rect font:(MSBTextBlockFont)font baseline:(MSBTextBlockBaseline)baseline;

@end
