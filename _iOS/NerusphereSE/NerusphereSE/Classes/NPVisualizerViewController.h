//
//  NPViewController.h
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NPVisualizerView.h"
#import "CCGLTouchViewController.h"

@interface NPVisualizerViewController : CCGLTouchViewController {
	NPVisualizerView* _visualizerView;
}
@property (weak, nonatomic) IBOutlet UIImageView *groma;
@end
