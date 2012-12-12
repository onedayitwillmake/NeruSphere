//
//  NPViewController.h
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NPVisualizerView.h"
#import "NPAudioPlaylistCreatorViewController.h"
#import "PaperFoldConstants.h"
#import "PaperFoldView.h"

@interface NPVisualizerViewController : UIViewController {
	NPVisualizerView*						_visualizerView;
	NPAudioPlaylistCreatorViewController*	_playlistCreator;
	
	// Paperfold
	PaperFoldView*							_paperFoldView;
}
@property (weak, nonatomic) IBOutlet UIImageView *groma;

#pragma mark - Methods

/// Sets up the back button, to hi-jack behavior so that we can use the fold-transition
-(void)setupBackButton;
@end
