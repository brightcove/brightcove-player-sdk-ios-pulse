# Pulse Plugin for Brightcove Player SDK for iOS, version 7.1.0.7

## Installation

Pulse Plugin for Brightcove Player SDK provides a dynamic library framework for installation.

The Pulse plugin supports INVIDI Technologies Pulse SDK version 2.6.21.6.0 for iOS and version 2.6.21.6.0 for tvOS, [Pulse iOS and tvOS SDK Reference][pulselatest]. The Podspec for the Pulse Plugin for Brightcove Player SDK references [Pulse SDK Release History][pulsesdkchangelog].

### CocoaPods

You can use [CocoaPods][cocoapods] to add the Pulse Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-Pulse` podspec [here][podspecs]. The PulseSDK needs to be added to your project, download the latest version [here][pulsesdkresource].

#### CocoaPod Podfile example:

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '12.0'
use_frameworks!

target 'MyApp' do
	pod 'Brightcove-Player-Pulse'
end
```

#### XCFramework example:

XCFramework can be installed by appending the `/XCFramework` subspec in the pod name.

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '12.0'
use_frameworks!

target 'MyApp' do
	pod 'Brightcove-Player-Pulse/XCFramework'
end
```

### Manual

To add the Pulse Plugin for Brightcove Player SDK to your project manually:

1. Download the latest zipped Brightcove Player SDK framework from the [releases page][bcovsdkreleases].
1. Download the latest zip'ed release of the BrightcovePulse plugin from our [release page][release].
1. Download the [PulseSDK][pulsesdkresource].
1. On the "General" tab of your application target, add the **dynamic** framework, `BrightcovePlayerSDK.framework` or `BrightcovePlayerSDK.xcframework`, from the Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The universal Framework and XCFramework are found in the ios directory of the download. The _Embed_ setting must be "_Embed & Sign_".
1. On the "General" tab of your application target, add `BrightcovePulse.framework` or `BrightcovePulse.xcframework` from the Pulse Plugin for Brightcove Player SDK download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting must be "_Embed & Sign_".
1. On the "General" tab of your application target, add `PulseSDK.xcframework` and `OMSDK_Invidi.xcframework` from the INVIDI Technologies download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the XCFrameworks must be "_Embed & Sign_".
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.
1. (**Universal Framework** only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcovePulse.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
1. On the "Build Settings" tab of your application target:
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.
1. (**Apple Silicon with Universal Framework** only) On the "Build Settings" tab of your application target:
    * Ensure that `arm64` has been added to your "Excluded Architectures" build setting for `Any iOS Simulator SDK`.
    
### Swift Package Manager

To add the Pulse Plugin for Brightcove Player SDK to your project with Swift Package Manager: 

1. First [follow the steps][corespm] to add the Core XCFramework with Swift Package Mananger.
1. Add the Pulse package to Swift Package Manager using `https://github.com/brightcove/brightcove-player-sdk-ios-pulse.git`.
1. Download the [PulseSDK][pulsesdkresource].
1. On the "General" tab of your application target, add `PulseSDK.xcframework` and `OMSDK_Invidi.xcframework` from the INVIDI Technologies download to the list of **Frameworks, Libraries, and Embedded Content**. The _Embed_ setting for the XCFrameworks must be "_Embed & Sign_".
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.

[corespm]: https://github.com/brightcove/brightcove-player-sdk-ios#swift-package-manager

### Imports

The Pulse Plugin for Brightcove Player SDK can be imported using:
```swift
import BrightcovePulse
```

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-Pulse
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/releases

## Quick Start

The BrightcovePulse plugin is a bridge between [PulseSDK][pulsesdkresource] and the [Brightcove Player SDK for iOS][bcovsdk]. This snippet shows its basic usage with Server Side Ad Rules.

