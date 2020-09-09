# Pulse Plugin for Brightcove Player SDK for iOS, version 6.7.11.1278

Requirements
============

- Xcode 11.0+
- ARC

Supported Platforms
==========
iOS 11.0 and above.
tvOS 11.0 and above

Installation
==========
Pulse Plugin for Brightcove Player SDK provides a dynamic library framework for installation.

The Pulse plugin supports INVIDI Technologies Pulse SDK version 2.5.20.1.0 for iOS and version 2.5.19.9.0 for tvOS, [Pulse iOS and tvOS SDK Reference][pulselatest]. The Podspec for the Pulse Plugin for Brightcove Player SDK references [Pulse SDK Release History][pulsesdkchangelog]. 

CocoaPods
----------

You can use [CocoaPods][cocoapods] to add the Pulse Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-Pulse` podspec [here][podspecs]. The PulseSDK needs to be added to your project, download the latest version [here][pulsesdkresource]. CocoaPods 1.0 or newer is required.

CocoaPod Podfile example:

```
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '11.0'
use_frameworks!

target 'MyApp' do
	pod 'Brightcove-Player-Pulse'
end
```

Manual
----------

To add the Pulse Plugin for Brightcove Player SDK to your project manually:

1. Download the latest zipped Brightcove Player SDK framework from the [releases page][bcovsdkreleases].
1. Download the latest zipped Pulse Plugin for Brightcove Player SDK framework from the [releases page][bcovpulsereleases].
1. Download the [PulseSDK][pulsesdkresource] framework.
1. On the "General" tab of your application target, add the **dynamic** framework, BrightcovePlayerSDK.framework, from the Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The dynamic framework, BrightcovePlayerSDK.framework, is found in the ios/dynamic directory of the download. The _Embed_ setting for the framework must be "_Embed & Sign_".
1. On the "General" tab of your application target, add BrightcovePulse.framework from the Pulse Plugin for Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the framework must be "_Embed & Sign_".
1. On the "General" tab of your application target, add PulseSDK.framework from the INVIDI Technologies download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the framework must be "_Embed & Sign_".
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.
1. On the "Build Settings" tab of your application target:
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.

Imports
----------
The Pulse Plugin for Brightcove Player SDK can be imported into code a few different ways; `@import BrightcovePulse;`, `#import <BrightcovePulse/BrightcovePulse.h>` or `#import <BrightcovePulse/[specific class].h>`. You can import the `PulseSDK` and `BrightcovePlayerSDK` modules in similar fashion.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-Pulse
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/releases

Quick Start
==========
The BrightcovePulse plugin is a bridge between [PulseSDK][pulsesdkresource] and the [Brightcove Player SDK for iOS][bcovsdk]. This snippet shows its basic usage with Server Side Ad Rules.

    [1] OOContentMetadata *contentMetadata = [OOContentMetadata new];
        contentMetadata.category = <category>;
        contentMetadata.tags     = @[ <tag1>, <tag2>, ..., <tagN> ];
        contentMetadata.flags    = @[ <flag1>, <flag2>, ..., <flagN> ];

        OORequestSettings *requestSettings = [OORequestSettings new];
        requestSettings.linearPlaybackPositions = @[ @(position1), @(position2), ..., @(positionN) ];
    
        NSString *pulseHost = <pulse domain>;
    
    [2] NSDictionary *pulseOptions = @{ kBCOVPulseOptionPulsePlaybackSessionDelegateKey: self,
                                        kBCOVPulseOptionPulsePersistentIdKey: [NSUUID.UUID UUIDString]
                                      };

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller =
    [3]         [manager createPulsePlaybackControllerWithPulseHost:pulseHost
                                                    contentMetadata:contentMetadata
                                                    requestSettings:requestSettings
                                                        adContainer:self.playerView.contentOverlayView
                                                     companionSlots:nil
                                                       viewStrategy:nil
                                                            options:pulseOptions];
        controller.delegate = self;

        [videoContainerView addSubview:controller.view];  

        NSString *policyKey = <your-policy-key>;
        NSString *accountId = <your-account-id>;
        NSString *videoID = <your-video-id>;
        BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:accountID
                                                                                    policyKey:policyKey];
        [playbackService findVideoWithVideoID:videoID
                                   parameters:nil
                                   completion:^(BCOVVideo    *video,
                                                NSDictionary *jsonResponse,
                                                NSError      *error) {
            [controller setVideos:@[ video ]];
            [controller play];
        }];

Breaking the code down into steps:

