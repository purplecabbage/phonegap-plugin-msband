//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

/**
 Band Name Max Length
 */
extern int const MSBBandNameMaxLength;

/**
 * Notification when Bluetooth is turned on or off.
 */
extern NSString * const MSBClientManagerBluetoothPowerNotification;

/**
 * Key of the userInfo in MSBClientManagerBluetoothStateNotification.
 * Value contains a NSNumber of bool.
 */
extern NSString * const MSBClientManagerBluetoothPowerKey;

/****************************
 Notification constants
 ****************************/

/**
 VibrationType Constant of
 MSBNotificationManager::vibrateWithType:completionHandler:
 */
typedef NS_ENUM(NSUInteger, MSBVibrationType)
{
    MSBVibrationTypeNotificationOneTone = 0x07,
    MSBVibrationTypeNotificationTwoTone = 0x10,
    MSBVibrationTypeNotificationAlarm   = 0x11,
    MSBVibrationTypeNotificationTimer   = 0x12,
    MSBVibrationTypeOneToneHigh         = 0x1B,
    MSBVibrationTypeTwoToneHigh         = 0x1D,
    MSBVibrationTypeThreeToneHigh       = 0x1C,
    MSBVibrationTypeRampUp              = 0x05,
    MSBVibrationTypeRampDown            = 0x04
};


/**
 Flags Constants of
 MSBNotificationManager::sendMessageWithTileID:title:body:timeStamp:flags:completionHandler:
 */
typedef NS_ENUM(UInt8, MSBNotificationMessageFlags)
{
    MSBNotificationMessageFlagsNone                     = 0,
    MSBNotificationMessageFlagsShowDialog               = 1,
};

extern int const MSBNotificationMessageTitleLengthMax;
extern int const MSBNotificationMessageBodyLengthMax;

extern int const MSBNotificationDialogTitleLengthMax;
extern int const MSBNotificationDialogBodyLengthMax;

/****************************
 Personalization constants
 ****************************/



/****************************
 Tile constants
 ****************************/

// Maximum width and height of tile icon and small tile icon.
extern const int MSBTileIconMaxWidthAndHeight;
extern const int MSBSmallTileIconMaxWidthAndHeight;
extern const int MSBTileNameMaxLength;

extern const int MSBPageIconsMaxLength;
extern const int MSBPageTemplatesMaxLength;