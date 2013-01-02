//
//  NPViewController.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPVisualizerViewController.h"
#import "NPVisualizerView.h"
#import "MPFoldEnumerations.h"
#import "MPFoldTransition.h"

@interface NPVisualizerViewController ()

@end

@implementation NPVisualizerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	self.groma.center = CGPointMake(self.view.center.x, self.view.center.y - 42);

	/// Sets up the back button, to hi-jack behavior so that we can use the fold-transition
	UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStyleBordered target:self action:@selector(shouldPopViewController:)];
	self.navigationItem.leftBarButtonItem = backButton;
}

-(void)shouldPopViewController:(id)sender {
	[self.navigationController popViewControllerWithFoldStyle:MPFoldStyleDefault];
}

#pragma mark View Lifecycle
-(void)viewDidAppear:(BOOL)animated {
	
	// Animate groma out, on complete initialzie the visualizer view
	[UIView animateWithDuration:0.25 delay:0 options:UIViewAnimationOptionCurveEaseIn animations:^{
		self.groma.transform = CGAffineTransformTranslate( CGAffineTransformScale(CGAffineTransformIdentity, 20, 20), 0, -40);
		
	} completion:^(BOOL done) {
		[self.groma removeFromSuperview];

		_paperFoldView		= [[PaperFoldView alloc] initWithFrame:CGRectMake(0,0,[self.view bounds].size.width, [self.view bounds].size.width)];
//		_visualizerView		= [[NPVisualizerView alloc] initWithFrame: CGRectMake(0,0,[self.view bounds].size.width, [self.view bounds].size.height)];
		[_paperFoldView setCenterContentView: _visualizerView];

		_playlistCreator	= [[NPAudioPlaylistCreatorViewController alloc] initWithNibName:nil bundle:nil];
		[_paperFoldView setLeftFoldContentView:[_playlistCreator view] foldCount:2 pullFactor:0.9];
		
		[self.view addSubview: _paperFoldView ];
	}];
	
	[self becomeFirstResponder];
}

-(void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
	[self resignFirstResponder];
	[_visualizerView removeFromSuperview];
	_visualizerView = nil;
	
}


-(void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
	NSLog(@"Memory warning!");
}


-(BOOL)canBecomeFirstResponder { return YES; }

@end
