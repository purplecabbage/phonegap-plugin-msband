//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "MSBConstants.h"

@class MSBIcon;
@class MSBTheme;
@class MSBPageLayout;

@interface MSBTile : NSObject

@property(nonatomic, readonly)                  NSString            *name;
@property(nonatomic, readonly)                  NSUUID              *tileId;
@property(nonatomic, readonly)                  MSBIcon             *smallIcon;
@property(nonatomic, readonly)                  MSBIcon             *tileIcon;
@property(nonatomic, strong)                    MSBTheme            *theme;
@property(nonatomic, assign, getter=isBadgingEnabled)   BOOL        badgingEnabled;

/**
 * The length of pageIcons cannot exceeds MSBPageIconsMaxLength. The objects in pageIcons should be MSBIcon.
 */
@property(nonatomic, readonly)                  NSMutableArray      *pageIcons;

/**
 * The length of pageTemplates cannot exceeds MSBPageTemplatesMaxLength. The objects in pageTemplates must be MSBPageLayout.
 */
@property(nonatomic, readonly)                  NSMutableArray      *pageLayouts;


/*
 * Factory method for MSBTile class.
 * @param tileId        A unique identifier for the tile.
 * @param tileName      The display name of the tile.
 * @param tileIcon      The main tile icon.
 * @param smallIcon     The icon to be used in notifications and badging.
 * @param pError        An optional error reference.
 * @return              An instance of MSBTile.
 */
+ (MSBTile *)tileWithId:(NSUUID *)tileId name:(NSString *)tileName tileIcon:(MSBIcon *)tileIcon smallIcon:(MSBIcon *)smallIcon error:(NSError **)pError;

/**
 * Setter for name property. The name cannot be nil and cannot be longer than MSBTileNameMaxLength.
 */
- (BOOL)setName:(NSString *)tileName error:(NSError **)pError;

/**
 * Setter for tileIcon property. The icon cannot be nil and cannot have a dimension larger than MSBTileIconMaxWidthAndHeight.
 */
- (BOOL)setTileIcon:(MSBIcon *)tileIcon error:(NSError **)pError;

/**
 * Setter for smallIcon property. The icon cannot be nil and cannot have a dimension larger than MSBSmallTileIconMaxWidthAndHeight.
 */
- (BOOL)setSmallIcon:(MSBIcon *)smallIcon error:(NSError **)pError;

@end
