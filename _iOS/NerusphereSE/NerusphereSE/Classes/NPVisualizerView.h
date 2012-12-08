//
//  NPVisualizerView.h
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CCGLTouchView.h"
#import "WorldController.h"
#import "Conversions.h"
#import "Planet.h"
#import "Box2D/Box2D.h"
#import "AudioAnalyzer.h"


@interface NPVisualizerView : CCGLTouchView {
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planet;
	AudioAnalyzer _audioAnalyzer;
	
	double	_lastElapsedSeconds;	// Store to keep track of delta
}


-(void)reset;
-(void)createHeads;
-(void)update;
-(void)drawParticles;

@end
