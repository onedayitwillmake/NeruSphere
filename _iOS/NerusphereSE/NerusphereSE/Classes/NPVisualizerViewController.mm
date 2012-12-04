//
//  NPViewController.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPVisualizerViewController.h"
#import "NPVisualizerView.h"

@interface NPVisualizerViewController ()

@end

@implementation NPVisualizerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	
	_visualizerView = [[NPVisualizerView alloc] initWithFrame: self.view.frame];
	[self.view addSubview: _visualizerView ];
	
	// Do any additional setup after loading the view, typically from a nib.
	NSLog(@"U");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