1. Create the same [OOContentMetadata](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OOContentMetadata.html), [OORequestSettings](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OORequestSettings.html) that you would create if you were using INVIDI Technologies's Pulse iOS SDK directly. The Pulse Plugin requires a valid domain and an UIView container to display the ads.
2. Optionally, the plugin can receive a NSDictionary with properties to be used in the plugin. The available keys are `kBCOVPulseOptionPulsePlaybackSessionDelegateKey`, `kBCOVPulseOptionPulseDeviceContainerKey` and `kBCOVPulseOptionPulsePersistentIdKey`. To override the Pulse Session, the PulsePlaybackSessionDelegate needs to be implemented, passing the `kBCOVPulseOptionPulsePlaybackSessionDelegateKey` with the class that implements the method.
3. BrightcovePulse adds some category methods to BCOVPlaybackManager. The first of these is `-createPulsePlaybackControllerWithPulseHost:contentMetadata:requestSettings:adContainer:companionSlots:viewStrategy:options:`. Use this method to create your playback controller. 

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at the [Brightcove Native Player SDKs][forum] Google group.

[pulselatest]: http://pulse-sdks.videoplaza.com/ios_2/latest/
[pulsesdkresource]: https://docs.videoplaza.com/oadtech/ad_serving/dg/pulse_sdks_resources.html
[pulsesdkchangelog]: http://pulse-sdks.videoplaza.com/ios_2/latest/changelog.html
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[bcovsdkreleases]: https://github.com/brightcove/brightcove-player-sdk-ios/releases
[bcovpulse]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse
[bcovpulsereleases]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/releases
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Play and Pause
==========
The Brightcove Pulse Plugin implements custom play and pause logic to ensure the smoothest possible ad experience. Therefore, you will need to make sure that you use the play method on the `BCOVPlaybackController` or the `-[BCOVSessionProviderExtension pulse_play]` or `-[BCOVSessionProviderExtension pulse_pause]` ([BCOVSessionProviderExtension][BCOVPulseComponent]), and not the AVPlayer.

As an example, calling play for the first time on `BCOVPlaybackController` allows BCOVPulse to process preroll ads without any of the content playing before the preroll. For more information on how BCOVPulse overrides the default `BCOVPlaybackController` methods, please check out [BCOVSessionProviderExtension][BCOVPulseComponent].

[BCOVPulseComponent]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/blob/master/ios/BrightcovePulse.framework/Headers/BCOVPulseComponent.h

Using the Built-In PlayerUI
==========
In your `UIViewController`, create a `BCOVPUIPlayerView` property called the player view, to contain the playback controls, the video content view, and a special view where Pulse can display its ads.

```
// PlayerUI's player view
@property (nonatomic) BCOVPUIPlayerView *playerView;
```

Then create your player view; supply a nil playback controller which will be added later. This player view contains both the video content view and the view that displays playback controls and ad controls. This setup is the same no matter what plugin you are using. Set up the player view to match the video container from your layout (`videoView`) when it resizes.

```
// Create and configure Control View.
BCOVPUIBasicControlView *controlView = [BCOVPUIBasicControlView basicControlViewWithVODLayout];
    
// Create the player view with a nil playback controller.
self.playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil options:nil controlsView:controlView];
// Add BCOVPUIPlayerView to your video view.
[self.videoView addSubview:self.playerView];
```

You'll need to set up the layout for the player view, you can do this with Auto Layout or the older Springs & Struts method. 

**Springs & Struts**
```
self.playerView.frame = self.videoView.bounds;
self.playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
```

**Auto Layout**
```
self.playerView.translatesAutoresizingMaskIntoConstraints = NO;
[NSLayoutConstraint activateConstraints:@[
                                          [self.playerView.topAnchor constraintEqualToAnchor:self.videoView.topAnchor],
                                          [self.playerView.rightAnchor constraintEqualToAnchor:self.videoView.rightAnchor],
                                          [self.playerView.leftAnchor constraintEqualToAnchor:self.videoView.leftAnchor],
                                          [self.playerView.bottomAnchor constraintEqualToAnchor:self.videoView.bottomAnchor],
                                         ]];
```

Creating the playback controller is specific to Pulse. Create your playback controller as you did above, but instead of your video container view, pass in the `contentOverlayView` from the player view as your `adContainer`. The `contentOverlayView` is a special view used for overlaying views on the main video content. You should also use `nil` instead of `[manager defaultControlsViewStrategy]` if you were using that as your `viewStrategy` (this was the older method for using built-in controls).

```
// Create the playback controller.
id<BCOVPlaybackController> controller =
                [manager createPulsePlaybackControllerWithPulseHost:pulseHost
                                                    contentMetadata:contentMetadata
                                                    requestSettings:requestSettings
                                                        adContainer:self.playerView.contentOverlayView
                                                     companionSlots:nil
                                                       viewStrategy:nil
                                                            options:nil];
controller.delegate = self;

// Assign new playback controller to the player view.
// This associates the playerController's session with the PlayerUI.
// You can keep this player view around and assign new
// playback controllers to it as they are created.
self.playerView.playbackController = self.playbackController;
```

