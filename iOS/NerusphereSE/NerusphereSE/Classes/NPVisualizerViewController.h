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
#import "NPVisualizerSettingsPanel.h"
#import "PaperFoldConstants.h"
#import "PaperFoldView.h"

@interface NPVisualizerViewController : UIViewController {
	NPVisualizerView*							_visualizerView;
	NPAudioPlaylistCreatorViewController*		_playlistCreator;
	NPVisualizerSettingsPanel*	_settingsEditor;
	
	// Paperfold
	PaperFoldView*								_paperFoldView;
}
@property (weak, nonatomic) IBOutlet UIImageView *groma;

#pragma mark - Methods

@end
