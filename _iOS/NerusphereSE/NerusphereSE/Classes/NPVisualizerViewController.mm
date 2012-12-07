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
	
	// Override backbutton behavior so we can call popViewController
	UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back"
																   style:UIBarButtonItemStyleBordered
																  target:self
																  action:@selector(shouldPopViewController:)];
	
	self.groma.center = self.view.center;
	self.navigationItem.leftBarButtonItem = backButton;
}

-(void)shouldPopViewController:(id)sender {
	[self.navigationController popViewControllerWithFoldStyle:MPFoldStyleDefault];
}

-(void)viewDidAppear:(BOOL)animated {
	
	// Animate groma out, on complete initialzie the visualizer view
	[UIView animateWithDuration:0.25 delay:0 options:UIViewAnimationOptionCurveEaseIn animations:^{
		self.groma.transform = CGAffineTransformScale(CGAffineTransformIdentity, 8, 8);
	} completion:^(BOOL done) {
		[self.groma removeFromSuperview];
		
		self.view.frame = CGRectMake(0, 0, 768, 1024 - self.view.superview.frame.origin.y);
		_visualizerView = [[NPVisualizerView alloc] initWithFrame: self.view.frame];
		[self.view addSubview: _visualizerView ];
	}];
}

-(void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
	[_visualizerView removeFromSuperview];
	_visualizerView = nil;
	
}

-(void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
	
}

@end