Now, when playing video with ads, you will see the PlayerUI controls while playing video content, plus ad markers on the timeline scrubber.

The PlayerUI is highly customizable. For more information and sample code, please see **Custom Layouts** section in the README.md file of the [Brightcove Native Player SDK repository][BCOVSDK].

[BCOVSDK]: https://github.com/brightcove/brightcove-player-sdk-ios

Customizing Plugin Behavior
==========
There are a couple of configuration points in BCOVPulse. You can combine BCOVPulse with another plugin for the Brightcove Player SDK for iOS, you can create a custom view strategy, and you can override the current ads request.

BCOVPulsePlaybackSessionDelegate
----------
The `BCOVPulsePlaybackSessionDelegate` protocol provides a way for the BrightcovePulse plugin to communicate with the host application. This delegate allows you to override the content metadata and request settings before the session starts. 

The `UIViewController` needs to adopt the `BCOVPulsePlaybackSessionDelegate` protocol.

```
@interface ViewController () <BCOVPulsePlaybackSessionDelegate>
```

Create a NSDictionary passing the `kBCOVPulseOptionPulsePlaybackSessionDelegateKey` with the class that will implement the method to override the session.

```
NSDictionary *pulseOptions = @{ kBCOVPulseOptionPulsePlaybackSessionDelegateKey: self };
```

Create a `BCOVPlaybackSessionProvider` or `BCOVPlaybackController` for Pulse using the methods in `BCOVPlaybackManager`, remember to pass the dictionary created in the previous step. This example uses a playback controller.

```
BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
id<BCOVPlaybackController> controller = 
            [manager createPulsePlaybackControllerWithPulseHost:pulseHost
                                                contentMetadata:[OOContentMetadata new]
                                                requestSettings:[OORequestSettings new]
                                                    adContainer:self.playerView.contentOverlayView
                                                 companionSlots:nil
                                                   viewStrategy:nil
                                                        options:pulseOptions];
```
[category]: http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OOContentMetadata.html#/c:objc(cs)OOContentMetadata(py)category
[linearplaybackpositions]: http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OORequestSettings.html#/c:objc(cs)OORequestSettings(py)linearPlaybackPositions

The `createSessionForVideo:withPulseHost:contentMetadata:requestSettings:` method provides the current video, host domain, [content metadata](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OOContentMetadata.html) and [request settings](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OORequestSettings.html) for the session. In this example, the previous objects were empty and will be overriden with a new [category][category] and [linear playback positions][linearplaybackpositions] array.

 ```
 - (id<OOPulseSession>)createSessionForVideo:(BCOVVideo *)video 
                               withPulseHost:(NSString *)pulseHost 
                              contentMetadata:(OOContentMetadata *)contentMetadata 
                             requestSettings:(OORequestSettings *)requestSettings
  { 
    // Override the content metadata.
    contentMetadata.category = @"new_category_for_midrolls";
    
    // Override the request settings.
    requestSettings.linearPlaybackPositions = @[ @(15) ];
    return [OOPulse sessionWithContentMetadata:contentMetadata requestSettings:requestSettings];
}
```

View Strategy
----------
You can provide a custom view strategy to the BCOVPlaybackManager when you are constructing your playback controller or session provider, rather than specify the defaultControlsViewStrategy directly. With a custom view strategy, the ad container view and ad companion slots can be tied with the video content view. This is an example of custom view strategy.

    BCOVPlaybackControllerViewStrategy customViewStrategy = ^UIView* (UIView *view, id<BCOVPlaybackController> playbackController){
        
        BCOVPlaybackControllerViewStrategy defaultControlsViewStrategy = [playbackManager defaultControlsViewStrategy];
        UIView *contentAndDefaultControlsView = defaultControlsViewStrategy(view, playbackController);
        
        [<UIView of video container> addSubview:contentAndDefaultControlsView];
        
        return <UIView of video container>;
    };


Composing Session Providers
----------
If you are using more than one plugin to the Brightcove Player SDK for iOS that needs to create a customized playback controller, you must instead compose a chain of session providers and pass the final session provider to the `-[BCOVPlayerSDKManager createPlaybackControllerWithSessionProvider:viewStrategy:]` method.

When composing session providers, the session preloading can be enabled from [`BCOVBasicSessionProvider`][basicprovider].

[basicprovider]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVBasicSessionProvider.h#L31-L46


Frequently Asked Questions
==========
_I can hear the ads, but I can't see them playing._

This usually happens when the ad container view is not in the view hierarchy, or when the ad view (which is a subview of the ad container view) is covered by other views.
