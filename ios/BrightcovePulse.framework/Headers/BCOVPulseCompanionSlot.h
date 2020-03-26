//
// BCOVPulseCompanionSlot.h
// BrightcovePulse
//
// Copyright (c) 2020 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

/**
 * This class represents a companion slot to be populated with a matching companion ad.
 */
@interface BCOVPulseCompanionSlot : NSObject

/**
 * The designated initializer.
 *
 * @param width The width of the companion ad to match.
 * @param height The height of the companion ad to match.
 * @return An intialized instance.
 */
- (instancetype)initWithView:(UIView *)view width:(NSInteger)width height:(NSInteger)height NS_DESIGNATED_INITIALIZER;

@end
