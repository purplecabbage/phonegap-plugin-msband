//----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define MSB_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define MSB_EXTERN extern __attribute__((visibility ("default")))
#endif

MSB_EXTERN NSString *const MSBErrorCodeDomain;

typedef NS_ENUM(NSInteger, MSBNSErrorCodes) {
    //Device Errors
    MSBErrorCodeBandNotConnected = 100,
    MSBErrorCodeBandError,
    
    //Validation Errors
    MSBErrorCodeNullArgument = 200,
    MSBErrorCodeValueEmpty,
    MSBErrorCodeInvalidImage,
    MSBErrorCodeInvalidFilePath,
    MSBErrorCodeTileNameInvalidLength,
    MSBErrorCodeSDKUnsupported,
    MSBErrorCodeInvalidArgument,
    
    //Tile Errors
    MSBErrorCodeInvalidTile = 300,
    MSBErrorCodeInvalidTileID,
    MSBErrorCodeUserDeclinedTile,
    MSBErrorCodeMaxTiles,
    MSBErrorCodeTileAlreadyExist,
    MSBErrorCodeTileNotFound,
    
    //Unkown
    MSBErrorCodeUnknown = 900
};