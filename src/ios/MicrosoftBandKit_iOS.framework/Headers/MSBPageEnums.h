//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#ifndef CargoKit_MSBPageEnums_h
#define CargoKit_MSBPageEnums_h


typedef NS_ENUM(NSUInteger, MSBPageElementHorizontalAlignment)
{
    MSBPageElementHorizontalAlignmentNone = 0,
    MSBPageElementHorizontalAlignmentLeft,
    MSBPageElementHorizontalAlignmentCenter,
    MSBPageElementHorizontalAlignmentRight
};


typedef NS_ENUM(NSUInteger, MSBPageElementVerticalAlignment)
{
    MSBPageElementVerticalAlignmentNone = 100,
    MSBPageElementVerticalAlignmentTop,
    MSBPageElementVerticalAlignmentCenter,
    MSBPageElementVerticalAlignmentBottom
};


typedef NS_ENUM(NSUInteger, MSBPageElementVisibility)
{
    MSBPageElementVisibilityHidden = 200,
    MSBPageElementVisibilityVisible
};


typedef NS_ENUM(NSUInteger, MSBFlowListOrientation)
{
    MSBFlowListOrientationHorizontal = 300,
    MSBFlowListOrientationVertical
};


typedef NS_ENUM(NSUInteger, MSBTextBlockBaselineAlignment)
{
    MSBTextBlockBaselineAlignmentAbsolute = 400,
    MSBTextBlockBaselineAlignmentRelative
};


typedef NS_ENUM(NSUInteger, MSBTextBlockFont)
{
    /// <summary>
    /// Smallest font, contains all characters supported by the device.
    /// </summary>
    MSBTextBlockFontSmall = 500,
    
    /// <summary>
    /// Medium sized font, contains alphanumeric characters as well as some symbols.
    /// </summary>
    MSBTextBlockFontMedium,
    
    /// <summary>
    /// Large font, contains numeric and some symbols.
    /// </summary>
    MSBTextBlockFontLarge,
    
    /// <summary>
    /// Extra large font contains numeric characters and a very small set of symbols.
    /// </summary>
    MSBTextBlockFontExtraLargeNumbers,
    
    /// <summary>
    /// Extra Large Bold contains numbers and a very small subset of symbols.
    /// </summary>
    MSBTextBlockFontExtraLargeNumbersBold
};


typedef NS_ENUM(UInt32, MSBWrappedTextBlockFont)
{
    /// <summary>
    /// Smallest font, contains all characters supported by the device.
    /// </summary>
    MSBWrappedTextBlockFontSmall = 600,
    
    /// <summary>
    /// Medium sized font, contains alphanumeric characters as well as some symbols.
    /// </summary>
    MSBWrappedTextBlockFontMedium
};


typedef NS_ENUM(UInt32, MSBTextBlockLayoutElementWidth)
{
    MSBTextBlockLayoutElementWidthFixed = 700,
    MSBTextBlockLayoutElementWidthAuto
};


typedef NS_ENUM(UInt16, MSBBarcodeType)
{
    MSBBarcodeTypePDF417 = 800,
    MSBBarcodeTypeCODE39
};

#endif
