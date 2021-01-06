//
// BCOVPulseSessionProvider.h
// BrightcovePulse
//
// Copyright (c) 2021 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

@class OOContentMetadata;
@class OORequestSettings;


/**
 * Session provider implementation that delivers playback sessions with support
 * for Pulse.
 *
 * Instances of this class should not be created directly by clients of the
 * Brightcove Player SDK for iOS; instead use the `-[BCOVPlayerSDKManager createPulseSessionProviderWithPulseHost:contentMetadata:requestSettings:adContainer:companionSlots:upstreamSessionProvider:options:]`
 * factory method (which is added as a category method).
 */
@interface BCOVPulseSessionProvider : NSObject <BCOVPlaybackSessionProvider>

/**
 * Requests an extension of the current session.
 *
 * @param contentMetadata An OOContentMetadata that will be used to extend the
 * current session object.
 * @param requestSettings An OORequestSettings that will be used to extend the
 * current session.
 * @param onSuccess A success block if the session was successfully extended.
 */
- (void)requestSessionExtensionWithContentMetadata:(OOContentMetadata *)contentMetadata requestSettings:(OORequestSettings *)requestSettings success:(void(^)(void))onSuccess;

@end

