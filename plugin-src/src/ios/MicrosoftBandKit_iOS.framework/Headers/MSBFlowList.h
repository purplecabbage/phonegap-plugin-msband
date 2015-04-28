//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPagePanel.h"
#import "MSBPageEnums.h"


@interface MSBFlowList : MSBPagePanel

@property(nonatomic, assign)        MSBFlowListOrientation         orientation;

-(id)initWithRect:(MSBRect *)rect orientation:(MSBFlowListOrientation)orientation;

@end
