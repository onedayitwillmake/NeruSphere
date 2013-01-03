//
//  NPViewController.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPVisualizerViewController.h"
#import "NPConstants.h"
#import "NPVisualizerView.h"
#import "MPFoldEnumerations.h"
#import "MPFoldTransition.h"

@interface NPVisualizerViewController ()

@end

@implementation NPVisualizerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	// Recenter groma due to a glitch in MPFold transitions placing it at (0,0)
	self.groma.center = CGPointMake(self.view.center.x, self.view.center.y - 42);

	/// Setup the back button to hi-jack behavior so that we can use the fold-transition
//	UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStyleBordered target:self action:@selector(shouldPopViewController:)];
//	self.navigationItem.leftBarButtonItem = backButton;
	
	/// Setup the PaperFold views
	UIStoryboard *storyboard = [UIStoryboard storyboardWithName:[NPkConstants storyboardName] bundle:nil];
	_paperFoldView		= [[PaperFoldView alloc] initWithFrame:CGRectMake(0,0,[self.view bounds].size.width, [self.view bounds].size.height)];
	
	// Center: Visualizer view
	_visualizerView		= [[NPVisualizerView alloc] initWithFrame: CGRectMake(0,0,[self.view bounds].size.width, [self.view bounds].size.height)];
	[_paperFoldView setCenterContentView: _visualizerView];
	
	// Leftside: Set the playlist editor
	_playlistCreator	= [storyboard instantiateViewControllerWithIdentifier: NPkViewControllerIdentifierNPAudioPlayer];
	[[_playlistCreator view] setFrame: CGRectMake(0, 0, 320, [self.view bounds].size.height) ];
	[_paperFoldView setLeftFoldContentView:[_playlistCreator view] foldCount:1 pullFactor:0.9];
	
	// Rightside: Set the visualizer settings controller
	_settingsEditor	= [storyboard instantiateViewControllerWithIdentifier: NPkViewControllerIdentifierNPSettingsPanel ];
	[[_settingsEditor view] setFrame: CGRectMake(0, 0, 320, [self.view bounds].size.height) ];
	[_paperFoldView setRightFoldContentView:[_settingsEditor view] foldCount:1 pullFactor:0.9];
	
	[self.view insertSubview: _paperFoldView atIndex: 0];
//	[self.view insertSubview:_visualizerView atIndex:0];
}

-(void)shouldPopViewController:(id)sender {
	[self.navigationController popViewControllerWithFoldStyle:MPFoldStyleDefault];
}

#pragma mark View Lifecycle
-(void)viewDidAppear:(BOOL)animated {
	//	[self.navigationController setNavigationBarHidden:YES animated:NO];
	
	// Animate groma out, on complete initialize the visualizer view
	[UIView animateWithDuration:0.25 delay:0 options:UIViewAnimationOptionCurveEaseIn animations:^{
		self.groma.transform = CGAffineTransformTranslate( CGAffineTransformScale(CGAffineTransformIdentity, 20, 20), 0, -40);
	} completion:^(BOOL done) {
		[self.groma removeFromSuperview];
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

- (IBAction)shouldOpenPlaylistEditor:(id)sender {
	[_paperFoldView setPaperFoldState: PaperFoldStateLeftUnfolded];
}
- (IBAction)shouldOpenVisualizerSettings:(id)sender {
	[_paperFoldView setPaperFoldState: PaperFoldStateRightUnfolded];
}

-(BOOL)canBecomeFirstResponder { return YES; }

@end
