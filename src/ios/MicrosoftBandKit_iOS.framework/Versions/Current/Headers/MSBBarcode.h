//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import "MSBPageElement.h"
#import "MSBPageEnums.h"


@interface MSBBarcode : MSBPageElement

@property(nonatomic, assign)        MSBBarcodeType     barcodeType;

- (id)initWithRect:(MSBRect *)rect barcodeType:(MSBBarcodeType)type;

@end
