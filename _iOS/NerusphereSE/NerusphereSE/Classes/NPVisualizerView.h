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


@interface NPVisualizerView : CCGLTouchView {
	uint32_t _elapsedFrames;
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planet;
	double	_lastElapsedSeconds;
}


-(void)reset;
-(void)createHeads;
-(void)update;
-(void)drawParticles;

@end
