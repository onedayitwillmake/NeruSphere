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
	
	[self setupBackButton];
	self.groma.center = self.view.center;
}
-(void)setupBackButton { 
	// Override backbutton behavior so we can call popViewController
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
		self.groma.transform = CGAffineTransformScale(CGAffineTransformIdentity, 8, 8);
	} completion:^(BOOL done) {
		[self.groma removeFromSuperview];
			
		//_paperFoldView		= [[PaperFoldView alloc] initWithFrame:CGRectMake(0,0,[self.view bounds].size.width, boundsHeight)];
		_visualizerView		= [[NPVisualizerView alloc] initWithFrame: CGRectMake(0,0,[self.view bounds].size.width, [self.view bounds].size.height)];
//		_playlistCreator	= [[NPAudioPlaylistCreatorViewController alloc] initWithNibName:nil bundle:nil];
		//_playlistCreator.view.frame =
		

		//paperFoldView setCenterContentView:_visualizerView];
		[self.view addSubview: _visualizerView ];
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
