//
//  NPAudioPlayerViewController.h
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/7/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

@interface NPAudioPlaylistCreatorViewController : UIViewController <UINavigationBarDelegate, MPMediaPickerControllerDelegate> {
	MPMediaPickerController*	_mediaPicker;
	MPMediaItem*				_song;
}

-(void)shouldPopViewController:(id)sender;
@end