```swift
[1] let contentMetadata = OOContentMetadata()
    contentMetadata.category = "<category>"
    contentMetadata.tags = ["<tag1>", "<tag2>"]
    contentMetadata.flags = ["<flag1>", "<flag2>"]

    let requestSettings = OORequestSettings()
    requestSettings.linearPlaybackPositions = [30, 60]

    let pulseHose = "<pulse domain>"

[2] let pulseOptions: [String:Any] = [
        kBCOVPulseOptionPulsePlaybackSessionDelegateKey: self,
        kBCOVPulseOptionPulsePersistentIdKey: NSUUID().uuidString
    ]

    let sdkManager = BCOVPlayerSDKManager.sharedManager()
[3] let playbackController = sdkManager.createPulsePlaybackController(withPulseHost: pulseHose,
                                                                  contentMetadata: contentMetadata,
                                                                  requestSettings: requestSettings,
                                                                  adContainer: playerView.contentOverlayView,
                                                                  companionSlots: nil,
                                                                  viewStrategy: nil,
                                                                  options: pulseOptions)

    guard let playbackController else {
        return
    }

    playbackController.delegate = self

    videoView.addSubview(playerView)

    let policyKey = "<your-policy-key>"
    let accountID = "<your-account-id>"
    let videoID = "<your-video-id>"
    let playbackService = BCOVPlaybackService(withAccountId: accountID,
                                              policyKey: policyKey)
    let configuration = [
        BCOVPlaybackService.ConfigurationKeyAssetID: videoID
    ]
    playbackService.findVideo(withConfiguration: configuration,
                              queryParameters: nil) { (video: BCOVVideo?,
                                                       jsonResponse: Any?,
                                                       error: Error?) in
        if let video {
            playbackController.setVideos([video])
            playbackController.play()
        }
    }
```

Breaking the code down into steps:

1. Create the same [OOContentMetadata](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OOContentMetadata.html), [OORequestSettings](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OORequestSettings.html) that you would create if you were using INVIDI Technologies's Pulse iOS SDK directly. The Pulse Plugin requires a valid domain and an UIView container to display the ads.
2. Optionally, the plugin can receive a NSDictionary with properties to be used in the plugin. The available keys are `kBCOVPulseOptionPulsePlaybackSessionDelegateKey`, `kBCOVPulseOptionPulseDeviceContainerKey` and `kBCOVPulseOptionPulsePersistentIdKey`. To override the Pulse Session, the PulsePlaybackSessionDelegate needs to be implemented, passing the `kBCOVPulseOptionPulsePlaybackSessionDelegateKey` with the class that implements the method.
3. BrightcovePulse adds some category methods to BCOVPlaybackManager. The first of these is `-createPulsePlaybackControllerWithPulseHost:contentMetadata:requestSettings:adContainer:companionSlots:viewStrategy:options:`. Use this method to create your playback controller. 

[pulselatest]: http://pulse-sdks.videoplaza.com/ios_2/latest/
[pulsesdkresource]: https://github.com/INVIDITechnologies/pulse-sdk-ios-2.x-sample
[pulsesdkchangelog]: http://pulse-sdks.videoplaza.com/ios_2/latest/changelog.html
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[bcovsdkreleases]: https://github.com/brightcove/brightcove-player-sdk-ios/releases
[bcovpulse]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse
[bcovpulsereleases]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/releases
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

## Play and Pause

The Brightcove Pulse Plugin implements custom play and pause logic to ensure the smoothest possible ad experience. Therefore, you will need to make sure that you use the play method on the `BCOVPlaybackController` or the `-[BCOVSessionProviderExtension pulse_play]` or `-[BCOVSessionProviderExtension pulse_pause]` ([BCOVSessionProviderExtension][BCOVPulseComponent]), and not the AVPlayer.

As an example, calling play for the first time on `BCOVPlaybackController` allows BCOVPulse to process preroll ads without any of the content playing before the preroll. For more information on how BCOVPulse overrides the default `BCOVPlaybackController` methods, please check out [BCOVSessionProviderExtension][BCOVPulseComponent].

[BCOVPulseComponent]: https://github.com/brightcove/brightcove-player-sdk-ios-pulse/blob/master/ios/BrightcovePulse.framework/Headers/BCOVPulseComponent.h

## Customizing Plugin Behavior

There are a couple of configuration points in BCOVPulse. You can combine BCOVPulse with another plugin for the Brightcove Player SDK for iOS, you can create a custom view strategy, and you can override the current ads request.

