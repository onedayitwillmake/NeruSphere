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

- (void)viewDidLoad {
    [super viewDidLoad];
	
	// Override backbutton behavior so we can call popViewController
	UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back"
																   style:UIBarButtonItemStyleBordered
																  target:self
																  action:@selector(shouldPopViewController:)];
	
	self.navigationItem.leftBarButtonItem = backButton;
}

-(void)shouldPopViewController:(id)sender {
	[self.navigationController popViewControllerWithFoldStyle:MPFoldStyleDefault];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
