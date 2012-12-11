//
//  NPAudioPlayerViewController.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/7/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPAudioPlayerViewController.h"
#import "MPFoldTransition.h"
#import "MPFoldEnumerations.h"
#import <MediaPlayer/MediaPlayer.h>
#import "NPAudioConverter.h"

@interface NPAudioPlayerViewController ()

@end

@implementation NPAudioPlayerViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)dealloc {
	_mediaPicker = nil;
	_song = nil;
}

-(void)shouldPopViewController:(id)sender {
	[self.navigationController popViewControllerWithFoldStyle:MPFoldStyleDefault];
}

- (void)viewDidLoad {
    [super viewDidLoad];
	
	// Override backbutton behavior so we can call popViewController
	UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStyleBordered
																  target:self action:@selector(shouldPopViewController:)];
	self.navigationItem.leftBarButtonItem = backButton;
}

-(void)viewDidAppear:(BOOL)animated {
	if(!_mediaPicker) {
		_mediaPicker =	[[MPMediaPickerController alloc] initWithMediaTypes: MPMediaTypeMusic];
		_mediaPicker.prompt = @"Choose song to export";
		_mediaPicker.allowsPickingMultipleItems = NO;
		_mediaPicker.delegate = self;
		[self presentViewController:_mediaPicker animated:YES completion: nil];
	} else if(_song) {
		[[NPAudioConverter sharedConverter] getConvertedSongPath:_song];
	}
}



- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection {
	_song = [[mediaItemCollection items] objectAtIndex:0];
	[mediaPicker dismissViewControllerAnimated:YES completion:nil];
}

- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker {
	[mediaPicker dismissViewControllerAnimated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
