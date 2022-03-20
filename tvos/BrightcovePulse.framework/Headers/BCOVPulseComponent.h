//
// BCOVPulseComponent.h
// BrightcovePulse
//
// Copyright (c) 2022 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>

@class OOContentMetadata;
@class OORequestSettings;
@protocol OOPulseSession;

/**
 *  The user's option dictionary key for the Pulse Playback Session Delegate.
 */
extern NSString * const kBCOVPulseOptionPulsePlaybackSessionDelegateKey;

/**
 * The user's option dictionary key for the Pulse device container, if any; can be nil.
 */
extern NSString * const kBCOVPulseOptionPulseDeviceContainerKey;

/**
 * The user's option dictionary key for the Pulse persistent user id, if any; can be nil.
 */
extern NSString * const kBCOVPulseOptionPulsePersistentIdKey;


/**
 * A delegate protocol for users of the Brightcove Pulse advertising plugin.
 * This delegate allows you to override the content metadata and request settings
 * dynamically.
 */
@protocol BCOVPulsePlaybackSessionDelegate <NSObject>

/**
 * Called immediately before the Pulse Plugin calls `-[OOPulse startSessionWithDelegate:]`
 * to allow the user to first modify the ads request object, for example, to change
 * the category property.
 *
 *  @param video The current video content.
 *  @param pulseHost The Pulse hostname.
 *  @param contentMetadata  The content metadata.
 *  @param requestSettings  The request settings.
 *  @return The newly created Pulse ad session.
 */
- (id<OOPulseSession>)createSessionForVideo:(BCOVVideo *)video withPulseHost:(NSString *)pulseHost contentMetadata:(OOContentMetadata *)contentMetadata requestSettings:(OORequestSettings *)requestSettings;

@end


@interface BCOVPulseComponent : NSObject <BCOVComponent, BCOVComponentIdentity>

+ (NSString *)versionIdentifier;

@end

/**
 * Category methods added to BCOVPlayerSDKManager to support Pulse.
 */
@interface BCOVPlayerSDKManager (BCOVPulseAdditions)

/**
 * Creates and returns a new playback controller with the specified Pulse host,
 * OOContentMetadata object, OORequestSettings object, and user options. The
 * returned playback controller will be configured with a Pulse session provider.
 *
 * @param pulseHost The Pulse hostname for the client account being used.
 * @param contentMetadata An OOContentMetadata that will be used to configure the
 * session object used by the returned playback controller.
 * @param requestSettings An OORequestSettings that will be used to configure the
 * session object used by the returned playback controller.
 * @param adContainer The view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param companionSlots An array of BCOVPulseCompanionSlots to be populated.
 * @param strategy A view strategy that determines the view for the returned
 * playback controller.
 * @param options An NSDictionary of Pulse options. Can be nil or empty. The only
 *  valid option keys are
 *      kBCOVPulseOptionPulsePlaybackSessionDelegateKey
 *      kBCOVPulseOptionPulseDeviceContainerKey
 *      kBCOVPulseOptionPulsePersistentIdKey
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createPulsePlaybackControllerWithPulseHost:(NSString *)pulseHost contentMetadata:(OOContentMetadata *)contentMetadata requestSettings:(OORequestSettings *)requestSettings adContainer:(UIView *)adContainer companionSlots:(NSArray *)companionSlots viewStrategy:(BCOVPlaybackControllerViewStrategy)strategy options:(NSDictionary *)options;

/**
 * Creates and returns a new BCOVPulseSessionProvider with the specified
 * parameters.
 *
 * @param pulseHost The Pulse hostname for the client account being used.
 * @param contentMetadata An OOContentMetadata that will be used to configure the
 * session object used by the returned playback controller.
 * @param requestSettings An OORequestSettings that will be used to configure the
 * session object used by the returned playback controller.
 * @param adContainer The view in which the ad will be displayed and the ad
 * information UI will be rendered.
 * @param companionSlots An array of BCOVPulseCompanionSlots to be populated.
 * @param provider A session provider to attach upstream and deliver playback
 * sessions to the returned session provider.
 * @param options An NSDictionary of Pulse options. Can be nil or empty. The only
 *  valid option keys are
 *      kBCOVPulseOptionPulsePlaybackSessionDelegateKey
 *      kBCOVPulseOptionPulseDeviceContainerKey
 *      kBCOVPulseOptionPulsePersistentIdKey
 * @return A new BCOVPulseSessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createPulseSessionProviderWithPulseHost:(NSString *)pulseHost contentMetadata:(OOContentMetadata *)contentMetadata requestSettings:(OORequestSettings *)requestSettings adContainer:(UIView *)adContainer companionSlots:(NSArray *)companionSlots upstreamSessionProvider:(id<BCOVPlaybackSessionProvider>)provider options:(NSDictionary *)options;

@end


/**
 * Pulse specific methods for the plugin context.
 */
@interface BCOVSessionProviderExtension (BCOVPulseAdditions)

/**
 * Plays the video.
 *
 * On first play, before playing content, the session will process all preroll ads before starting
 * the content.
 */
- (void)pulse_play;

/**
 * Pauses the video.
 */
- (void)pulse_pause;


/**
 * Extends the current session.
 *
 * @param contentMetadata An OOContentMetadata that will be used to extend the
 * current session object.
 * @param requestSettings An OORequestSettings that will be used to extend the
 * current session object.
 * @param onSuccess A callback to confirm that session was successfully extended.
 */
- (void)pulse_requestSessionExtensionWithContentMetadata:(OOContentMetadata *)contentMetadata requestSettings:(OORequestSettings *)requestSettings success:(void(^)(void))onSuccess;

@end