### BCOVPulsePlaybackSessionDelegate

The `BCOVPulsePlaybackSessionDelegate` protocol provides a way for the BrightcovePulse plugin to communicate with the host application. This delegate allows you to override the content metadata and request settings before the session starts. 

The `UIViewController` needs to adopt the `BCOVPulsePlaybackSessionDelegate` protocol.

```swift
class ViewController: UIViewController, BCOVPulsePlaybackSessionDelegate
```

Create a NSDictionary passing the `kBCOVPulseOptionPulsePlaybackSessionDelegateKey` with the class that will implement the method to override the session.

```swift
let pulseOptions = [
    kBCOVPulseOptionPulsePlaybackSessionDelegateKey: self
]
```

Create a `BCOVPlaybackSessionProvider` or `BCOVPlaybackController` for Pulse using the methods in `BCOVPlaybackManager`, remember to pass the dictionary created in the previous step. This example uses a playback controller.

```swift
let sdkManager = BCOVPlayerSDKManager.sharedManager()
let playbackController = sdkManager.createPulsePlaybackController(withPulseHost: pulseHose,
                                                                  contentMetadata: OOContentMetadata(),
                                                                  requestSettings: OORequestSettings(),
                                                                  adContainer: playerView.contentOverlayView,
                                                                  companionSlots: nil,
                                                                  viewStrategy: nil,
                                                                  options: pulseOptions)
```

The `createSessionForVideo:withPulseHost:contentMetadata:requestSettings:` method provides the current video, host domain, [content metadata](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OOContentMetadata.html) and [request settings](http://pulse-sdks.videoplaza.com/ios_2/latest/Classes/OORequestSettings.html) for the session. In this example, the previous objects were empty and will be overriden with a new `OOContentMetadata` and `OORequestSettings` array.

```swift
func createSession(for video: BCOVVideo,
                   withPulseHost pulseHost: String,
                   contentMetadata: OOContentMetadata,
                   requestSettings: OORequestSettings) -> OOPulseSession {
    // Override the content metadata.
    contentMetadata.category = "new_category_for_midrolls"

    // Override the request settings.
    requestSettings.linearPlaybackPositions = [15]
    return OOPulse.session(with: contentMetadata, requestSettings: requestSettings)
}
```

### Composing Session Providers

If you are using more than one plugin to the Brightcove Player SDK for iOS that needs to create a customized playback controller, you must instead compose a chain of session providers and pass the final session provider to the `sdkManager.createPlaybackController(withSessionProvider:viewStrategy:)` method.

When composing session providers, the session preloading can be enabled from [`BCOVBasicSessionProvider`][basicprovider].

[basicprovider]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/BrightcovePlayerSDK.framework/Headers/BrightcovePlayerSDK-Swift.h#L407-L420

## AVPlayerViewController Support

#### Displaying an Ad UI

If you'd like to display your own Ad UI during ad playback you can use the `playbackController:playbackSession:didEnterAd:`  and `playbackController:playbackSession:didExitAdSequence:`  delegate methods. Here is an example:

```swift
// MARK: BCOVPlaybackControllerDelegate

func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didEnter ad: BCOVAd) {
    displayAdUI(withAdDuration: CMTimeGetSeconds(ad.duration))
}

func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didExitAdSequence adSequence: BCOVAdSequence) {
    hideAdUI()
}
```

## Picture-in-Picture

The Brightcove Pulse plugin does not currently support Picture-in-Picture. Attempting to use Picture-in-Picture functionality with the Pulse plugin will result in unexpected behavior.


## Frequently Asked Questions

#### I can hear the ads, but I can't see them playing.

This usually happens when the ad container view is not in the view hierarchy, or when the ad view (which is a subview of the ad container view) is covered by other views.

## Support

If you have questions, need help or want to provide feedback, please use the [Support Portal](https://supportportal.brightcove.com/s/login/) or contact your Account Manager.  To receive notification of new SDK software releases, subscribe to the Brightcove Native Player SDKs [Google Group](https://groups.google.com/g/brightcove-native-player-sdks).
