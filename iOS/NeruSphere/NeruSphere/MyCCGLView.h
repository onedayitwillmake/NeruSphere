//
//  MyCCGLView.h
//  CCGLTouchBasic example
//
//  Created by Matthieu Savary on 09/09/11.
//  Copyright (c) 2011 SMALLAB.ORG. All rights reserved.
//
//  More info on the CCGLTouch project >> http://cocoacid.org/ios/
//  License & disclaimer >> see license.txt file included in the distribution package
//
//  Latest revision on 10/06/12.
//

#import "CCGLTouchView.h"

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/Display.h"
#include "cinder/Filesystem.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "cinder/DataTarget.h"
#include "cinder/gl/Texture.h"

#include "WorldController.h"
#include "Conversions.h"
#include "cinder/CinderMath.h"
#include "cinder/Perlin.h"
#include "cinder/gl/Fbo.h"
#include "AudioAnalyzer.h"
#include "Constants.h"
#include "Textures.h"
#include "PhysicsObject.h"
#include "Planet.h"

@interface MyCCGLView : CCGLTouchView {
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planetPhysicsObject;
}

/**
 *  incoming from controller
 */

-(void)setCubeSize:(float)size;
-(void)setupHeads;
-(void)update;
-(void)drawParticles;
-(void)restart;

@end
